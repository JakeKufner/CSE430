#include "threads.h"
#include <stdio.h>
#include <stdlib.h>
/* for the sleep routine */
#include <unistd.h>


/* thread routines */
void t1(void);
void t2(void);

/* int to be modified by both routines. */
int shared_int;

int main(int argc, char ** argv){
	/* We need to init the global thread queue */
	runQ = (Queue*) malloc(sizeof(Queue));
	
	shared_int = 0;
	
	start_thread(t1);
	start_thread(t2);

	/* start pulling threads from the runQ */	
	run();
	free(runQ);

	return 0;
}


void t1(){
	int local_int = 0;
	while(1){
		yield();
		printf("In t1 shared_int = %d, local_int = %d\n", shared_int, local_int);
		shared_int++;
		local_int++;
		sleep(1);
	}
}



void t2(){
	int local_int = 0;
	while(1){
		printf("In t2 shared_int = %d, local_int = %d\n", shared_int, local_int);
		sleep(1);
		yield();
		shared_int--;
		local_int--;

	}
}
