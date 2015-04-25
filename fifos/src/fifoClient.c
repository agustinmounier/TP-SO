#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "fifo.h"
#include "../../common/ipc.h"
#include "../../common/common.h"

char fifoPath[FIFO_PATH_LENGTH];
int server_fd, client_fd;
Response response;
Request request;

static void removeFifo(void);
void onSigInt(int sig);

static void
removeFifo(void){
    unlink(fifoPath);
}

/*
int
main(void){
	char input[30];
	printf("Welcome to SO-cinema.\n");
	initialize();
	char check[20] = "check_seats";
	while(1){
		printf("Type the desired option: \n");
		printf("ShowMovies, \n");
		fgets(input, 30, stdin);
		if(strcmp(input, check)){
			printf("seats %d\n", check_seats("01", "0100"));
		}else{
			printf("invalid comand.\n");
		}
	}
}
*/
void
initialize(void){

	umask(0);
	snprintf(fifoPath, FIFO_PATH_LENGTH, FIFO_CLIENT_PATH, (long) getpid());

	if(mkfifo(fifoPath, S_IRUSR | S_IWUSR | S_IWGRP) == -1
        && errno != EEXIST){
        printf("error while creating the fifo\n");
        exit(EXIT_FAILURE);
    }

    server_fd = open(FIFO_SERVER_PATH, O_WRONLY);

    if(server_fd == -1){
        printf("Error opening server FIFO\n");
        exit(EXIT_FAILURE);
    }

	signal(SIGINT, onSigInt);
    
    if(atexit(removeFifo) != 0){
        printf("atexit error\n");
        exit(EXIT_FAILURE);
    }
}

//TODO: ver q onda
void
terminateClient(void){
    int exit_status = EXIT_SUCCESS;
    if(close(client_fd)) exit_status = EXIT_FAILURE;
    if(close(server_fd)) exit_status = EXIT_FAILURE;
    if(unlink(fifoPath)) exit_status = EXIT_FAILURE;
    exit(exit_status);
}

void onSigInt(int sig){
    terminateClient();
}

void
sendRequest(void){

	if (write(server_fd, &request, sizeof(request)) != sizeof(request)){
		printf("Error when writing into server.\n");
        exit(EXIT_FAILURE);
    }
	if( (client_fd = open(fifoPath, O_RDONLY)) == -1){
        printf("Error when opening client FIFO\n");
        exit(EXIT_FAILURE);
    }

    if( read(client_fd, &response, sizeof(Response)) != sizeof(Response)){
        printf("Couldn't read response from the server\n");
        exit(EXIT_FAILURE);
    }

    if( close(client_fd) == -1 ){
        printf("Error while closing the client's FIFO\n");
        exit(EXIT_FAILURE);
    }

}

int
getSeats(char * movieId, char * movieTime){

	request.clientpid = getpid();
	request.ac = CHECK_SEATS;
	strcpy(request.movieID, movieId);
	strcpy(request.times, movieTime);
	sendRequest();
	return response.value;
}

List_Movies
getMovies(void){
    request.clientpid = getpid();
    request.ac = GET_MOVIES;
    sendRequest();
    return response.list;
}

void
getTimes(char times[5][5]){
    request.clientpid = getpid();
    request.ac = GET_TIMES;
    request.movieTimes = times;
    sendRequest();
}

void
reserveSeat(char* id, char* time, int n){
    request.clientpid = getpid();
    request.ac = RESERVE_SEAT;
    strcpy(request.movieID, id);
    strcpy(request.times, time);
    request.cant_seats = n;
    sendRequest();
}
