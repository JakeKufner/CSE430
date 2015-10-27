#include "sem.h"


/* thread routines */
void t1(void);
void t2(void);
void producer(void);
void consumer(void);
/* int to be modified by both routines. */
int shared_int;
Semaphore *sem;

int main(int argc, char ** argv){
	/* We need to init the global thread queue */
	runQ = (Queue*) malloc(sizeof(Queue));
	sem = (Semaphore*) malloc(sizeof(Semaphore));
	
	InitQueue(runQ);
	InitSem(sem, 1);
	
	shared_int = 0;
	
	start_thread(t1);
	start_thread(t2);

	/* start pulling threads from the runQ */	
	run();
	free(runQ);
	free(sem);
	return 0;
}


void
t1(){
	int local_int = 0;
	while(1){
		P(sem);
		printf("In t1 shared_int = %d, local_int = %d\n", shared_int, local_int);
		shared_int++;
		local_int++;
		V(sem);
		sleep(1);
	}
}



void
t2(){
	int local_int = 0;
	while(1){
		P(sem);
		printf("In t2 shared_int = %d, local_int = %d\n", shared_int, local_int);
		shared_int--;
		local_int--;
		V(sem);
		sleep(1);

	}
}

void
producer()
{


}


void
consumer()
{


}
