#ifndef _common_
#define _common_

#include "../database/src/db.h"
#define CANT_COMMANDS 3


void execute_input(char * input);

void show_movies();

void get_movies(Movie * moviesRead, int movies);

int get_seats(char * id, char * time);

void get_moviePath(char* moviePath,char* id, char* time);

void reserve_seat( char* id, char* time, int n);

int rdlockFile(int fd);

int wrlockFile(int fd);

int unlockFile(int fd);

void get_times(char times[5][5]);

int getCantMovies();

void show_seats(char * movie, char * time);

#endif
