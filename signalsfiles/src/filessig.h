#ifndef _filessig_
#define _filessig_

#define CLIENT_FILE_PATH "../tmp/client_%ld"
#define SERVER_PID_FILE "./server_pid"

void user1_handler(int sig, siginfo_t *info, void *ptr);
void dealWithClient(unsigned long pid);
void readClientMessage(unsigned long pid);
void initialize(void);
List_Movies getMovies(void);
void getTimes(char times[5][5]);
void user2_handler(int s);
int getSeats(char * id, char * times);
void reserveSeat(char * id, char * times,int n);
void create_request(void);
void notify_server(void);
void communicate_with_server(void);

#endif