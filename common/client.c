#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./common.h"
#include "../fcntl/src/clientBack.h"


int
main(void){
	char input[30];
	int i;
	printf("\n\x1b[31mWelcome to SO-cinema.\x1b[0m\n\n");
	initialize();
	while(1){
		printf("\n");
		printf("What would you like to do? Type the desired option: \n");
		printf("ShowMovies, ReserveSeat, CheckSeats, Help \n");
		fgets(input, 40, stdin);
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

	for(i=0; i<15 && input[i]!= '\0' && input[i]!=' ' && input[i]!= '\n';i++){
		cmd[i]=input[i];
	}
	cmd[i] = '\0';

	if(strcmp(cmd, "ShowMovies")==0){
		show_movies();
		return;
	}
	if(strcmp(cmd,"ReserveSeat")==0){
		for(i=0;i<2 && input+(12+i)!='\0' && input[12+i]!=' ';i++){
			id[i]=*(input+(12+i));
		}
		id[2] = '\0'; 
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
		if(getSeats(id, times) < cant){
			printf("The are not enough seats available.\n", cant);
			return;
		}
		reserveSeat(id,times,cant);
		return;
	}
	if(strcmp(cmd, "CheckSeats")==0){
		for(i=0;i<2 && input+(11+i)!='\0' && input[11+i]!=' ';i++){
			id[i]=*(input+(11+i));
		}

		id[2] = '\0'; 
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
	if(strcmp(cmd, "Help")==0){
		printf("ShowMovies: displays a list of all the movies available.\n\n");
		printf("CheckSeats: indicates how many seats left are available for that movie. You will have to indicate the ID and time of the movie.\n");
		printf("	Example: 'CheckSeats 09 2100' will indicate the number of seats left for the movie which has 09 as id and airs at 2100\n\n");
		printf("ReserveSeats: reserves the seats for a specific movie at a specific time. You will have to indicate the id and time of the movie as well as the amount of seats to reserve.\n");
		printf("	Example: 'ReserveSeats 02 2100 5' will reserve 5 seats for the movie which has id 02 at 2100");
	}
	printf("%s\n", "Invalid option.\n");
}

void
show_movies(){
	List_Movies list;
	char times[5][5];
	int i=0;
	list=getMovies();
	getTimes(times);
	
	for(; i<CANT_MOVIES; i++){
		printf("%s - %s\n", list.movies_list[i].id, list.movies_list[i].name);
	}
	printf("\n");
	printf("Available times:\n");
	for(i=0; i<5; i++){
		printf("%s     ", times[i]);
	}
	printf("\n");
}

void
show_seats(char * movie, char * movietime){
	int seats;
	seats=getSeats(movie, movietime);
	printf("There are %d available seats for movie id: %s\n", seats, movie );
}
