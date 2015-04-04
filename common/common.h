#ifndef _common_
#define _common_

#include "../database/src/db.h"
#define CANT_COMMANDS 1


void execute_input(char * input);

void show_movies();

void get_movies(Movie * moviesRead);

#endif