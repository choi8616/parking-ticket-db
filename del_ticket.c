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
 * del_ticket
 *      remove ticket (summons) from the database
 *      look up the summons for a vehicle and pay it (remove the ticket) 
 *
 *      Find the vehicle by the state and plate. if not found return -1
 *
 *      convert the summ string to a long long int using
 *      using strtosumid. This long long int is how the summons number
 *      is stored in the database in struct ticket.
 *      After being converted you can use it find a summons id match
 *      in the linked list of tickets attached to the strcut vehicle.      
 *
 *      After you have the vehicle, find the summons on the ticket chain
 *      that matches the converted summons string (summid in the example)
 *      example:
 *        unsigned long long summid
 *        if (strtosumid(summ, &summid, argv) != 0)
 *           return -1;
 *        now search the ticket chain to find that summons
 *        struct ticket *tptr;
 *        if (tptr->summons == summid)
 *          found it
 *           
 *      If found, delete it from the ticket chain. If the vehicle
 *      no longer has any tickets, then remove the vehicle from the hash chain
 *      Otherwise you must update the tot_fine and cnt_tickets fields in
 *      the struct vehicle so the are accurate after removing the summons
 *      Make sure to delete all space that malloc()'d 
 *
 * Inputs:
 *  hashtab pointer to hashtable (pointer to an array of pointers)
 *  tabsz   number of elements in the hash table
 *  fineTab table mapping fine code to description and fine   
 *  plate   plate id string to be found
 *  state   state id string to be found
 *  summ    summon id string to be found
 *  argv    for error printing
 *
 * returns 0 if ok -1 if not found or error
 */

int
del_ticket(struct vehicle **hashtab, uint32_t tabsz, struct fine *fineTab,
    char *plate, char *state, char *summ, char **argv)
{
    uint32_t hashnum;			/* converted hash value of vehicle */
    int index;				/* hash table index of vehicle */
    if ((hashnum = hash(plate, argv)) == 0UL) {
    	return -1;
    }
    index = hashnum % tabsz;

    struct vehicle *veh;		/* vehicle being found */
    struct vehicle *prevveh;		/* pointer to previous vehicle */
    veh = hashtab[index];
    prevveh = hashtab[index];
    while (veh != NULL) {
    	if ((strcmp(veh->plate, plate) == 0) 
		&& (strcmp(veh->state, state) == 0)) {
	    break;
	}
	prevveh = veh;
	veh = veh->next;
    }
    /*
     * Special case of vehicle not found
     */
    if (veh == NULL) {
	return -1;
    }  

    unsigned long long summid;		/* summons id of ticket to delete */
    if ((strtosumid(summ, &summid, argv) != 0)) {
	return -1;
    }
    struct ticket *ptr = veh->head;	/* pointer to delete ticket */
    struct ticket *prev = veh->head;	/* pointer to previous ticket */

    while (ptr != NULL) {
    	if (ptr->summons == summid) {
	    break;
	}
	prev = ptr;
	ptr = ptr->next;
    }
    /*
     * Pointer has reached NULL, meaning ticket is not found
     */   
    if (ptr == NULL) {
    	return -1;
    }

    if (ptr == veh->head) {
	int index = ptr->code;		/* index of fine table */
	/* 
	 * Update total fine and count of ticket after deletion
	 */
	veh->tot_fine -= fineTab[index].fine;
	veh->cnt_ticket--;
    	veh->head = ptr->next;
    } else {
	int index = ptr->code;		
	veh->tot_fine -= fineTab[index].fine;
	veh->cnt_ticket--;
	prev->next = ptr->next;
    }
    
    /* 
     * Special case of vehicle not having any ticket after deletion,
     * delete the vehicle from the hash table and free all the memory
     */
    if (veh->tot_fine == 0 && veh->cnt_ticket == 0) {
	if (veh == hashtab[index]) {
	    hashtab[index] = veh->next;
	} else {
	    prevveh->next = veh->next;
	}
    	free(veh->state);
    	free(veh->plate);
    	free(veh->head);
    	free(veh);
    }

    free(ptr);
    return 0;
}
#endif
