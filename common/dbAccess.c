#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "common.h"
#include "../database/src/db.h"

static struct flock fl = {.l_start = 0, .l_whence = SEEK_SET, .l_len = 0};

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
	fclose(file);
}

int
get_seats(char* id, char* time){
	char movieID[20];
	FILE *file;
	int seats;
	char moviePath[40];
	strcpy(movieID, id);
    strcat(movieID, "-");
    strcat(movieID, time);
	
	sprintf(moviePath, MOVIE_PATH, movieID);

	file=fopen(moviePath, "rb+");
	fread(&seats, sizeof(int), 1, file);
	fclose(file);
	return seats;
}

void
reserve_seat(char* id, char* time, int n){
	char movieID[20];
	FILE * file;
	char moviePath[40];
	int seats, fd;
	strcpy(movieID, id);
    strcat(movieID, "-");
    strcat(movieID, time);
	
	sprintf(moviePath, MOVIE_PATH, movieID);
	
	file=fopen(moviePath, "rb+");
	fd=fileno(file);

	if( wrlockFile(fd) == -1){
		printf("Imposible realizar la reserva. Pruebe de nuevo en unos minutos.");
		return;
	}
	fread(&seats, sizeof(int), 1, file);

	if( seats < n ){
		printf("No hay asientos disponibles");
		return;
	}
	
	seats=seats-n;
	printf("seats: %d\n", seats);
	fseek(file, 0, SEEK_SET);
	fwrite(&seats, sizeof(int), 1, file);
	unlockFile(fd);
	fclose(file);
	printf("Reserva exitosa");
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
