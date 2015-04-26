#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../../common/ipc.h"
#include "../../common/common.h"
#include "../../common/dbAccess.h"
#include "mutual.h"

int main(void){
	Request *req;
	Response *resp;
	FILE *file = fopen("/tmp/semshm", "wb");
	if( file == NULL ){
		fatal("fopen");
	}
	fclose(file);
	req = (Request *)getmem();
	memset(req, 0, SIZE);
	resp = (Response *)req;
	initsemaphores();
	signal(SIGINT, onSigInt);
	for(;;){
		enter(2);
		printf("movie code %d",req->movieID);
		executeRequest(*req, resp);
		leave(3);
	}
	return 0;
}

void onSigInt(int sig){
	terminateServer();
}