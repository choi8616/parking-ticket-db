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
 * free_tickets
 *      tears down the database freeing all allocated memory
 *
 *      go down each hash chain and free all the vehicles and the tickets
 *      for each vehicle
 *      count the number of tickets freed in the database and
 *      print it out before returning
 *
 *      unsigned long cnt = 0UL
 *      printf("Total tickets freed: %lu\n", cnt);
 * args
 *  hashtab pointer to hashtable (pointer to an array of pointers)
 *  tabsz   number of elements in the hash table
 */
void
free_tickets(struct vehicle **hashtab, uint32_t tabsz)
{
    unsigned long cnt = 0UL;		/* Count of freed ticket */
    for (int i = 0; i < (int)tabsz; i++) {
	/*
	 * Traverse the vehicles for each hash table
	 */    
	struct vehicle *ptr;		/* Pointer to each vehicle */
	struct vehicle *prev_veh;	/* Pointer to previous vehicle */
	ptr = hashtab[i];
    	while (ptr != NULL) {
	    /*
	     * Traverse tickets for each vehicle
	     */
	    struct ticket *curr = ptr->head;	/* Pointer to each ticket */
	    struct ticket *prev = ptr->head;	/* Pointer to previous ticket */
	    while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		/*
		 * Free previous pointed ticket after we have stored the next 
		 * ticket with curr pointer
		 */
	    	free(prev);
		cnt++;
	    }
	    prev_veh = ptr; 
	    /*
	     * Free up all the memories associated with vehicle
	     */
	    free(ptr->state);
	    free(ptr->plate);
	    ptr = ptr->next;
	    free(prev_veh);
	}
    }
    free(hashtab);
    printf("Total tickets freed: %lu\n", cnt);
}
#endif
