#ifndef _ipc_
#define _ipc_
#include "../database/src/db.h"

typedef enum {RESERVE_SEAT , GET_MOVIES, CHECK_SEATS, GET_TIMES} action;


typedef struct{
	Movie movies_list[CANT_MOVIES];
}List_Movies;

typedef struct {
	unsigned long clientpid;
	action ac;
	char movieID[3];
	char times[5];
	int cant_seats; 
	char movieTimes[5][5];
}Request;

typedef struct 
{
	int value;
	List_Movies list;
	char movieTimes[5][5];
}Response;


void executeRequest(Request r, Response* response);

#endif
