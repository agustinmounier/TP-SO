#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../../common/ipc.h"
#include "../../common/common.h"
#include "mutual.h"

int main(void){
	Request *req;
	Response *resp;
	FILE *file = fopen("/tmp/semshm", "wb");
	if( file == NULL ){
		printf("Imposible crear memoria compartida");
	}
	fclose(file);
	req = (Request *)getmem();
	resp = (Response *)req;
	initsemaphores();
	signal(SIGINT, onSigInt);
	for(;;){
		enter(2);
		printf("movie code %d",atoi(req->movieID));
		executeRequest(*req, resp);
		leave(3);
	}
	return 0;
}

void onSigInt(int sig){
	terminateServer();
}