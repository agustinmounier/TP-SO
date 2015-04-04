#include <stdlib.h>
#include <stdio.h>
#include "../common.h"

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
	for(; cmd < CANT_COMMANDS; cmd++){
		if(strcmp(input, commands[cmd]) == 0)
			break;
	}

	switch(cmd){
		case 0: show_movies();
				break;
		default: printf("Invalid option. \n");


	}
}

void
show_movies(){
	printf("Pulp Fiction.\n");
	printf("The Wolf of Wall Street. \n");
	printf("Inception. \n");
}