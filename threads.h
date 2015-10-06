#include "q.h"
#include <stdio.h>
#define STACK_SIZE 8192

/* Global run queue */
Queue * runQ;

void start_thread(void (*routine)(void)){
	void * stack = malloc(STACK_SIZE);
	TCB_t * tcb = (TCB_t *) malloc(sizeof(TCB_t));
	init_TCB(tcb, routine, stack, STACK_SIZE);
	
	/* Add the TCB to the thread Q */
	AddQueue(runQ, tcb);

}



void run(){
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQ->head->context));

}


void yield(){
	ucontext_t current, next;
	RotateQ(runQ);
	getcontext(&current);
	next = runQ->head->context;
	swapcontext(&current, &next);
}
