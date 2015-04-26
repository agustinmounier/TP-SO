#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../../common/ipc.h"
#include "sockets.h"

static Request req;
static Response resp;
static char serverip[14];

void
initializeClient(){
    printf("Insert server IP to connect: ");
    scanf("%s", serverip);
}

void
communicate_with_server(void){
    struct sockaddr_in addr;
    int fd;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, serverip, &(addr.sin_addr));
    if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        printf("%s\n","Unable to create a socket" );
        return;
    if(connect(fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1)
        printf("%s\n","Unable to connect" );
        return;
    if(write(fd, &req, sizeof(Request)) != sizeof(Request))
        printf("%s\n","Couldn't write Request in socket" );
        return;
    if(read(fd, &resp, sizeof(Response)) != sizeof(Response))
        printf("%s\n","Couldn't read response from server" );
        return;

    if(close(fd) == -1){
        printf("Error closing socket");
    }
    return;
}

int
get_seats(char * id, char * times){
    req.ac=CHECK_SEATS;
    strcpy(req.times,times);
    strcpy(req.movieID,id);
    communicate_with_server();
    return resp.value;
}


void
reserve_seats(char * id, char * times,int n){
    req.ac=RESERVE_SEAT;
    strcpy(req.times,times);
    strcpy(req.movieID,id);
    req.cant_seats=n;
    communicate_with_server();
    return ;
}

List_Movies
get_movies(){
    req.ac=GET_MOVIES;
    communicate_with_server();
    return resp.list;
}
