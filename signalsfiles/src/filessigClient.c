#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../common/ipc.h"
#include "../../common/common.h"
#include "filessig.h"

static Request req;
static Response resp;
static char clientFile[40];
static struct sigaction sig;

void initialize(void){
	req.clientpid=(unsigned long)getpid();
	printf("client pid %d\n", getpid());
	sprintf(clientFile,CLIENT_FILE_PATH,(unsigned long)getpid());
	sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = user2_handler;
	sigaction(SIGUSR2, &sig,0);
	//signal(SIGINT, onSigInt);
}

List_Movies
getMovies(void){
    req.ac=GET_MOVIES;
    communicate_with_server();
    pause();
    return resp.list;
}

void
getTimes(char times[5][5]){
	int i=0;
	req.ac=GET_TIMES;
	communicate_with_server();
	pause();
	for(; i < 5; i++)
        strcpy(times[i], resp.movieTimes[i]);
	return;
}

void
user2_handler(int s){
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,SIGUSR1);
    sigaddset(&sigset,SIGUSR2);

	if(sigprocmask(SIG_BLOCK,&sigset, NULL)==-1){
		write(0,"Couldn't block signals",22);
		return;
	}

    FILE * file = fopen(clientFile, "rb+");
    if(file == NULL){
    	write(0,"Couldn't open file",18);
		return;
    }
    if(fread(&resp, sizeof(Response), 1, file) == -1){
    	write(0,"Couldn't read file",18);
		return;
    }
    fclose(file);

    if( sigprocmask(SIG_UNBLOCK, &sigset, NULL) == -1 ){
        write(0,"Couldn't unblock signals",24);
		return;
    }
}

int
getSeats(char * id, char * times){
	req.ac=CHECK_SEATS;
	strcpy(req.times,times);
	strcpy(req.movieID,id);
	communicate_with_server();
	pause();
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
reserveSeat(char * id, char * times,int n){
	req.ac=RESERVE_SEAT;
	strcpy(req.times,times);
	strcpy(req.movieID,id);
	req.cant_seats=n;
	communicate_with_server();
	pause();
	return ;
}

void
create_request(void){
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
notify_server(void){
	FILE *file=fopen(SERVER_PID_FILE,"rb+");
	unsigned long pid_s;
	if(file==NULL){
		printf("%s\n","There is no server available" );
		return;
	}
	if(fread(&pid_s,sizeof(pid_s), 1,file)==0){
		printf("%s\n","Couldn't read the server file" );
		return;
	}
	fclose(file);
	kill(pid_s, SIGUSR1);
	return;
}

void
communicate_with_server(void){
	create_request();
	notify_server();
}


