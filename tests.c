#include "greatest.h"
#include "q.h"
#include <stdlib.h>

/*
The queue is represented by a simple doubly linked list

typedef struct _Queue{
	Node * head; //beginning of queue
	Node * tail; //end of queue
	unsigned int count;

} Queue;

typedef struct _Node{
	Node * prev;
	Node * next;
	int val;	
} Node;


*/

SUITE(test_suite);

//TODO: For Nathaniel to implement
TEST
test_DelQueue(){

	PASS();
}

//TODO: For Nathaniel to implement
TEST
test_RotateQ(){

	PASS();
}


TEST
test_initQueue(){
	Queue q;
	InitQueue(&q);
	ASSERT(q.count == 0);
	PASS();
	
}

TEST
test_NewItem(){
	Node * newItem;
	newItem = NewItem();
	newItem->val = 5;
	ASSERT(newItem->val == 5);

	FreeItem(newItem);

	PASS();
}


TEST
test_Enqueue(){
	Queue q;
	Node *newItem, *newItem2, *newItem3;
	int val1 = 1, val2 = 2, val3 =3;
	InitQueue(&q);
	
	newItem = NewItem();
	newItem->val = val1;	
	
	//add item to queue
	AddQueue(&q, newItem);

	ASSERT(q.head->val == val1);
	ASSERT(q.tail->val == val1);
	ASSERT(q.count == 1);

	newItem2 = NewItem();
	newItem2->val = val2;
	AddQueue(&q, newItem2);

	//make sure that head val has not changed, and only tail val has changed
	ASSERT(q.head->val == val1);
	ASSERT(q.tail->val == val2);
	ASSERT(q.count == 2);
	//head should point at tail
	ASSERT(q.head->next == q.tail);

	//one more for good measure
	newItem3 = NewItem();
	newItem3->val = val3;
	AddQueue(&q, newItem3);
	//head has not changed, as we add to the end
	ASSERT(q.head->val == val1);
	//tail is our new item
	ASSERT(q.tail == newItem3);
	//count updated correctly
	ASSERT(q.count == 3);
	//head.prev points to tail
	ASSERT(q.head->prev == q.tail);
	//head.next does not point to tail, points to middle
	ASSERT(q.head->next == newItem2);
	//3 items, all connected
	ASSERT(q.head->next->next == q.tail);
	//tail.next == head
	ASSERT(q.tail->next == q.head);
	
	//free items
	FreeItem(newItem);
	FreeItem(newItem2);
	FreeItem(newItem3);


	PASS();
}



SUITE(test_suite)
{
	RUN_TEST(test_initQueue);
	RUN_TEST(test_NewItem);
	RUN_TEST(test_Enqueue);
	RUN_TEST(test_DelQueue);
	RUN_TEST(test_RotateQ);


}

GREATEST_MAIN_DEFS();

int main(int argc, char ** argv){

	GREATEST_MAIN_BEGIN();
	RUN_SUITE(test_suite);
	GREATEST_MAIN_END();
	return 0;
}
