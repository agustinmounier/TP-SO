#ifndef _db_
#define _db_

#define CANT_MOVIES 5
#define CANT_TIMES 5
#define MOVIES_PATH "./database/db/movies_list"
#define MOVIE_PATH "./database/db/%s"


typedef struct {
	char id[3];
	char name[20];
} Movie; 

#endif