#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "../../common/ipc.h"
#include "../../common/common.h"
#include "filessig.h"

static Request req;
static Response resp;
struct sigaction sig;


int main(){
	printf("%s", "The server is running...");
	long pid = (long)getpid();
	FILE* file= fopen(SERVER_PID_FILE, "wb");
	if(file==NULL){
		printf("%s\n","The server file couldn't be opened.");
		return -1;
	}
	if(fwrite(&pid, sizeof(unsigned long), 1, file)==0){
		printf("%s\n", "Not able to write the server pid.");
		return -1;
	}
	fclose(file);
	signal(SIGINT, onSigInt);

	sigemptyset(&sig.sa_mask);
	    sig.sa_flags = 0;
	    sig.sa_handler = user1_handler;
	    sigaction(SIGUSR1, &sig, NULL);
	    while(1){

	    }
	    return 0;
}

void
user1_handler(int sig, siginfo_t *info, void *ptr){
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset,SIGUSR1);
	if(sigprocmask(SIG_BLOCK,&sigset, NULL)==-1){
		write(0,"Couln't block signals",22);
		return;
	}
	switch(fork()){
		case -1: {
				write(0, "Unable to fork process",22);
				break;
				 }
		case 0: {
				dealWithClient();
				break;
		}
		default: {
			if(sigprocmask(SIG_UNBLOCK,&sigset, NULL)==-1){
				write(0,"Couln't unblock signals",24);
				return;
			}
		}		
	}
	return;
	}

	void
	dealWithClient(){
		readClientMessage();
	}

	void
	readClientMessage(){
		char clientFile[50];
		DIR *dirp;
		FILE *file;
		struct dirent *direntp;
		char* name;
		if((dirp = opendir(CA_PATH)) == NULL){
			exit(-1);
		}
		while((direntp =readdir(dirp))!=NULL && direntp->d_name[0] == '.'){
		}
		strcpy(name,direntp->d_name);
		strcpy(clientFile, CA_PATH);
		strcat(clientFile,"/");
		strcat(clientFile, name);
		file=fopen(clientFile,"rb+");
		if(file == NULL){
			printf("Error while opening %s file\n",clientFile);
			exit(EXIT_FAILURE);
		}
		if(fread(&req,sizeof(Request),1,file) == -1){
			printf("Error while reading from %s file\n",clientFile);
			exit(EXIT_FAILURE);
		}
		fclose(file);
		if(remove(clientFile) == -1){
			printf("Error while removing %s file\n",clientFile);
			exit(EXIT_FAILURE);
		}
		closedir(dirp);
		executeRequest(req,&resp);
		strcpy(clientFile, SA_PATH);
		strcat(clientFile,"/");
		strcat(clientFile, name);
		file=fopen(clientFile, "wb+");
		if(file==NULL){
			printf("%s\n","Unable to open file from client");
			return;
		}
		if(fwrite(&resp,sizeof(Response),1,file)==-1){
			printf("%s\n","Unable to write file" );
			return;
		}
		fclose(file);
		kill(atoi(name), SIGUSR2);
}

void 
onSigInt(int sig) {
	if(remove(SERVER_PID_FILE)== -1){
		printf("%s\n","Couldn't remove the server pid file");
	}
	exit(-1);
}
