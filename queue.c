/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/

queue_t*
q_new()
{
	queue_t* q = malloc(sizeof(queue_t));
	/* What if malloc returned NULL? */
	if (q != NULL) {
		q->head = NULL;
		q->tail = NULL;
		q->size = 0;
		return q;
	}
	return NULL;
}

/* Free all storage used by queue */
void
q_free(queue_t* q)
{
	/* How about freeing the list elements and the strings? */
	/* Free queue structure */
	list_ele_t* tempP;
	while (q->head) {
		tempP	= q->head;
		q->head = q->head->next;
		free(tempP->value);
		free(tempP);
	}
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool 
q_insert_head(queue_t* q, char* s)
{
	list_ele_t* newh;
	char* value;
	/* What should you do if the q is NULL? */
	newh  = malloc(sizeof(list_ele_t));
	value = (char *) calloc(strlen(s) + 1, sizeof *s);
	if (q && newh && value) {
		newh->value = value;
		strcpy(newh->value, s);
		newh->next = q->head;
		q->head	   = newh;
		if (q->size == 0)
			q->tail = newh;
		q->size++;
		return true;
	}
	/* Don't forget to allocate space for the string and copy it */
	return false;
	/* What if either call to malloc returns NULL? */
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool
q_insert_tail(queue_t* q, char* s)
{
	/* You need to write the complete code for this function */
	/* Remember: It should operate in O(1) time */

	list_ele_t* newh;
	char* value;

	/* What should you do if the q is NULL? */
	newh  = malloc(sizeof(list_ele_t));
	value = (char *) calloc(strlen(s) + 1, sizeof *s);

	if (q && newh && value) {
		newh->value = value;
		strcpy(newh->value, s);

		if (!q->tail)
			q->tail = newh;

		q->tail->next = newh;
		q->tail		  = newh;
		newh->next	  = NULL;

		if (!q->size)
			q->head = newh;

		q->size++;
		return true;
	}
	/* Don't forget to allocate space for the string and copy it */
	return false;
	/* What if either call to malloc returns NULL? */
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool
q_remove_head(queue_t* q, char* sp, size_t bufsize)
{
	/* You need to fix up this code. */
	list_ele_t* pl = q->head;
	if (q && pl) {
		if(sp) {
			strncpy(sp, pl->value, bufsize - 1);
			sp[bufsize - 1] = '\0';
		}
		q->head = q->head->next;
		q->size--;
		free(pl->value);
		free(pl);
		return true;
	}
	return false;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int
q_size(queue_t* q)
{
	/* You need to write the code for this function */
	/* Remember: It should operate in O(1) time */
	return q ? q->size: 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void
q_reverse(queue_t* q)
{
	/* You need to write the code for this function */
	if (q == NULL || q->size <= 1)
        return;
	
	list_ele_t* prev = NULL;
	list_ele_t* current = q->head;

	while(current) {
		list_ele_t* next = current->next;
		current->next = prev;
		prev = current;
		current = next;	
	}
	list_ele_t* temp = q->tail;
	q->tail = q->head;
	q->head = temp;

}