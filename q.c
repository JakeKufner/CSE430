#include "q.h"
#include <stdlib.h>

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



