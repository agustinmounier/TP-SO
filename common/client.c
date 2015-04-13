#include <stdlib.h>
#include <stdio.h>
#include "./common.h"

int
main(void){
	char input[15];
	printf("Welcome to SO-cinema.\n");
	while(1){
		printf("Type the desired option: \n");
		printf("ShowMovies, \n");
		scanf("%s", input);
		execute_input(input);
	}
}

void
execute_input(char * input){

	int cmd = 0;
	char commands[3][15]={"showmovies", "reserveseat", "checkseats"};
	for(; cmd < CANT_COMMANDS; cmd++){
		if(strcmp(input, commands[cmd]) == 0)
			break;
	}

	switch(cmd){
		case 0: show_movies();
				break;
		case 1: reserve_seat("01", "0900", 20);break;
		case 2: show_seats("01","0900");break;
		default: printf("Invalid option. \n");
	}
}

void
show_movies(){
	int movies=getCantMovies();
	Movie movielist[movies];
	char times[5][5];
	int i=0;

	get_movies(movielist, movies);
	get_times(times);
	
	for(; i<movies; i++){
		printf("%s - %s\n", movielist[i].id, movielist[i].name);
	}
	printf("Available times:\n");
	for(i=0; i<5; i++){
		printf("%s      ", times[i]);
	}
	printf("\n");
}

void
show_seats(char * movie, char * movietime){
	int seats;
	seats=get_seats(movie, movietime);
	printf("There are %d available seats for movie id: %s\n", seats, movie );
}