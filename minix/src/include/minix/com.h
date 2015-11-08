#ifndef _MINIX_COM_H
#define _MINIX_COM_H

/*
 * ==================================================================
 *                       Magic process numbers
 * ==================================================================
 */

#define ANY     0x7ace  /* used to indicate 'any process' */
#define NONE    0x6ace  /* used to indicate 'no process at all' */
#define SELF    0x8ace  /* used to indicate 'own process' */

/*
 * ==================================================================
 *         Process numbers of processes in the system image
 * ==================================================================
 */

/*
 * The values of serval task numbers depend on whether they or other tasks
 * are enabled. They are defined as (PREVIOUS_TASK - ENABLE_TASK) in general
 * ENABLE_TASK is either 0 or 1, so a task either gets a new number, or gets
 * the same number as the previous task and is further unused. Note that the
 * order should correspond to the order in the task table defined in table.
 */

/* Kernel tasks. These all run in the same address space. */
#define IDLE          -4  /* runs when no one else can run */
#define CLOCK         -3  /* alarms and other clock functions */
#define SYSTEM        -2  /* request system functionality */
#define KERNEL        -1  /* pseudo-process for IPC and scheduling */
#define HARDWARE  KERNEL  /* for hardware interrupt handlers */

/* Number of tasks. Note that NR_PROCS is defined in <minix/config.h> */
#define NR_TASKS       4

/* Use-space processes, that is, device drivers, servers, and INIT. */
#define PM_PROC_NR     0  /* process manager */
#define FS_PROC_NR     1  /* file system */
#define RS_PROC_NR     2  /* reincarnation server */
#define MEM_PROC_NR    3  /* memory driver (RAM disk, null, etc.) */
#define LOG_PROC_NR    4  /* log device driver */
#define TTY_PROC_NR    5  /* terminal (TTY) driver */
#define DRVR_PROC_NR   6  /* device driver for boot medium */
#define INIT_PROC_NR   7  /* init -- goes multiuser */

/* Number of processes contained in the system image. */
#define NR_BOOT_PROCS  (NR_TASKS + INIT_PROC_NR + 1)

/*
 * ==================================================================
 *                      Kernel notification types
 * ==================================================================
 */

/*
 * Kernel notification types. In principle, these can be sent to any process
 * so make sure that these types do not interfere with other message types.
 * Notifications are prioritized because of the way they are unhold() and
 * blocking notificatoins are delivered. The lowest numbers go first. The
 * offset are used for the per-process notification bit maps.
 */
#define NOTIFY_MESSAGE     0x1000
#define NOTIFY_FROM(p_nr)  (NOTIFY_MESSAGE | ((p_nr) + NR_TASKS))
#  define SYN_ALARM     NOTIFY_FROM(CLOCK)        /* synchronous alarm */
#  define SYN_SIG       NOTIFY_FROM(SYSTEM)       /* system signal */
#  define HARD_INT      NOTIFY_FROM(HARDWARE)     /* hardware interrupt */
#  define NEW_KSIG      NOTIFY_FROM(HARDWARE)     /* new kernel signal */
#  define FKEY_PRESSED  NOTIFY_FROM(TTY_PROC_NR)  /* functoin key press */

/* Shorthands for message parameters passed with notifications */
#define NOTIFY_SOURCE      m_source
#define NOTIFY_TYPE        m_type
#define NOTIFY_ARG         m2_l1
#define NOTIFY_TIMESTAMP   m2_l2
#define NOTIFY_FLAGS       m2_i1

/*
 * ==================================================================
 *             Messages for BLOCK and CHARACTER device drivers
 * ==================================================================
 */

/* Message types for device drivers. */
#define DEV_RQ_BASE   0x400  /* base for device request types */
#define DEV_RS_BASE   0x500  /* base for device response types */

#define CANCEL        (DEV_RQ_BASE +  0)  /* general req to force a task to stop*/
#define DEV_READ      (DEV_RQ_BASE +  3)  /* read from minor device */
#define DEV_WRITE     (DEV_RQ_BASE +  4)  /* write to minor device */
#define DEV_IOCTL     (DEV_RQ_BASE +  5)  /* I/O control code */
#define DEV_OPEN      (DEV_RQ_BASE +  6)  /* open a minor device */
#define DEV_CLOSE     (DEV_RQ_BASE +  7)  /* close a minor device */
#define DEV_SCATTER   (DEV_RQ_BASE +  8)  /* write from a vector */
#define DEV_GATHER    (DEV_RQ_BASE +  9)  /* read into a vector */
#define TTY_SETPGRP   (DEV_RQ_BASE + 10)  /* set process group */
#define TTY_EXIT      (DEV_RQ_BASE + 11)  /* process group leader exited */
#define DEV_SELECT    (DEV_RQ_BASE + 12)  /* request select() attention */
#define DEV_STATUS    (DEV_RQ_BASE + 13)  /* request driver status */






#endif /* _MINIX_COM_H */
