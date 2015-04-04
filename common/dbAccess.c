#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "../database/src/db.h"


void
get_movies(Movie * moviesRead){
	int i = 0;

	FILE *file = fopen(MOVIES_PATH, "rb+");
    if( file == NULL ){
        printf("Invalid movie code: not found in database\n");
        return ;
    }

    fread(moviesRead, sizeof(Movie), CANT_MOVIES, file);

    for(; i < CANT_MOVIES; i++){
    	printf("%s\n", moviesRead[i].name);
    }

}