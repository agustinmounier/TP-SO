#ifndef _sockets_
#define _sockets_

int initialize(void);
void sendRequest(void);
int getSeats(char * movieId, char * movieTime);
List_Movies getMovies(void);
void getTimes(char times[5][5]);
void reserveSeat(char* id, char* time, int n);

#endif