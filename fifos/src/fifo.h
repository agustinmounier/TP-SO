#ifndef _fifo_
#define _fifo_

#define FIFO_PATH_LENGTH 30
#define FIFO_CLIENT_PATH "/tmp/fifo_pid.%ld"
#define FIFO_SERVER_PATH "/tmp/fifo_server"

void initialize(void);
void terminateClient(void);
void onSigInt(int sig);
void sendRequest(void);
int check_seats(char * movieId, char * movieTime);
void initializeServer(void);
void terminateServer(void);


#endif