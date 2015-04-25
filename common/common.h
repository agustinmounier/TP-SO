#ifndef _common_
#define _common_

#include "ipc.h"
#define CANT_COMMANDS 3
#define CANT_MOVIES 10


void execute_input(char * input);

void show_movies();

int getCantMovies();

void show_seats(char * movie, char * time);

void executeRequest(Request r, Response * response);
#endif
