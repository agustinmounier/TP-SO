#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "common.h"
#include "../database/src/db.h"

static struct flock fl = {.l_start = 0, .l_whence = SEEK_SET, .l_len = 0};

List_Movies
get_movies(){
	int fd;
	List_Movies list;
	FILE *file = fopen(MOVIES_PATH, "rb+");
    if( file == NULL ){
        printf("Invalid movie code: not found in database\n");
        return list;
    }
	fd=fileno(file);
	if( rdlockFile(fd) == -1){
		printf("Impossible to show movies.");
		return list;
	}

    fread(list.movies_list, sizeof(Movie), CANT_MOVIES, file);
    unlockFile(fd);
	fclose(file);
	return list;
}

void
get_moviePath(char* moviePath,char* id, char* time){

	char movieID[20];
	strcpy(movieID, id);
    strcat(movieID, "-");
    strcat(movieID, time);

	
	sprintf(moviePath, MOVIE_PATH, movieID);
}
int
get_seats(char* id, char* time){
	FILE *file;
	int seats,fd;
	char moviePath[40];
	get_moviePath(moviePath,id,time);
	file=fopen(moviePath, "rb+");
	if(file==NULL){
		printf("The entered data doesn´t correspond to an available screening. \n");
		return -1;
	}
	fd=fileno(file);
	if( rdlockFile(fd) == -1){
		printf("Reservation could not be completed. Please, try again later.");
		return -1;
	}
	fread(&seats, sizeof(int), 1, file);
	unlockFile(fd);
	fclose(file);
	return seats;
}

void
reserve_seat(char* id, char* time, int n){
	FILE * file;
	int seats, fd;
	char moviePath[40];
	get_moviePath(moviePath,id,time);

	
	file=fopen(moviePath, "rb+");
	if(file==NULL){
		printf("The entered data doesn´t correspond to an available screening.hhh \n");
		return;
	}
	fd=fileno(file);

	if( wrlockFile(fd) == -1){
		printf("It was not possible to make the reservation. Try again later.\n");
		return;
	}
	fread(&seats, sizeof(int), 1, file);

	if( seats < n ){
		printf("Sorry, no seats available.\n");
		return;
	}
	
	seats=seats-n;
	printf("seats: %d\n", seats);
	fseek(file, 0, SEEK_SET);
	fwrite(&seats, sizeof(int), 1, file);
	unlockFile(fd);
	fclose(file);
	printf("The seats have been successfully reserved.\n");
	return;
}

int
rdlockFile(int fd){
	fl.l_type = F_RDLCK;
	return fcntl(fd, F_SETLKW, &fl);
}

int
wrlockFile(int fd){
	fl.l_type = F_WRLCK;
	return fcntl(fd, F_SETLKW, &fl);
}

int
unlockFile(int fd){
	fl.l_type = F_UNLCK;
	return fcntl(fd, F_SETLKW, &fl);
}

void get_times(char times[5][5]){
	int i = 0;

	FILE *file = fopen(TIMES, "rb+");
    if( file == NULL ){
        printf("Invalid time: not found in database\n");
        return ;
    }

    fread(times, 5, CANT_TIMES, file);

	fclose(file);
}

