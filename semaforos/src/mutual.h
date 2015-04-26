#ifndef MUTUAL_H
#define MUTUAL_H

#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "../../common/ipc.h"
 
#define SIZE sizeof(Request)
#define KEY ftok("/tmp/semshm", 1)
 

void * getmem(void);

void initsemaphores(void);

/*
 * SIGINT handler
 */
void onSigInt(int sig);

/**
 * Close open semaphores before calling exit()
 */
void terminateClient(void);

/**
 * Close open semaphores and unlink them before calling exit()
 */
void terminateServer(void);

void enter(int sem_num);

void leave(int sem_num);

#endif