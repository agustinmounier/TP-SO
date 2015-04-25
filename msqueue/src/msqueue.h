#ifndef _msqueue_
#define _msqueue_

#include "../../common/ipc.h"

#define SERVER_KEY ftok("/tmp/mqueues-server", 2)
#define CLIENTS_KEY ftok("/tmp/mqueues-clients", 1)

typedef struct {
    long mtype;
    Request req;
} RequestMsg;

typedef struct {
    long mtype;
    Response resp;
} ResponseMsg;

void initializeServer(void);
void terminateServer(void);
void onSigInt(int sig);
void initialize(void);
void terminateClient(void);
void sendMsg(void);
int getSeats(char * movieId, char * movieTime);
List_Movies getMovies(void);
void getTimes(char times[5][5]);
void reserveSeat(char* id, char* time, int n);


#endif