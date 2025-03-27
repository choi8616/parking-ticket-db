#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "hashdb.h"
#include "readsubs.h"

//uncomment the next line when you want to use your routine
//#define MYCODE
#ifndef MYCODE
TODO(USING THE SOLUTION FUNCTION NOT MY CODE)
#else

/*
 * insert_ticket
 *      add a ticket (summons) to the database
 *
 *      YOU CANNOT USE CALLOC(), only malloc() is allowed.
 *
 *      if the vehicle (plate state) is not in the database then
 *      a new struct vehicle entry must be made for it in the hash table.
 *      New vehicle entries are made at the the FRONT of the collison chain
 *
 *      If the vehicle is already in the hash chain, you only need to add 
 *      a new ticket to the ticket chain for this summons.
 *
 *      Tickets are added to the ticket chain linked to the struct vehicle
 *      at the END of the ticket chain.
 *
 *      Also you must update the tot_fine and cnt_tickets in the struct vehicle
 *      to account for the new summons(ticket) just added
 * args:
 *  hashtab pointer to hashtable (pointer to an array of pointers)
 *  tabsz   number of elements in the hash table
 *          example hashval = hash(plate, argv) % tabsz;
 *  fineTab pointer fine table. maps code number to text description & fine cost 
 *          you use this table to get the amount of the fine when calculating
 *          the tot_fine field in struct vehicle.
 *          example:
 *              struct vehicle *vhpt;
 *              vhpt->tot_fine += fineTab[code].fine;
 *  summ    summons id string to be added
 *          this string needs to be converted to a number to be stored in the
 *          database. This saves space and is faster to compare than a string         
 *          Conversion function is supplied. use example:
 *               long long summid;
 *               if (strtosumid(summ, &summid, argv) != 0)
 *                  error handling
 *               new_ticket->summons = summid;
 *  plate   plate id string to be added
 *  state   state id string to be added
 *  date    date of summons string
 *          this string needs to be converted to a number to be stored in the
 *          database. This saves space and is faster to compare than a string
 *          The encoding into a number uses Linux time format.
 *          Conversion function is supplied. use example:
 *              time_t dateval;
 *              if (strtoDate(date, &dateval, argv) != 0)
 *                  error handling
 *              new_ticket->date = dateval;
 *  code    summons code integer value used an an index into the fines table
 *  argv    for error printing
 *
 * returns 0 if ok -1 for all errors
 */
int
insert_ticket(struct vehicle **hashtab, uint32_t tabsz, struct fine *fineTab, char *summ,
            char *plate, char *state, char *date, int code, char **argv)
{
    unsigned long long summid;		/* summons id of new ticket */
    time_t dateval;			/* date of new ticket */
    /*
     * Special case of invalid summ or date value
     */
    if ((strtosumid(summ, &summid, argv) != 0)) {
    	return -1;
    } 
    if ((strtoDate(date, &dateval, argv) != 0)) {
    	return -1;
    }

    struct ticket *new_ticket;		/* new ticket to be inserted */
    if ((new_ticket = malloc(sizeof(*new_ticket))) == NULL) {
    	return -1;
    }
    if (new_ticket != NULL) {
    	new_ticket->summons = summid;
	new_ticket->date = dateval;
	new_ticket->code = code;
	new_ticket->next = NULL;
    }    

    struct vehicle *veh;		/* vehicle that is being found */    
    if ((veh = vehicle_lookup(hashtab, tabsz, plate, state, argv)) == NULL) {
    	uint32_t hashnum;		/* converted hash value of vehicle */
	int index;			/* hash table index of vehicle */
	if ((hashnum = hash(plate, argv)) == 0UL) {
	    return -1;
	}
        index = hashnum % tabsz;
	
	/*
	 * If vehicle is not found create a new vehicle sturct 
	 */
	struct vehicle *new_vehicle;	/* new vehicle being added */
	if ((new_vehicle = malloc(sizeof(*new_vehicle))) == NULL) {
	    free(new_ticket);
	    return -1;
	}
	if (new_vehicle != NULL) {
	    new_vehicle->state = strdup(state);
	    new_vehicle->plate = strdup(plate);
	    new_vehicle->tot_fine = fineTab[code].fine;
	    new_vehicle->cnt_ticket = 1;
	    new_vehicle->next = hashtab[index];
	    hashtab[index] = new_vehicle;
	    new_vehicle->head = new_ticket;
	}
    } else {
    	struct ticket *ptr = veh->head; /* pointer to add ticket */
	struct ticket *prev = veh->head;/* pointer to previous of new ticket */
	/*
	 * Traverse the pointer to the end of the ticket linked list and add
	 * the new ticket at the end
	 */
    	while (ptr != NULL) {
	    prev = ptr;
    	    ptr = ptr->next;
    	}
	/* 
	 * If no ticket exist in the vehicle add the ticket to the head
	 */
	if (ptr == veh->head) {
	    veh->head = new_ticket;
	} else {
	    prev->next = new_ticket;
	}
    	veh->tot_fine += fineTab[code].fine;
    	veh->cnt_ticket++;
    }
    return 0;
}
#endif
