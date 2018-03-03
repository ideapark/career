#ifndef SEM_H_
#define SEM_H_

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>

union semun {
        int val;                 /* value for SETVAL */
        struct semid_ds *buf;    /* buffer for IPC_STAT, IPC_SET */
        unsigned short *array;   /* array for GETALL, SETALL */
        struct semuninfo *__buf; /* buffer for IPC_INFO, (linux-specific) */
};

#endif /* SEM_H_ */
