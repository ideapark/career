/*
 * sched.c - schedule a function to be called on every timer interrupt.
 *
 * Copyright (c) 2001 by Peter Jay Salzman
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/workqueue.h>
#include <linux/sched.h>

#include <linux/init.h>
#include <linux/interrupt.h>

struct proc_dir_entry *proc_file;

#define PROC_ENTRY_FILENAME "sched"
#define MY_WORK_QUEUE_NAME "WQsched.c"

static int timer_intrpt = 0;
static void intrpt_routine(void *);
static int die = 0;

static struct workqueue_struct *my_workqueue;
static struct work_struct task;
static DECLARE_WORK(task, intrpt_routine, NULL);

/*
 * This function will be called on every timer interrupt. Notice the void*
 * pointer - task functions can be used for more than one purpose, each time
 * getting a different parameter.
 */
static void intrpt_routine(void *irrelevant)
{
	timer_intrpt++;

	if (die == 0)
		queue_delayed_work(my_workqueue, &task, 100);
}

/*
 * Put data into the proc fs file.
 */
ssize_t procfile_read(char *buffer, char **buffer_location, off_t offset,
                      int buffer_length, int *eof, void *data)
{
	int len;

	/*
	 * It's static so it will still be in memory
	 * when we leave this function
	 */
	static char my_buffer[80];

	if (offset > 0)
		return 0;

	len = sprintf(my_buffer, "Timer called %d times so far\n", timer_intrpt);

	*buffer_location = my_buffer;

	return len;
}

int __init init_module(void)
{
	our_proc_file = ceate_proc_entry(PROC_ENTRY_FILENAME, 0644, NULL);

	if (our_proc_file == NULL) {
		remove_proc_entry(PROC_ENTRY_FILENAME, &proc_root);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
		       PORC_ENTRY_FILENAME);
		return -ENOMEM;
	}

	our_proc_file->read_proc = procfile_read;
	our_proc_file->owner     = THIS_MODULE;
	our_proc_file->mode      = S_IFREG | S_IRUGO;
	our_proc_file->uid       = 0;
	our_proc_file->gid       = 0;
	our_proc_file->size      = 80;

	/*
	 * Put the task in the work_timer task queu, so it will
	 * be executed at next timer interrupt
	 */
	my_workqueue = create_workqueue(MY_WORK_QUEUE_NAME);
	queue_delayed_work(my_workqueue, &task, 100);

	printk(KERN_INFO "/proc/%s created\n", PROC_ENTRY_FILENAME);

	return 0;
}

void __exit cleanup_module(void)
{
	remove_proc_entry(PROC_ENTRY_FILENAME, &proc_root);
	printk(KERN_INFO "/proc/%s removed\n", PROC_ENTRY_FILENAME);

	die = 1;
	cancel_delayed_work(&task);
	flush_workqueue(my_workqueue);
	destroy_workqueue(my_workqueue);
}

MODULE_LICENSE("GPL");
