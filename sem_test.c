#include "sem.h"
#include <time.h>


/* thread routines */
void t1(void);
void t2(void);
void producer1(void);
void consumer1(void);
void producer2(void);
void consumer2(void);
void testMethod1(void);
void testMethod2(void);
/* int to be modified by both routines. */
int shared_int;
Semaphore *sem;


/******Producer Consumer (Method 2)*********/
Semaphore *empty, *full, *mutex;
#define N 5
int buffer[N];
int in, out;

/***************/


int main(int argc, char ** argv){
	/* We need to init the global thread queue */
	runQ = (Queue*) malloc(sizeof(Queue));
	InitQueue(runQ);

	//run method to demonstrate functionality
	testMethod2();
	

	free(runQ);
	return 0;
}

//These methods are to demostrate the functionality of the semaphores
void
testMethod1(){
	sem = (Semaphore*) malloc(sizeof(Semaphore));

	InitSem(sem, 1);
	
	shared_int = 0;
	
	start_thread(t1);
	start_thread(t2);

	run();
	free(sem);

}

void
testMethod2(){
	/* Method 2 - producer consumer setup */
	srand(time(NULL));

	in = 0;
	out = 0;

	empty = (Semaphore*) malloc(sizeof(Semaphore));
	full = (Semaphore*) malloc(sizeof(Semaphore));
	mutex = (Semaphore*) malloc(sizeof(Semaphore));

	InitSem(empty, N);
	InitSem(full, 0);
	InitSem(mutex, 1);

	start_thread(producer1);
	start_thread(producer2);
	start_thread(consumer1);
	start_thread(consumer2);


	/* start pulling threads from the runQ */	
	run();

	free(empty);
	free(full);
	free(mutex);

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
producer1()
{
	while(1){
		int item = rand();
		P(empty);
		P(mutex);
		buffer[in] = item;
		printf("Producer 1 places %d in the buffer at index %d\n", item, in);
		in = (in + 1) % N;
		
		V(mutex);
		V(full);
		sleep(1);
	}

}


void
consumer1()
{
	while(1){
		P(full);
		P(mutex);
		int item = buffer[out];
		printf("Consumer 1 removes %d from the buffer at index %d\n", item, out);
		out = (out + 1) % N;
		V(mutex);
		V(empty);
		sleep(1);
	}

}

void
producer2()
{
	while(1){
		int item = rand();
		P(empty);
		P(mutex);
		buffer[in] = item;
		printf("Producer 2 places %d in the buffer at index %d\n", item, in);
		in = (in + 1) % N;
		V(mutex);
		V(full);
		sleep(1);
	}

}


void
consumer2()
{
	while(1){
		P(full);
		P(mutex);
		int item = buffer[out];
		printf("Consumer 2 removes %d from the buffer at index %d\n", item, out);
		out = (out + 1) % N;
		V(mutex);
		V(empty);
		sleep(1);
	}	

}

