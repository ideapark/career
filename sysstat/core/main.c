/*
 * sysstat/core/main.c - sysstat main engine
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>

#include "core/config.h"
#include "core/main.h"
#include "irq/irq.h"
#include "sys/sys.h"
#include "proc/proc.h"
#include "task/task.h"

long g_timestamp     = 0;
int32_t g_sampcnt    = 0;
int32_t g_sampcntmax = SAMPLECNT_MAX;

/*
 * boolean: awaiting trigger
 */
static char awaittrigger;

/*
 * callback handler queue
 */
static queue_entry g_callbackqueue[CALLBACKQUEUE_LEN] = {{
  .callback = {
    .init = NULL,
    .run  = NULL,
    .exit = NULL,
  },
  .taken = untaken,
}};

static void reset_timestamp(void)
{
  struct timeval time_val;

  gettimeofday(&time_val, NULL);
  g_timestamp = time_val.tv_sec;
}

/*
 * sysstat initialization
 */
static void sysstat_init(void)
{
  int i;

  for (i = 0; i < CALLBACKQUEUE_LEN; i++) {
    if (g_callbackqueue[i].taken == taken)
      (*g_callbackqueue[i].callback.init)();
  }
}

/*
 * sysstat do work
 */
static void sysstat_run(void)
{
  int i;

  alarm(DEFAULT_INTERVAL);
  for (g_sampcnt = 0; g_sampcnt < g_sampcntmax; g_sampcnt++) {
    if (g_sampcnt > 0 && awaittrigger)
      pause();
    awaittrigger = 1;
    reset_timestamp();
    for (i = 0; i < CALLBACKQUEUE_LEN; i++) {
      if (g_callbackqueue[i].taken == taken)
        (*g_callbackqueue[i].callback.run)();
    }
  }
}

/*
 * sysstat exit
 */
static void sysstat_exit(void)
{
  int i;

  for (i = 0; i < CALLBACKQUEUE_LEN; i++) {
    if (g_callbackqueue[i].taken == taken)
      (*g_callbackqueue[i].callback.exit)();
  }
}

/*
 * handler for ALARM signal
 */
static void getalarm(int sig)
{
  awaittrigger = 0;
  alarm(DEFAULT_INTERVAL); /* restart the timer */
}

/*
 * handler for USR1 signal
 */
static void getusr1(int sig)
{
  awaittrigger = 0;
}

/*
 * handler for USR2 signal
 */
static void getusr2(int sig)
{
  awaittrigger = 0;
  g_sampcntmax = g_sampcnt; /* force stop after next sample */
}

/*
 * handler for HUB signal
 */
static void gethub(int sig)
{
  fprintf(stderr, "get hub signal, ignoring!\n");
}

/*
 * handler for TERM signal
 */
static void getterm(int sig)
{
  sysstat_exit();
  exit(EXIT_SUCCESS);
}

/*
 * register system signal handler
 */
static void setup_signalhandler()
{
  struct sigaction sigact;
  memset(&sigact, 0, sizeof(sigact));

  /*
   * install the signal-handler for ALARM, USR1 and
   * USR2 (triggers for the next sample), HUB, TERM
   */
  sigact.sa_handler = getusr1;
  sigact.sa_flags = 0;
  sigemptyset(&sigact.sa_mask);
  if (sigaction(SIGUSR1, &sigact, NULL)) {
    perror("register of SIGUSR1 handler failed: ");
    exit(EXIT_FAILURE);
  }

  sigact.sa_handler = getusr2;
  sigact.sa_flags = 0;
  sigemptyset(&sigact.sa_mask);
  if (sigaction(SIGUSR2, &sigact, NULL)) {
    perror("register of SIGUSR2 handler failed: ");
    exit(EXIT_FAILURE);
  }

  sigact.sa_handler = gethub;
  sigact.sa_flags = 0;
  sigemptyset(&sigact.sa_mask);
  if (sigaction(SIGHUP, &sigact, NULL)) {
    perror("register of SIGHUP handler failed: ");
    exit(EXIT_FAILURE);
  }

  sigact.sa_handler = getalarm;
  sigact.sa_flags = 0;
  sigemptyset(&sigact.sa_mask);
  if (sigaction(SIGALRM, &sigact, NULL)) {
    perror("register of SIGALRM handler failed: ");
    exit(EXIT_FAILURE);
  }

  sigact.sa_handler = getterm;
  sigact.sa_flags = 0;
  sigemptyset(&sigact.sa_mask);
  sigaddset(&sigact.sa_mask, SIGTERM);
  if (sigaction(SIGTERM, &sigact, NULL)) {
    perror("register SIGTERM handler failed: ");
    exit(EXIT_FAILURE);
  }
}

/*
 * register call back
 */
int register_callback(const callback_t *callback)
{
  int i;

  for (i = 0; i < CALLBACKQUEUE_LEN; i++) {
    if (g_callbackqueue[i].taken == untaken) {
      g_callbackqueue[i].callback.init = callback->init;
      g_callbackqueue[i].callback.run  = callback->run;
      g_callbackqueue[i].callback.exit = callback->exit;
      g_callbackqueue[i].taken = taken;
      return i;
    }
  }
  return -1;
}

/*
 * unregister call back
 */
void unregister_callback(int i)
{
  if (i < 0 || i >= CALLBACKQUEUE_LEN) {
    fprintf(stderr, "unregister: invalid index %d.\n", i);
    return;
  }
  g_callbackqueue[i].taken = untaken;
}

/*
 * chdir to sample file directory
 */
static int option_usage(int argc, char *argv[])
{
  static const char *help = "Usage:\n\t%s [directory-to-save-result]\n";

  struct stat statbuf;
  const char *dir;

  if (argc == 1)
    return 0; /* default save to current directory */

  if (argc != 2)
    goto fail;

  dir = argv[1];
  if (stat(dir, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
    if (chdir(dir) == -1)
      goto fail;
    else
      return 0;
  } else
    goto fail;

fail:
  fprintf(stderr, help, argv[0]);
  exit(-1);
}

/*
 * fork child process, parent process exit
 */
static void go_fork(void)
{
  switch (fork()) {
    case -1:
      perror("sysstat: fork() failed: ");
      exit(EXIT_FAILURE);
      break;
    case 0:
      break;
    default:
      /* parent */
      _exit(EXIT_SUCCESS);
      break;
  }
}

/*
 * setup daemon process
 */
static void setup_sysstatdaemon()
{
  go_fork();

  if (setsid() < 0) {
    perror("go_daemon: couldn't setsid\n");
    exit(EXIT_FAILURE);
  }

  go_fork();
}

int main(int argc, char *argv[])
{
  (void)option_usage(argc, argv);

  callback_t irq = {.init=irq_init, .run=irq_run, .exit=irq_exit};
  register_callback(&irq);

  callback_t sys = {.init=sys_init, .run=sys_run, .exit=sys_exit};
  register_callback(&sys);

  callback_t proc = {.init=proc_init, .run=proc_run, .exit=proc_exit};
  register_callback(&proc);

  callback_t task = {.init=task_init, .run=task_run, .exit=task_exit};
  register_callback(&task);

  setup_signalhandler();
  setup_sysstatdaemon();

  sysstat_init();
  sysstat_run();
  sysstat_exit();

  return 0;
}
