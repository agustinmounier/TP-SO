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

List_Movies get_movies(){
    req.ac=SHOW_MOVIES;
    communicate_with_server();
    return resp.list;
}

int get_seats(char * id, char * times){
    enter(1);
    req->action=CHECK_SEATS;
    req->movieID=id;
    req->times=times;
    leave(2);
    enter(3);
    memcpy(resp, req, sizeof(Response));
    leave(1);
    return resp->value;
}

void reserve_seats(char * id, char * times, int n){
    enter(1);
    req->action=RESERVE_SEAT;
    req->movieID=id;
    req->times=times;
    req->cant_seats=n;
    leave(2);
    enter(3);
    memcpy(resp, req, sizeof(Response));
    leave(1);
}

