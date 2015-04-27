#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fifo.h"
#include "../../common/ipc.h"
#include "../../common/common.h"


int client_fd, server_fd;
char fifoPath[FIFO_PATH_LENGTH];
Request req;
Response resp;


int
main(void){

	initializeServer();
	printf("Server running...\n");
	while(1){

		if(read(server_fd, &req, sizeof(Request)) != sizeof(Request))
            continue;

        snprintf(fifoPath, FIFO_PATH_LENGTH, FIFO_CLIENT_PATH,
                (long) req.clientpid);
        client_fd = open(fifoPath, O_WRONLY);
        if(client_fd == -1){
            printf("couldn't open %s", fifoPath);
            continue;
        }

        executeRequest(req, &resp);
        if( write(client_fd, &resp, sizeof(Response)) != sizeof(Response) )
            printf("Error writing to FIFO %s", fifoPath);
        if(close(client_fd) == -1){
            printf("error closing FIFO %s\n", fifoPath); 
        }

	}

}

void
initializeServer(void){

	if(mkfifo(FIFO_SERVER_PATH, S_IRUSR | S_IWUSR | S_IWGRP) == -1
            && errno != EEXIST){
        printf("error creating server fifo");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, onSigInt);

    server_fd = open(FIFO_SERVER_PATH, O_RDONLY);
    if(server_fd == -1){
        printf("error opening the server fifo\n");
        exit(EXIT_FAILURE);
    }
}

void
onSigInt(int sig){
    terminateServer();
}

void
terminateServer(void){
    int exit_status = EXIT_SUCCESS;
    if(client_fd != -1 && close(client_fd) ) exit_status = EXIT_FAILURE;
    if(server_fd != -1 && close(server_fd) ) exit_status = EXIT_FAILURE;
    if(unlink(FIFO_SERVER_PATH) ) exit_status = EXIT_FAILURE;
    exit(exit_status);
}