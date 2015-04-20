#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "../common/ipc.h"
#include "filessig.h"

static Request req;
static Response resp;
static char clientFile[40];

void initialize(){
	req.clientpid=getpid();
	sprintf(clientFile,CLIENT_FILE_PATH,(long)getpid());
	signal(SIGINT, onSigInt);
}
List_Movies
get_movies(){
    req.action=SHOW_MOVIES;
    communicate_with_server();
    return resp.movies_list;
}

int get_seats(char * id, char * times){
	req.action=CHECK_SEATS;
	req.times=times;
	req.movieID=id;
	communicate_with_server();
	return resp.value;
}

void
onSigInt(){
	terminateClient();
}
void
reserve_seats(char * id, char * time){
	req.action=RESERVE_SEAT;
	req.times=times;
	req.movieID=id;
	communicate_with_server();
	return ;
}
void
terminateClient(void){
    int exit_status = EXIT_SUCCESS;
    exit(exit_status);
}

void
create_request(){
	FILE *file=fopen(clientFile,"wb+");
	if(file==NULL){
		printf("Not able to create file.");
		return;
	}
	if(write(&req,sizeof(Request),1, file)==-1){
		printf("Not able to write in clientfile.");
		return;
	}
	fclose();
}

void
communicate_with_server(){
	create_request();
	notify_server();
}


