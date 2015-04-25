#ifndef _ipc_
#define _ipc_
#include "common.h"
typedef enum {RESERVE_SEAT , SHOW_MOVIES, CHECK_SEATS} action;

typedef struct {
	long clientpid;
	action ac;
	char movieID[3];
	char times[5];
	int cant_seats; 
} Request;

typedef struct 
{
	int value;
	List_Movies list;

}Response;


void executeRequest(Request r, Response * response);

#endif
