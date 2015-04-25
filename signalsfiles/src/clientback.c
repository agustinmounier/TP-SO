#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "../../common/ipc.h"
#include "../../common/common.h"
#include "filessig.h"

static Request req;
static Response resp;
static char clientFile[40];

void initialize(){
	req.clientpid=getpid();
	sprintf(clientFile,CLIENT_FILE_PATH,(long)getpid());
	sigaction(SIGUSR2, user2_handler,0);
	//signal(SIGINT, onSigInt);
}

List_Movies
get_movies(){
    req.ac=SHOW_MOVIES;
    communicate_with_server();
    return resp.list;
}

int
get_seats(char * id, char * times){
	req.ac=CHECK_SEATS;
	strcpy(req.times,times);
	strcpy(req.movieID,id);
	communicate_with_server();
	return resp.value;
}

/*void
onSigInt(){
	sprintf(clientFile,CLIENT_FILE_PATH,(long) getpid());
    if( remove(clientFile) == -1 ) {
    	printf("%s\n", "Couldn't remove the client file" );
    }
    return;
}*/


void
reserve_seats(char * id, char * times,int n){
	req.ac=RESERVE_SEAT;
	strcpy(req.times,times);
	strcpy(req.movieID,id);
	req.cant_seats=n;
	communicate_with_server();
	return ;
}

void
create_request(){
	FILE *file=fopen(clientFile,"wb+");
	if(file==NULL){
		printf("Not able to create file.");
		return;
	}
	if(fwrite(&req,sizeof(Request),1, file)==-1){
		printf("Not able to write in clientfile.");
		return;
	}
	fclose(file);
}

void 
notify_server(){
	FILE *file=fopen(SERVER_PID_FILE,"rb");
	unsigned long pid_s;
	if(file==NULL){
		printf("%s\n","There is no server available" );
		return;
	}
	if(fread(&pid_s,sizeof(pid_s), 1,file)==0){
		printf("%s\n","Couldn't read the server file" );
		return;
	}
	kill(pid_s, SIGUSR1);
	return;
}

void
communicate_with_server(){
	create_request();
	notify_server();
}


