#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "../../common/ipc.h"

#define PORT 3550 
#define BACKLOG 50 

int fd, fd2; 
Request req;
Response resp;
void onSigInt(int sig);


int 
main() {

   struct sockaddr_in server; 
   struct sockaddr_in client; 
   int sin_size;

   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {  
      printf("error when creating socket\n");
      exit(-1);
   }

   server.sin_family = AF_INET;         
   server.sin_port = htons(PORT); 
   server.sin_addr.s_addr = INADDR_ANY; 
   bzero(&(server.sin_zero),8); 


   if(bind(fd,(struct sockaddr*)&server,
           sizeof(struct sockaddr))==-1) {
      printf("error in bind() \n");
      exit(-1);
   }     

   if(listen(fd,BACKLOG) == -1) {  
      printf("error in listen()\n");
      exit(-1);
   }

   signal(SIGINT, onSigInt);

   while(1) {
      sin_size = sizeof(struct sockaddr_in);
      if ((fd2 = accept(fd,(struct sockaddr *)&client,
                        &sin_size))==-1) {
         printf("error in accept()\n");
         exit(-1);
      }
      recv(fd2, &req, sizeof(Request), 0);
      executeRequest(req, &resp);
      send(fd2, &resp, sizeof(resp), 0); 
      close(fd2);
   }
}

void
onSigInt(int sig){
    int exit_status = EXIT_SUCCESS;
    if( fd != -1 && close(fd) != 0 ) 
      exit_status = EXIT_FAILURE;
    if( fd2 != -1 && close(fd2) != 0 ) 
      exit_status = EXIT_FAILURE;
    exit(exit_status);
}
