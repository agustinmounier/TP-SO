#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../common/ipc.h"
#include "sockets.h"

int
main(void){
    int fd, fd2;
   	struct sockaddr_in server; 
   	struct sockaddr_in client; 
  	int sin_size;
   	if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {  
      	printf("Not able to open a new Socket. Try again later.\n");
		return -1;
   	}
   	server.sin_family = AF_INET;  
   	server.sin_port = htons(PORT);
   	server.sin_addr.s_addr = INADDR_ANY;bzero(&(server.sin_zero),8);
   	if(bind(fd,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1) {
      	printf("Unable to do the binding. \n");
        exit(-1);
    }     
    printf("Unable to complete the listen.\n");
      exit(-1);

   	while(1){
      sin_size=sizeof(struct sockaddr_in);
       if ((fd2 = accept(fd,(struct sockaddr *)&client,&sin_size))==-1) {
         printf("error en accept()\n");
         exit(-1);
      }
      switch(fork()){
        case -1: 
          printf("%s\n", "Couldn't create child to attend client." );
          break;
        case 0:
          dealWithClient(fd2);
          break;
        default:
          close(fd2);
          break;
      }
        
   }
}

void
dealWithClient(int fd){
    Request req;
    Response resp;
    if(readn(fd, &req, sizeof(Request)) != sizeof(Request)) {
            close(fd);
            return;
    }
    executeRequest(req, &resp);
    if (writen(fd, &resp, sizeof(Response)) != sizeof(Response))
          printf("%s\n","Couldn't write Response" );

    if(close(fd) == -1) /* Close connection */
            printf("Couldn't close Socket\n");
}
