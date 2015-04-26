#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "mutual.h"
#include "../../common/common.h"
#include "../../common/ipc.h"
 
static Request *req;
static Response *resp;

void initialize(void){
    req = (Request *)getmem();
    resp = malloc(sizeof(Response));
    initsemaphores();
    signal(SIGINT, onSigInt);
    return;
}

void onSigInt(int sig){
    terminateClient();
}

List_Movies getMovies(){
    enter(1);
    req->ac=GET_MOVIES;
    leave(2);
    enter(3);
    memcpy(resp, req, sizeof(Response));
    leave(1);
    return resp->list;
}

char ** getTimes(char * id){
    char** aux=malloc(sizeof(req->movieTimes));
    enter(1);
    req->ac=GET_TIMES;
    strcpy(req->movieID, id);
    leave(2);
    enter(3);
    memcpy(resp, req, sizeof(Response));
    memcpy(aux, req->movieTimes, sizeof(req->movieTimes));
    leave(1);
    return aux;
}

int getSeats(char * id, char * times){
    enter(1);
    req->ac=CHECK_SEATS;
    strcpy(req->times,times);
    strcpy(req->movieID,id);
    leave(2);
    enter(3);
    memcpy(resp, req, sizeof(Response));
    leave(1);
    return resp->value;
}

void reserveSeat(char * id, char * times, int n){
    enter(1);
    req->ac=RESERVE_SEAT;
    strcpy(req->times,times);
    strcpy(req->movieID,id);
    req->cant_seats=n;
    leave(2);
    enter(3);
    memcpy(resp, req, sizeof(Response));
    leave(1);
}

