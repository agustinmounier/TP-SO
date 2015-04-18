#ifndef _db_
#define _db_

#define CANT_MOVIES 10
#define CANT_TIMES 5
#define MOVIES_PATH "./database/db/movies_list"
#define MOVIE_PATH "./database/db/%s"
#define TIMES "./database/db/times"


typedef struct {
	char id[3];
	char name[30];
} Movie; 

#endif
