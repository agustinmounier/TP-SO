#ifndef _ipc_
#define _ipc_
typedef enum {RESERVE_SEAT , SHOW_MOVIES, CHECk_SEATS} action;

typedef struct {
	long clientpid;
	action ac;
	char[3] movieID;
	char[5] times;
	int cant_seats; 
} Request;

typedef struct 
{
	int value;
	
}Response;
#endif