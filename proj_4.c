/*
Project:
CSE 430 Project 4

Semester:
Fall 2015

Instructor:
Partha Dasgupta

Authors:
Nathaniel Mendoza
John Robertson


*/

#include "sem.h"
#include <time.h>


/* thread routines */
void t1(void);
void t2(void);
void writer1(void);
void reader1(void);
void writer2(void);
void reader2(void);
void reader3(void);
void reader4(void);
void testMethod1(void);
void testMethod2(void);
/* int to be modified by both routines. */
int shared_int;
Semaphore *sem;


/******Writer Reader (Method 2)*********/
Semaphore *rsem, *wsem, *mutex;
#define N 2
int buffer[N];
int in, out;
int rwc, wwc, rc, wc;


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
	/* Method 2 - writer reader setup */
	srand(time(NULL));

	in = 0;
	out = 0;
	rwc = wwc = rc = wc = 0;

	rsem = (Semaphore*) malloc(sizeof(Semaphore));
	wsem = (Semaphore*) malloc(sizeof(Semaphore));
	mutex = (Semaphore*) malloc(sizeof(Semaphore));

	InitSem(rsem, 0);
	InitSem(wsem, 1);
	InitSem(mutex, 1);

	start_thread(writer1);
	start_thread(writer2);
	start_thread(reader1);
	start_thread(reader2);
	start_thread(reader4);
	start_thread(reader3);


	/* start pulling threads from the runQ */	
	run();

	free(rsem);
	free(wsem);
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
writer1()
{
	int writer_num = 1;
	while(1){
		int item = rand();
		P(mutex);
		if(rc > 0 || wc > 0){
			printf("Writer %d waiting, as rc=%d, wc=%d\n", writer_num, rc, wc);
			wwc++;
			V(mutex);
			P(wsem);
			wwc--;
		}
		wc++;
		printf("Writer %d enters C.S.\n", writer_num);
		V(mutex);
		buffer[in] = item;
		printf("Writer %d writes %d in the buffer\n", writer_num, item);
		in = (in + 1) % N;
	
		P(mutex);
		wc--;
		printf("Writer %d exiting\n", writer_num);
		if(rwc > 0)
			V(rsem);
		else if(wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}

}

void
writer2()
{
	int writer_num = 2;
	while(1){
		int item = rand();
		P(mutex);
		if(rc > 0 || wc > 0){
			printf("Writer %d waiting, as rc=%d, wc=%d\n", writer_num, rc, wc);
			wwc++;
			V(mutex);
			P(wsem);
			wwc--;
		}
		wc++;
		printf("Writer %d enters C.S.\n", writer_num);
		V(mutex);
		buffer[in] = item;
		printf("Writer %d writes %d in the buffer\n", writer_num, item);
		in = (in + 1) % N;
	
		P(mutex);
		wc--;
		printf("Writer %d exiting\n", writer_num);
		if(rwc > 0)
			V(rsem);
		else if(wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}

}


void
reader1()
{
	int reader_num = 1;
	while(1){
		P(mutex);
		if(wwc > 0 || wc > 0){
			printf("Reader %d waiting, as wwc=%d, wc=%d\n", reader_num, wwc, wc);
			rwc++;
			V(mutex);
			P(rsem);
			rwc--;

		}
		rc++;
		if(rwc > 0)
			V(rsem);
		else
			V(mutex);

		int item = buffer[in];
		printf("Reader %d reads %d from the buffer\n", reader_num, item);
		in = (in + 1) % N;

		P(mutex);
		rc--;
		
		printf("Reader %d exiting\n", reader_num);
		if(rc == 0 && wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}

}

void
reader2()
{
	int reader_num = 2;
	while(1){
		P(mutex);
		if(wwc > 0 || wc > 0){
			printf("Reader %d waiting, as wwc=%d, wc=%d\n", reader_num, wwc, wc);
			rwc++;
			V(mutex);
			P(rsem);
			rwc--;

		}
		rc++;
		if(rwc > 0)
			V(rsem);
		else
			V(mutex);

		int item = buffer[in];
		printf("Reader %d reads %d from the buffer\n", reader_num, item);
		in = (in + 1) % N;

		P(mutex);
		rc--;
		
		printf("Reader %d exiting\n", reader_num);
		if(rc == 0 && wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}

}

void
reader3()
{
	int reader_num = 3;
	while(1){
		P(mutex);
		if(wwc > 0 || wc > 0){
			printf("Reader %d waiting, as wwc=%d, wc=%d\n", reader_num, wwc, wc);
			rwc++;
			V(mutex);
			P(rsem);
			rwc--;

		}
		rc++;
		if(rwc > 0)
			V(rsem);
		else
			V(mutex);

		int item = buffer[in];
		printf("Reader %d reads %d from the buffer\n", reader_num, item);
		in = (in + 1) % N;

		P(mutex);
		rc--;
		
		printf("Reader %d exiting\n", reader_num);
		if(rc == 0 && wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}

}

void
reader4()
{
	int reader_num = 4;
	while(1){
		P(mutex);
		if(wwc > 0 || wc > 0){
			printf("Reader %d waiting, as wwc=%d, wc=%d\n", reader_num, wwc, wc);
			rwc++;
			V(mutex);
			P(rsem);
			rwc--;

		}
		rc++;
		if(rwc > 0)
			V(rsem);
		else
			V(mutex);

		int item = buffer[in];
		printf("Reader %d reads %d from the buffer\n", reader_num, item);
		in = (in + 1) % N;

		P(mutex);
		rc--;
		
		printf("Reader %d exiting\n", reader_num);
		if(rc == 0 && wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}

}



