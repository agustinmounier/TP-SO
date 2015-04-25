#ifndef _dbAccess_
#define _dbAccess_

#include "../ipc.h"

List_Movies get_movies();

void get_moviePath(char* moviePath,char* id, char* time);

int get_seats(char* id, char* time);

void reserve_seat(char* id, char* time, int n);

int rdlockFile(int fd);

int wrlockFile(int fd);

int unlockFile(int fd);

void get_times(char times[5][5]);

#endif