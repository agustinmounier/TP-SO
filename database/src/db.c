#include <stdlib.h>
#include <stdio.h>
#include "db.h"
#include "../../common/common.h"

int
main(void){

	Movie movies[CANT_MOVIES] = {
		{1, "Hangover"},
		{2, "Pulp Fiction"},
		{3, "Inception"}, 
		{4, "Fast and Furious 7"},
		{5, "Crank"}
	};

	FILE * file = fopen(MOVIES_PATH, "wb");
	if ( file == NULL ){
            printf("error while creating movie_list file\n");
            return 0;
    }

	if( fwrite(&movies, sizeof(Movie), CANT_MOVIES, file) != CANT_MOVIES){
            printf("Error while writing movie_list file\n");
            return 0;
	}
	fclose(file);

	get_movies();
	
    printf("abrio.\n");

    return 0;
}

