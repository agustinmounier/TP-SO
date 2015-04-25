#ifndef _fifo_
#define _fifo_

#include "../../common/ipc.h"

#define FIFO_PATH_LENGTH 30
#define FIFO_CLIENT_PATH "/tmp/fifo_pid.%ld"
#define FIFO_SERVER_PATH "/tmp/fifo_server"

void initialize(void);

void terminateClient(void);

void onSigInt(int sig);

void sendRequest(void);

int getSeats(char * movieId, char * movieTime);

List_Movies getMovies(void);

void getTimes(char times[5][5]);

void reserveSeat(char* id, char* time, int n);

void initializeServer(void);

void terminateServer(void);
#endif