#ifndef _clientBack_
#define _clientBack_

#include "../../common/common.h"

List_Movies getMovies(void);
void getTimes(char times[5][5]);
int getSeats(char * movieId, char* movieTime);

#endif
