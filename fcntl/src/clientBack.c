#include <stdio.h>
#include <stdlib.h>
#include "../../common/common.h"


List_Movies
getMovies(void){
	return get_movies();
}

void
getTimes(char times[5][5]){
	get_times(times);
}

int
getSeats(char * movieId, char* movieTime){
	return get_seats(movieId, movieTime);
}

void
reserveSeat(char* id, char* time, int n){
	reserve_seat(id, time, n);
}
