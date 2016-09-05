/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 *
 * Compile this source with or without libpthread, and
 * you will understand what it is saying.
 *
 *     gcc -Wall weakref.c
 *
 *     gcc -Wall weakref.c -lpthread
 */
#include <stdio.h>
#include <pthread.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		   void *(*start_routine)(void *), void *arg) __attribute__((weak));

int main(void)
{
	if (pthread_create) {
		printf("This is multi-thread version.\n");
	} else {
		printf("This is single-thread version.\n");
	}

	return 0;
}
