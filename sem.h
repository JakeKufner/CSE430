#ifndef SEM_H
#define SEM_H
#include "threads.h"
#include "q.h"
#include "tcb.h"
typedef struct Semaphore_{
	int value;
	Queue blocked;
} Semaphore;

/*
INPUT:
A semaphore struct and a value from which to initialize the semaphore.

OUTPUT:
Integer value to indicate the success of the routine.  If the result is < 0, an error has occurred


*/
int 
InitSem(Semaphore * s, int value)
{
	s->value = value;
	InitQueue(&s->blocked);

	return 0;

}

/*
INPUT:
A semaphore structure

OUTPUT:
none

Routine description:
Decrements the semaphore count and blocks the running process if P is negative.
*/
void
P(Semaphore *s)
{
	TCB_t * tcb;
	s->value -= 1;
	if(s->value < 0){
		//remove blocked process from runQ
		tcb = DelQueue(runQ);
		/*to actually block the process we need to swap the context*/
		if(!runQ->head){
			printf("No thread available to run on P.  Deadlock occurred.\n");
			exit(-1);
		}
		
		//block process by putting it on the blocked queue in the semaphore
		AddQueue(&s->blocked, tcb);
		//make sure that we have the up-to-date context in the blocked q
		swapcontext(&tcb->context, &runQ->head->context);
	}

}

/*
INPUT:
A semaphore structure

OUTPUT:
none

Routine description:
Increments the semaphore counter and moves a thread from the blocked queue to the run queue
*/
void
V(Semaphore *s)
{
	TCB_t * tcb;
	s->value += 1;
	if(s->value <= 0)
	{
		tcb = DelQueue(&s->blocked);
		AddQueue(runQ, tcb);
	}

	yield();

}
#endif
