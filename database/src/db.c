#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db.h"
#include "../../common/common.h"

int
main(void){

	Movie movies[CANT_MOVIES] = {
		{"01", "Hangover"},
		{"02", "Pulp Fiction"},
		{"03", "Inception"}, 
		{"04", "Fast and Furious 7"},
		{"05", "Crank"},
		{"06", "The day after tomorrow"},
		{"07", "Ocean 13"},
		{"08", "Atlantis"},
		{"09", "Big Eyes"},
		{"10", "Home"}
	};

	char times[5][5]={"0900", "1200", "1700", "2100", "0100"};
	char times2[5][5];

	Movie moviesRead[CANT_MOVIES];

	int i = 0;
	int j = 0;
	int seats = 40;
	char moviePath[30];
	char movieID[20];

	FILE * file = fopen(MOVIES_PATH, "wb+");
	FILE * file2 = fopen(TIMES, "wb+");
	
	if ( file == NULL ){
            printf("error while creating movie_list file fdsafdsa\n");
            return 0;
    }

	if( fwrite(&movies, sizeof(Movie), CANT_MOVIES, file) != CANT_MOVIES){
            printf("Error while writing movie_list file\n");
            return 0;
	}
	fclose(file);

	if ( file2 == NULL ){
            printf("error while creating times file\n");
            return 0;
    }

	if( fwrite(times, 5, CANT_TIMES, file2) != CANT_TIMES){
            printf("Error while writing times file\n");
            return 0;
	}
	fclose(file2);

	for(; i < CANT_MOVIES; i++){
		for(j = 0; j < CANT_TIMES; j++){


			strcpy(movieID, movies[i].id);
            strcat(movieID, "-");
            strcat(movieID, times[j]);

			sprintf(moviePath, MOVIE_PATH, movieID);

			file = fopen(moviePath, "wb");
			fwrite(&seats, sizeof(int), 1, file);
			fclose(file);
		}
		
	}

    return 0;
}

