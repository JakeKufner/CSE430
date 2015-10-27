/*
Project:
CSE 430 Project 2

Semester:
Fall 2015

Instructor:
Partha Dasgupta

Authors:
Nathaniel Mendoza
John Robertson


*/

#ifndef Q_H
#define Q_H
#include "tcb.h"
#include <stdlib.h>
/*
////////////////////////
START structure and type declarations


////////////////////////
*/

typedef enum __QUEUE_STATUS {Q_SUCCESS, Q_FAILURE} QUEUE_STATUS;

/* Use TCB_t as Node */
typedef TCB_t Node;

typedef struct __Queue{
	Node *head, *tail;
	int count;
} Queue;

/*
////////////////////////
END structure and type declarations


////////////////////////
*/

/*/////////////////////////////////////////////////////////////////////////////// */

/*
////////////////////////
START function declarations


////////////////////////
*/

QUEUE_STATUS InitQueue(Queue *q);
Node * NewItem(void);
QUEUE_STATUS FreeItem(Node *item);
QUEUE_STATUS AddQueue(Queue *q, Node *n);
Node * DelQueue(Queue *q);
QUEUE_STATUS RotateQ(Queue *q);

/*
////////////////////////
END function declarations


////////////////////////
*/

/*/////////////////////////////////////////////////////////////////////////////// */

/*
////////////////////////
START function definitions


////////////////////////
*/

QUEUE_STATUS
InitQueue(Queue *q){
	q->count = 0;
	return Q_SUCCESS;
}


Node *
NewItem(){
	return (Node *) malloc(sizeof(Node));
}


QUEUE_STATUS
FreeItem(Node *item){
	free(item);
	return Q_SUCCESS;
}


QUEUE_STATUS
AddQueue(Queue *q, Node *n){
	//first item
	if(q->count == 0){
		q->head = n;
		q->tail = n;
	}else{
		q->tail->next = n;
		n->prev = q->tail;
		q->tail = n;
	}
	
	//always increment count
	q->count++;
	//always point head.prev to tail and tail.next to head
	q->head->prev = q->tail;
	q->tail->next = q->head;

	return Q_SUCCESS;
}

/*
INPUT:
Queue structure

OUTPUT:
The node at the front of the queue, after removing it from the queue.

*/
Node *
DelQueue(Queue * q){

	if(q->count != 0){
		Node * item = q->head;

		if(q->head == q->tail){
			q->head = q->tail = 0;
		}
		else{
			q->head = q->head->next;
			//always point head.prev to tail and tail.next to head
			q->head->prev = q->tail;
			q->tail->next = q->head;
		}
		
		q->count--;

		return item;
	}
	else{
		return 0;
	}

}

QUEUE_STATUS 
RotateQ(Queue *q){

	if(q->count == 0){ //Cant rotate empty list, what to return?
		return Q_FAILURE;
	}
	else
	{
		if(q->head != q->tail) //More than 1 element in queue
		{
			q->head = q->head->next;
			q->tail = q->tail->next;
		}
	}

	return Q_SUCCESS;
}

/*
////////////////////////
END function definitions


////////////////////////
*/



#endif
