#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "../common/ipc.h"

static Request req;

List_Movies
get_movies(){
	req.clientpid=getpid();
}

int get_seats(char * id, char * time);
