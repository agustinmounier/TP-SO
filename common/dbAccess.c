#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "../database/src/db.h"


int
get_movies(){


	Movie moviesRead[CANT_MOVIES];
	int i = 0;

	FILE *file = fopen(MOVIES_PATH, "rb+");
    if( file == NULL ){
        printf("Invalid movie code: not found in database\n");
        return 0;
    }

    fread(moviesRead, sizeof(Movie), CANT_MOVIES, file);

    for(; i < CANT_MOVIES; i++){
    	printf("%s\n", moviesRead[i].name);
    }
    return i;

}