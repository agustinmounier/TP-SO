#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./common.h"

int
main(void){
	char input[30];
	printf("Welcome to SO-cinema.\n");
	while(1){
		printf("Type the desired option: \n");
		printf("ShowMovies, \n");
		fgets(input, 30, stdin);
		execute_input(input);
	}
}

void
execute_input(char * input){
	char cmd[15];
	char id[3];
	char times[5];
	int i;
	int cant;
	for(i=0; i<15 && input[i]!= '\0' && input[i]!=' ';i++){
		cmd[i]=input[i];
	}
	if(strcmp(cmd, "showmovies")==0){
		show_movies();
		return;
	}

	if(strcmp(cmd,"reserveseat")==0){
		for(i=0;i<2 && input+(12+i)!='\0' && input[12+i]!=' ';i++){
			id[i]=*(input+(12+i));
		}
		if(i!=2|| input[14] !=' '){
			printf("%s\n", "Not valid arguments.");
			return;
		}
		for(i=0;i<4 && input+(15+i) !='\0' && input[15+i]!=' ';i++){
			times[i]=*(input+(15+i));
		}
		if(i!=4 || input[19] != ' '){
			printf("%s\n", "Not valid arguments.");
			return;
		}
		times[4]='\0';
		cant=atoi(input+20);
		if(cant==0){
			printf("%s\n","Not valid arguments" );
			return;
		}
		reserve_seat(id,times,cant);
		return;
	}
	if(strcmp(cmd, "checkseats")==0){
		for(i=0;i<2 && input+(11+i)!='\0' && input[11+i]!=' ';i++){
			id[i]=*(input+(11+i));
		}
		if(i!=2|| input[13] !=' '){
			printf("%s\n", "Not valid arguments.");
			return;
		}
		for(i=0;i<4 && input+(14+i) !='\0' && input[14+i]!=' ';i++){
			times[i]=*(input+(14+i));
		}
		if(i!=4){
			printf("%s\n", "Not valid arguments.");
			return;
		}
		times[4]='\0';
		show_seats(id,times);
		return;
	}
	printf("%s\n", "Invalid option.\n");

	
	/*char commands[3][15]={"showmovies", "reserveseat", "checkseats"};
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
	}*/
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