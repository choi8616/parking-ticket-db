#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "hashdb.h"

//uncomment the next line when you want to use your routine
//#define MYCODE
#ifndef MYCODE
TODO(USING THE SOLUTION FUNCTION NOT MY CODE)
#else

/*
 * vehicle_lookup
 *          look for vehicle in the database
 *          vehicle must match both plate and state strings
 * args
 *  hashtab pointer to hashtable (pointer to an array of pointers)
 *  tabsz   number of elements in the hash table
 *  plate   plate id string to be found
 *  state   state id string to be found
 *  argv    for error printing
 *
 * returns  pointer to vehicle if found NULL otherwise
 */

struct vehicle *
vehicle_lookup(struct vehicle **hashtab, uint32_t tabsz, char *plate,
    char *state, char **argv)
{
    uint32_t hashnum;		/* converted hasho value of vehicle */
    int index;			/* hash table index of vehicle */
    if ((hashnum = hash(plate, argv)) == 0UL) {
    	return NULL;
    }
    index = hashnum % tabsz;

    struct vehicle *ptr;	/* pointer to the vehicle being searched */
    ptr = hashtab[index];
    while (ptr != NULL) {
    	if ((strcmp(ptr->plate, plate) == 0) 
		&& (strcmp(ptr->state, state) == 0)) {
	    break;
	}
	ptr = ptr->next;
    }
    
    /*
     * This condition means the vehicle pointer reached the end of the 
     * linked list, referring that it wans't found
     */    
    if (ptr == NULL) {
	return NULL;
    }  
    return ptr;
}
#endif
