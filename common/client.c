#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./common.h"

int
main(void){
	char input[30];
	printf("\n\x1b[31mWelcome to SO-cinema.\x1b[0m\n\n");
	while(1){
		printf("Type the desired option: \n");
		printf("ShowMovies, ReserveSeat, CheckSeats \n\n");
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
	for(i=0; i<15 && input[i]!= '\0' && input[i]!=' ' && input[i]!= '\n';i++){
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
}

void
show_movies(){
	List_Movies list;
	char times[5][5];
	int i=0;
	list=get_movies();
	get_times(times);
	
	for(; i<CANT_MOVIES; i++){
		printf("%s - %s\n", list.movies_list[i].id, list.movies_list[i].name);
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