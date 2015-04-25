#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "msqueue.h"

RequestMsg reqMsg;
ResponseMsg resMsg;
int msqidRcv, msqidSnd;
 
void
initialize(void){
    signal(SIGINT, onSigInt);
    reqMsg.mtype = (long)getpid();

	msqidRcv = msgget(SERVER_KEY, IPC_CREAT | 0666); 
	if(msqidRcv == -1)
        printf("Error when creating msqueue rcv.\n");

	msqidSnd = msgget(CLIENTS_KEY, IPC_CREAT | 0666); 
	if(msqidSnd == -1)
        printf("Error when creating msqueue snd.\n");
}

void
onSigInt(int sig){
    terminateClient();
}
 
void
terminateClient(void){
	exit(EXIT_SUCCESS);
}

void
sendMsg(void){
    if(msgsnd(msqidSnd, (char *)&reqMsg, sizeof(RequestMsg), 0) == -1)
        printf("Error when sending msqueue snd.\n");
    if((msgrcv(msqidRcv, (char *)&resMsg, sizeof(resMsg), getpid(), 0)) == -1)
        printf("Error when recieving msqueue rcv.\n");
}

int
getSeats(char * movieId, char * movieTime){

	reqMsg.req.ac = CHECK_SEATS;
	strcpy(reqMsg.req.movieID, movieId);
	strcpy(reqMsg.req.times, movieTime);
	sendMsg();
	return resMsg.resp.value;
}

List_Movies
getMovies(void){
    reqMsg.req.ac = GET_MOVIES;
    sendMsg();
    return resMsg.resp.list;
}

void
getTimes(char times[5][5]){
    reqMsg.req.ac = GET_TIMES;
    //reqMsg.req.movieTimes = times;
    sendMsg();
}

void
reserveSeat(char* id, char* time, int n){
    reqMsg.req.ac = RESERVE_SEAT;
    strcpy(reqMsg.req.movieID, id);
    strcpy(reqMsg.req.times, time);
    reqMsg.req.cant_seats = n;
    sendMsg();
}

