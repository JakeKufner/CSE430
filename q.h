/*
Project:
CSE 430 Project 1

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
/*
////////////////////////
START structure and type declarations


////////////////////////
*/

typedef enum __QUEUE_STATUS {Q_SUCCESS, Q_FAILURE} QUEUE_STATUS;

struct __Node{
	struct __Node *next, *prev;
	int val;
};

typedef struct __Node Node;

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
////////////////////////
END function definitions


////////////////////////
*/

#endif
