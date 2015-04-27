#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include "../../common/ipc.h"
#include "sockets.h"

#define PORT 3550         

int fd;       
Response response;
Request request;  
struct hostent *he;         
struct sockaddr_in server;  
char server_ip[16];

struct in_addr ipv4addr;


int
initialize(void) {
   char c;
   printf("Server ip address: ");
   fflush(stdout);

   scanf("%s", server_ip);
   while((c = getchar()) != '\n' && c != EOF);

   inet_pton(AF_INET, server_ip, &ipv4addr);

   if ((he=gethostbyaddr(&ipv4addr, sizeof(ipv4addr), AF_INET))==NULL){       
      printf("gethostbyaddr() error\n");
      exit(-1);
   }

   server.sin_family = AF_INET;
   server.sin_port = htons(PORT); 
   server.sin_addr = *((struct in_addr *)he->h_addr);  
   bzero(&(server.sin_zero),8); 

}

void
sendRequest(void){

   if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){  
      printf("socket() error\n");
      exit(-1);
   }

   if(connect(fd, (struct sockaddr *)&server,
      sizeof(struct sockaddr))==-1){ 
      printf("connect() error\n");
      exit(-1);
   }

   if(send(fd, &request, sizeof(request), 0) == -1){
      printf("Error en send() \n");
      exit(-1);
   }

   if ((recv(fd, &response, sizeof(Response), 0)) == -1){  
      printf("Error en recv() \n");
      exit(-1);
   }

   close(fd);  

}

int
getSeats(char * movieId, char * movieTime){

   request.ac = CHECK_SEATS;
   strcpy(request.movieID, movieId);
   strcpy(request.times, movieTime);
   sendRequest();
   return response.value;
}

List_Movies
getMovies(void){
    request.ac = GET_MOVIES;
    sendRequest();
    return response.list;
}

void
getTimes(char times[5][5]){
    int i = 0;
    request.ac = GET_TIMES;
    sendRequest();
    for(; i < 5; i++)
        strcpy(times[i], response.movieTimes[i]);

}

void
reserveSeat(char* id, char* time, int n){
    request.ac = RESERVE_SEAT;
    strcpy(request.movieID, id);
    strcpy(request.times, time);
    request.cant_seats = n;
    sendRequest();
}


