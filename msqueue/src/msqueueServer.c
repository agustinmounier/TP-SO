#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "msqueue.h"

static int msqidRcv, msqidSnd;

int
main(void){
	RequestMsg reqMsg;
	ResponseMsg resMsg;
	signal(SIGINT, onSigInt);

	initializeServer();
	while(1){
		if( msgrcv(msqidRcv, (char *)&reqMsg, sizeof(reqMsg), 0, 0) == -1 ){
            if(errno == EINTR)
                continue;
            perror("msgrcv");
            break;
        }
        executeRequest(reqMsg.req, &(resMsg.resp));
        resMsg.mtype = reqMsg.mtype;
        if( msgsnd(msqidSnd, (char *)&resMsg, sizeof(ResponseMsg), 0) == -1 ){
            perror("msgsnd");
            break;
        }
	}
	terminateServer();


}

void
initializeServer(void){

	FILE *f1 = fopen("/tmp/mqueues-clients","wb");
    fclose(f1);
    
    FILE *f2 = fopen("/tmp/mqueues-server","wb");
    fclose(f2);

    if( (msqidRcv = msgget(CLIENTS_KEY, IPC_CREAT | 0666)) == -1 )
        printf("Error when creating msqueue rcv.\n");
    if ( (msqidSnd = msgget(SERVER_KEY, IPC_CREAT | 0666)) == -1 )
		printf("Error when creating msqueue send.\n");
}

void
terminateServer(void){
    int exit_status = EXIT_SUCCESS;
    if(msqidRcv != -1 && msgctl(msqidRcv, IPC_RMID, NULL) == -1) 
    	exit_status = EXIT_FAILURE;
    if(msqidSnd != -1 && msgctl(msqidSnd, IPC_RMID, NULL) == -1) 
    	exit_status = EXIT_FAILURE;
    if(remove("/tmp/mqueues-clients") == -1 || remove("/tmp/mqueues-server") == -1) 
    	exit_status = EXIT_FAILURE;
    exit(exit_status);
}

void
onSigInt(int sig){
    terminateServer();
}