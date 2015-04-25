#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>


#define PORT 3550 /* El puerto que será abierto */
#define BACKLOG 2 /* El número de conexiones permitidas */
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
    printf("Unable to do complete the listen.\n");
      exit(-1);
   	}

   	while(1) {
      sin_size=sizeof(struct sockaddr_in);
      if ((fd2 = accept(fd,(struct sockaddr *)&client,&sin_size))==-1) {
         printf("error en accept()\n");
         exit(-1);
      }

      printf("Se obtuvo una conexión desde %s\n",
             inet_ntoa(client.sin_addr) ); 
      /* que mostrará la IP del cliente */

      send(fd2,"Bienvenido a mi servidor.\n",22,0); 
      /* que enviará el mensaje de bienvenida al cliente */

      close(fd2); /* cierra fd2 */
   }
}
