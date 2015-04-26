#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./dbAccess/dbAccess.h"
#include "ipc.h"

void
executeRequest(Request r, Response * response){
    switch(r.ac){
        case CHECK_SEATS:{
            response->value = get_seats(r.movieID, r.times);
            break;
        }
        case GET_MOVIES:{
        	response->list = get_movies();
        	break;
        }
        case RESERVE_SEAT:{
        	reserve_seat(r.movieID, r.times, r.cant_seats);
        	break;
        }
        case GET_TIMES:{
        	get_times(r.movieTimes);break;
        }
        default:{
        	printf("Invalid action.\n");
        }

    }
}
