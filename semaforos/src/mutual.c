#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include "mutual.h"


static Request *mem;
static int memid;
static int semid;

void * getmem(void){
	if( (memid= shmget(KEY, SIZE, IPC_CREAT | 0666)) == -1 )
		printf("Imposible crear una memoria compartida.\n");
	if( !(mem = shmat(memid, NULL, 0)) )
		printf("Imposible crear una memoria compartida.\n");
	return mem;
}

void initsemaphores(void){
	if( (semid = semget(KEY, 3, IPC_CREAT | 0666)) == -1 )
		printf("Imposible crear semaforos.\n");
	semctl(semid, 0, SETVAL, 1);
	semctl(semid, 1, SETVAL, 0);
	semctl(semid, 2, SETVAL, 0);
}

void terminateServer(void){
	int exit_status = EXIT_SUCCESS;
	if( shmdt(mem) != 0 ) 
		exit_status = EXIT_FAILURE;
	if( shmctl(memid, IPC_RMID, NULL) != 0 ) 
		exit_status = EXIT_FAILURE;
	if( semctl(semid, 0, IPC_RMID) != 0 ) 
		exit_status = EXIT_FAILURE;
	if(remove("/tmp/semshm") == -1) 
		exit_status = EXIT_FAILURE;
	exit(exit_status);
}

void terminateClient(void){
	int exit_status = EXIT_SUCCESS;
	if( shmdt(mem) != 0 ) 
		exit_status = EXIT_FAILURE;
	exit(exit_status);
}

void enter(int sem_num){
	struct sembuf sb;
	sb.sem_num = sem_num - 1;
	sb.sem_op = -1;
	sb.sem_flg = SEM_UNDO;
	if( semop(semid,&sb,1) == -1 ) 
		printf("Imposible realizar la accion con el semaforo.\n");
}

void leave(int sem_num){
	struct sembuf sb;
	sb.sem_num = sem_num - 1;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;
	if( semop(semid,&sb,1) == -1 ) 
		printf("Imposible realizar la accion con el semaforo.\n");
}