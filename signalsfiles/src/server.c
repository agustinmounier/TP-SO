#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "../../common/ipc.h"
#include "../../common/common.h"
#include "filessig.h"

static Request req;
static Response resp;
struct sigaction sig;


void main(){
	long pid = (long)getpid();
	FILE* file= fopen(SERVER_PID_FILE, "wb");

	if(file==NULL){
		printf("%s\n","The server file couldn't be opened.");
		return -1;
	}
	if(fwrite(&pid, sizeof(long), 1, file)==0){
		printf("%s\n", "Not able to write the server pid.");
		return -1;
	}
	fclose(file);
	//signal(SIGINT, onSigInt);

	sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = user1_handler;
    sigaction(SIGUSR1, &sig, NULL);
    while(1){

    }
}

void
user1_handler(int sig, siginfo_t *info, void *ptr){
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset,SIGUSR1);
	if(sigpromask(SIG_BLOCK,&sigset, NULL)==-1){
		write(0,"Couln't block signals",22);
		return;
	}
	switch(fork()){
		case -1: {
				write(0, "Unable to fork process",22);
				return;
				 }
		case 0: {
				dealWithClient(info->si_pid);
		}
		default: {
			if(sigpromask(SIG_UNBLOCK,&sigset, NULL)==-1){
				write(0,"Couln't unblock signals",24);
				return;
			}
		}		
	}
}

void
dealWithClient(unsigned long pid){
	readClientMessage(pid);
}

void
readClientMessage(unsigned long pid){
	Request req;
	Response resp;
	char clientFile[40];
	sprintf(clientFile,CLIENT_FILE_PATH,pid);
	File* file= fopen(clientFile, "rb");
	if(file==NULL){
		printf("%s\n","Unable to open file from client");
		return;
	}
	if(fread(&req,sizeof(Request),1,file)==0){
		printf("%s\n","Unable to read file" );
		return;
	}
	fclose();
	excecuteRequest(req,res);
	File* file= fopen(clientFile, "rb");
	if(file==NULL){
		printf("%s\n","Unable to open file from client");
		return;
	}
	if(fwrite(&resp,sizeof(Reponse),1,file)==0){
		printf("%s\n","Unable to read file" );
		return;
	}
	kill(pid, SIGUSR2);
}

/*void 
onSigInt(int sig) {
	if(remove(SERVER_PID_FILE)== -1){
		printf("%s\n","Couldn't remove the server pid file");
	}
	return;
}*/
