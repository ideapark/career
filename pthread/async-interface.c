/*
 * Example program featuring an asynchronous user interface
 */

#include <pthread.h>
#include <pthread_exception.h>
#include <stdio.h>
#include <time.h>

#define check(status, string)                                                    \
    if (status != 0) {                                                           \
        fprintf(stderr, "%s status %d: %s\n", string, status, strerror(status)); \
    }

#define PROMPT     "Info> "  /* Prompt string */
#define MAXLINSIZ  81        /* Command line size */
#define THDNUM      5        /* Number of server threads */

/*
 * Server thread "states"
 */
#define ST_INIT     0   /* "Initial" state (no thread) */
#define ST_FINISHED 1   /* Command completed */
#define ST_CANCELED 2   /* Command was canceled */
#define ST_ERROR    3   /* Command was terminated by an error */
#define ST_RUNNING  4   /* Command is running */

#ifndef FALSE
# define FALSE  0
# define TRUE   (!FALSE)
#endif

#ifndef NULL
# define NULL   ((void *)0)
#endif

/*
 * Global variables
 */
struct THREAD_DATA {
    pthread_t       thread; /* Server thread handle */
    pthread_mutex_t mutex;  /* Mutex protect fields below */
    int             time;   /* Amount of delay remaining */
    char            task;   /* Task being performed ('t' or 'd') */
    int             state;  /* State of server thread */
} thread_data[THDNUM];

/* Mutex to protect "free_thread" */
pthread_mutex_t free_thread_mutex = PTHREAD_MUTEX_INITIALIZER;
/* Condition variable for same */
pthread_cond_t free_thread_cv = PTHREAD_COND_INITIALIZER;
/* Flag indicating a free thread */
int free_thread;

/*
 * Local Routines
 */
static void dispatch_task(void *(*routine)(void *), char task, int time);
static void do_cancel(int index);
static void do_cleanup(int index, int final_state);
static void *do_date(void *arg);
static void do_delay(int index);
static void do_status(int index);
static void *do_time(void *arg);
static void do_wait(int index);
static int find_free_thread(int *index);
static char *get_cmd(char *buffer, int size);
static int get_y_or_n(char *query, char defans);
static void init_routine(void);
static void print_help(void);

int main(void)
{
    int  done = FALSE;        /* Flag indicating user is "done" */
    char cmdline[MAXLINSIZ];  /* Command line */
    char cmd_wd[MAXLINSIZ];   /* Command word */
    int  cmd_arg;             /* Command argument */
    int  cmd_cnt;             /* Number of items on command line */
    int  status;
    void *(*routine)(void *);  /* Routine to execute in a thread */
    static pthread_once_t once_block = PTHREAD_ONCE_INIT;

    /*
     * Perform program initialization.
     */
    status = pthread_once(&once_block, init_routine);
    check(status, "Pthread_once");

    /*
     * Main command loop
     */
    do {
        /*
         * Get and parse a command. Yield first so that any threads waiting
         * to execute get a chance to before we take out the global lock
         * and block for I/O.
         */
        sched_yield();
        if (get_cmd(cmdline, sizeof(cmdline))) {
            cmd_cnt = sscanf(cmdline, "%s %d", cmd_wd, &cmd_arg);
            routine = NULL;
            if ((cmd_cnt == -1) || (cmd_cnt == 2)) {
                cmd_wd[0] = tolower(cmd_wd[0]);
                switch (cmd_wd[0]) {
                case 'h':
                case '?':
                    print_help();
                    break;
                case 'q':
                    done = TRUE;
                    break;
                case 's':
                    do_status((cmd_cnt == 2) ? cmd_arg : -1);
                    break;
                    /* These commands require an argument */
                case 'c':   /* "Cancel" */
                case 'd':   /* "Date" */
                case 't':   /* "Time" */
                case 'w':   /* "Wait" */
                    if (cmd_cnt != 2) {
                        printf("Missing command argument.\n");
                    } else {
                        switch (cmd_wd[0]) {
                        case 'c':
                            do_cancel(cmd_arg);
                            break;
                        case 'd':
                            routine = do_date;
                            break;
                        case 't':
                            routine = do_time;
                            break;
                        case 'w':
                            do_wait(cmd_arg);
                            break;
                        }
                    }
                    break;
                default:
                    printf("Unrecognized command.\n");
                    break;
                }
            } else if (cmd_cnt != EOF) {
                printf("Unexpected parse error.\n");
            }
            /*
             * If there is a routine to be executed in a server thread,
             * create the thread.
             */
            if (routine)
                dispatch_task(routine, cmd_wd[0], cmd_arg);
        } else {
            done = TRUE;
        }
    } while (!done);
    return 0;
}

/*
 * Create a thread to handle the user's request.
 */
static void dispatch_task(void *(*routine)(void *), char task, int time)
{
    int i;
    int status;

    if (find_free_thread(&i)) {
        /*
         * Record the data for this thread where both the main thread and the
         * server thread can share it. Lock the mutex to ensure exclusive
         * access to the storage.
         */
        status = pthread_mutex_lock(&thread_data[i].mutex);
        check(status, "Mutex_lock");
        thread_data[i].time = time;
        thread_data[i].task = task;
        thread_data[i].state = ST_RUNNING;
        status = pthread_mutex_unlock(&thread_data[i].mutex);
        check(status, "Mutex_unlock");
        /*
         * Create the thread, using the default attributes. The thread will
         * execute the specified routine and get its data from array slot 'i'.
         */
        status = pthread_create(&thread_data[i].thread, NULL, routine, (void *)i);
        check(status, "Pthread_create");
        printf("This is command #%d.\n\n", i);
    }
}

/*
 * Wait for the completion of the specified command.
 */
static void do_cancel(int index)
{
    int cancelable;
    int status;

    if ((index < 0) || (index >= THDNUM)) {
        printf("Bad command number %d.\n", index);
    } else {
        status = pthread_mutex_lock(&thread_data[index].mutex);
        check(status, "Mutex_lock");
        cancelable = (thread_data[index].state == ST_RUNNING);
        status = pthread_mutex_unlock(&thread_data[index].mutex);
        check(status, "Mutex_unlock");
        if (cancelable) {
            status = pthread_cancel(thread_data[index].thread);
            check(status, "Pthread_cancel");
        } else {
            printf("Command %d is not active.\n", index);
        }
    }
}

/*
 * Post-task clean-up routine.
 */
static void do_cleanup(int index, int final_state)
{
    int status;
    /*
     * This thread is about to make the change from "running" to "finished",
     * so lock a mutex to prevent a race condition in which the main thread
     * sees this thread as finished before it is actually done cleaning up.
     *
     * Note that when attempting to lock more than one mutex at a time,
     * always lock the mutexes in the same order everywhere in the code.
     * The ordering here is the same as in "find_free_thread".
     */
    status = pthread_mutex_lock(&free_thread_mutex);
    check(status, "Mutex_lock");
    /*
     * Mark the thread as finished with its task.
     */
    status = pthread_mutex_lock(&thread_data[index].mutex);
    check(status, "Mutex_lock");
    thread_data[index].state = final_state;
    status = pthread_mutex_unlock(&thread_data[index].mutex);
    check(status, "Mutex_unlock");
    /*
     * Set the flag indicating that there is a free thread, and signal the
     * main thread, in case it is waiting.
     */
    free_thread = TRUE;
    status = pthread_cond_signal(&free_thread_cv);
    check(status, "Cond_signal");
    status = pthread_mutex_unlock(&free_thread_mutex);
    check(status, "Mutex_unlock");
}

/*
 * Thread routine that prints out the date.
 *
 * Synchronize access to ctime as it is not thread-safe (it returns the address
 * of a static string). Also synchronize access to stdio routines.
 */
static void *do_date(void *arg)
{
    time_t clock_time;  /* Julian time */
    char *date_str;
    char day[4], month[4], date[3], year[5];

    TRY {
        /*
         * Pretend that this task actually takes a long time to perform.
         */
        do_delay((int)arg);
        clock_time = time((time_t *)0);
        date_str = ctime(&clock_time);
        sscanf(date_str, "%s %s %s %s %s", day, month, date, year);
        printf("%d) Today is %s, %s %s %s.\n\n", arg, day, date, month, year);
    } CATCH (pthread_cancel_e) {
        printf("%d) Canceld.\n", arg);
        do_cleanup((int)arg, ST_CANCELED);
        RERAISE;
    } CATCH_ALL {
        printf("%d) ", arg);
        pthread_exc_report_np(THIS_CATCH);
        do_cleanup((int)arg, ST_ERROR);
        RERAISE;
    } ENDTRY;
    do_cleanup((int)arg, ST_FINISHED);
    return arg;
}

/*
 * Delay routine
 *
 * Since the actual tasks that threads do in this program take so little time
 * to perform, execute a delay to make it seem like they are taking a long
 * time. Also, this will give the user something of which to query the progress.
 */
static void do_delay(int index)
{
    static struct timespec interval = {1,0};
    int done;
    int status;

    while (TRUE) {
        /*
         * Decrement the global count, so the main thread can see how much
         * progress we have made. Keep decrementing as long as the remaining
         * time is greater than zero.
         *
         * Lock the mutex to ensure no conflict with the main thread that
         * might be reading the time remaining while we are decrementing it.
         */
        status = pthread_mutex_lock(&thread_data[index].mutex);
        check(status, "Mutex_lock");
        done = ((thread_data[index].time--) <= 0);
        status = pthread_mutex_unlock(&thread_data[index].mutex);
        check(status, "Mutex_unlock");
        if (done)
            break;
        pthread_delay_np(&interval);
    }
}

/*
 * Print the status of the specified thread.
 */
static void do_status(int index)
{
    int start, end;
    int i;
    int output = FALSE;
    int status;

    if ((index < -1) || (index >= THDNUM)) {
        printf("Bad command number %d.\n", index);
    } else {
        if (index == -1)
            start = 0, end = THDNUM;
        else
            start = index, end = start + 1;
        for (i = start; i < end; i++) {
            status = pthread_mutex_lock(&thread_data[i].mutex);
            check(status, "Mutex_lock");
            if (thread_data[i].state != ST_INIT) {
                printf("Command #%d: ", i);
                switch (thread_data[i].task) {
                case 't':
                    printf("\"time\"");
                    break;
                case 'd':
                    printf("\"date\"");
                    break;
                default:
                    printf("[unknown]");
                    break;
                }
                switch (thread_data[i].state) {
                case ST_FINISHED:
                    printf("completed");
                    break;
                case ST_CANCELED:
                    printf("canceled");
                    break;
                case ST_ERROR:
                    printf("terminated by error");
                    break;
                case ST_RUNNING:
                    if (thread_data[i].time < 0)
                        printf("waiting to print");
                    else
                        printf("%d seconds remaining", thread_data[i].time);
                    break;
                default:
                    printf("Bad thread state.\n");
                    break;
                }
                printf(".\n");
                output = TRUE;
            }
            status = pthread_mutex_unlock(&thread_data[i].mutex);
            check(status, "Mutex_unlock");
        }
        if (!output)
            printf("No such command.\n");
        printf("\n");
    }
}

/*
 * Thread routine that prints out the date.
 */
static void *do_time(void *arg)
{
    time_t clock_time;
    char *date_str;
    char time_str[8];

    TRY {
        /*
         * Pretend that this task acutally takes a long time to perform.
         */
        do_delay((int)arg);
        clock_time = time((time_t *)0);
        date_str = ctime(&clock_time);
        sscanf(date_str, "%*s %*s %*s %*s", time_str);
        printf("%d) At the tone the time will be, %s.%c\n\n", arg, time_str, '\007');
    } CATCH (pthread_cancel_e) {
        printf("%d) Canceled.\n", arg);
        do_cleanup((int)arg, ST_CANCELED);
        RERAISE;
    } CATCH_ALL {
        printf("%d) ", arg);
        pthread_exc_report_np(THIS_CATCH);
        do_cleanup((int)arg, ST_ERROR);
        RERAISE;
    } ENDTRY;
    do_cleanup((int)arg, ST_FINISHED);
    return arg;
}

/*
 * Wait for the completion of the specified command.
 */
static void do_wait(int index)
{
    int status;
    void *value;

    if ((index < 0) || (index >= THDNUM)) {
        printf("Bad command number %d.\n", index);
    } else {
        status = pthread_join(thread_data[index].thread, &value);
        check(status, "Pthread_join");
        if (value == (void *)index)
            printf("Command %d terminated successfully.\n", index);
        else if (value == PTHREAD_CANCELED)
            printf("Command %d was canceled.\n", index);
        else
            printf("Command %d terminated with unexpected value %#lx", index, value);
    }
}

/*
 * Find a free server thread to handle the user's request.
 *
 * If a free thread is found, its index is written at the supplied address
 * and the function returns true.
 */
static int find_free_thread(int *index)
{
    int i;
    int found;
    int retry = FALSE;
    int status;

    do {
        /*
         * We are about to look for a free thread, so prevent the data state
         * from changing while we are looking.
         *
         * Note that when attempting to lock more than one mutex at a time,
         * always lock the mutexes in the same order everywhere in the code.
         * The ordering here is the same as in "do_cleanup".
         */
        status = pthread_mutex_lock(&free_thread_mutex);
        check(status, "Mutex_lock");
        /*
         * Find a slot that does not have a running thread in it.
         *
         * Before checking, lock the mutex to prevent conflict with the thread
         * if it is running.
         */
        for (i = 0, found = FALSE; i < THDNUM; i++) {
            status = pthread_mutex_lock(&thread_data[i].mutex);
            check(status, "Mutex_lock");
            found = (thread_data[i].state != ST_RUNNING);
            status = pthread_mutex_unlock(&thread_data[i].mutex);
            check(status, "Mutex_unlock");
            if (found)
                break;
        }
        if (found) {
            retry = FALSE;
        } else {
            retry = get_y_or_n("All threads are currently busy, do you want to wait?", 'y');
            if (retry) {
                free_thread = FALSE;
                while (!free_thread)
                    pthread_cond_wait(&free_thread_cv, &free_thread_mutex);
            }
        }
        pthread_mutex_unlock(&free_thread_mutex);
    } while (retry);

    if (found) {
        /*
         * Request the Threads Library to reclaim its internal storage
         * for this old thread before we use the handle to create a new one.
         */
        status = pthread_detach(thread_data[i].thread);
        check(status, "Pthread_detach");
        *index = i;
    }
    return found;
}

/*
 * Get the next user command.
 *
 * Synchronize I/O with other threads to prevent conflicts if the stdio
 * routines are not thread-safe.
 */
static char *get_cmd(char *buffer, int size)
{
    printf(PROMPT);
    return fgets(buffer, size, stdin);
}

/*
 * Get a yes or no answer to a query. A "blank" answer uses default answer.
 *
 * Returns TRUE for "yes" and FALSE for "no".
 */
static int get_y_or_n(char *query, char defans)
{
    char buffer[MAXLINSIZ];
    int answer;
    int retry = TRUE:

        do {
            buffer[0] = '\0';
            flockfile(stdout);
            flockfile(stdin);
            printf("%s [%c] ", query, defans);
            fgets(buffer, sizeof(buffer), stdin);
            funlockfile(stdin);
            funlockfile(stdout);

            if (buffer[0] == '\0')
                buffer[0] = defans;

            switch (buffer[0]) {
            case 'y':
            case 'Y':
                answer = TRUE;
                retry = FALSE;
                break;
            case 'n':
            case 'N':
                answer = FALSE;
                retry = FALSE;
                break;
            default:
                printf("Please enter \"Y\" or \"N\".\n");
                retry= TRUE;
                break;
            }
        } while (retry);
    return answer;
}

/*
 * Initialization routine.
 *
 * Called as a one-time initialization action.
 */
static void inti_routine(void)
{
    int i;
    for (i = 0; i < THDNUM; i++) {
        pthread_mutex_init(&thread_data[i].mutex, NULL);
        thread_data[i].time = 0;
        thread_data[i].task = '\0';
        thread_data[i].state = ST_INIT;
    }
}

/*
 * Print help text.
 */
static void print_help(void)
{
    printf("Commands are formed by a verb and optional numeric argument.\n");
    printf("The following commands are available:\n");
    printf("\tCancel\t[command]\tCancel running command\n");
    printf("\tDate\t[delay]\t\tPrint the date\n");
    printf("\tHelp\t\tPrint this text\n");
    printf("\tQuit\t\tQuit (same as EOF)\n");
    printf("\tStatus\t[command]\tReport on running command\n");
    printf("\tTime\t[delay]\t\tPrint the time\n");
    printf("\tWait\t[command]\tWait for command to finish\n");
    printf("\n[command] refers to the command number.\n");
    printf("[delay] delays command execution for some number of seconds.\n");
    printf("This delay simulates a command task that actually takes some\n");
    printf("period of time to execute. During this delay, commands may be\n");
    printf("initiated, queried, and/or canceled.\n");
}
