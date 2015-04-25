#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "ipc.h"

void
executeRequest(Request r, Response * response){
    switch(r.ac){
        case CHECK_SEATS:
            response->value = get_seats(r.movieID, r.times);
            break;
        case SHOW_MOVIE:
            response->list=get_movies();
        case RESERVE_SEAT:
            response->value=reserve_seat(r.movieID,r.times);
        default:
        	printf("Invalid action.\n");

    }
}
