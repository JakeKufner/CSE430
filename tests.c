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

TEST
test_DelQueue(){

	Queue q;
	InitQueue(&q);
	Node *newItem1, *newItem2, *newItem3, *newItem4;
	Node *testItem1, *testItem2, *testItem3;
	int val1 = 1, val2 = 2, val3 = 3, val4 = 4;

	newItem1 = NewItem();
	newItem1->val = val1;

	AddQueue(&q, newItem1);
	ASSERT(q.head->val == val1);
	ASSERT(q.tail->val == val1);
	ASSERT(q.count == 1);

	testItem1 = DelQueue(&q);
	ASSERT(q.head == q.tail);
	ASSERT(q.count == 0);

	ASSERT(testItem1->val = val1);

	newItem2 = NewItem();
	newItem2->val = val2;

	newItem3 = NewItem();
	newItem3->val = val3;

	AddQueue(&q, newItem2);
	AddQueue(&q, newItem3);

	ASSERT(q.head->val == val2);
	ASSERT(q.tail->val == val3);
	ASSERT(q.count == 2);

	testItem2 = DelQueue(&q);
	ASSERT(testItem2->val = val2);
	ASSERT(q.count == 1);
	ASSERT(q.head == q.tail);

	testItem3 = DelQueue(&q);
	ASSERT(testItem3->val = val3);
	ASSERT(q.count == 0);

	newItem4 = NewItem();
	newItem4->val = val4;

	AddQueue(&q, newItem1);
	AddQueue(&q, newItem2);
	AddQueue(&q, newItem3);
	AddQueue(&q, newItem4);
	
	//test if queue is still circular after delete
	DelQueue(&q);
	ASSERT(q.head->prev->val = q.tail->val);
	ASSERT(q.tail->next->val = q.head->val);


	FreeItem(newItem1);
	FreeItem(newItem2);
	FreeItem(newItem3);
	FreeItem(newItem4);

	PASS();
}


TEST
test_RotateQ(){

	Queue q;
	InitQueue(&q);
	Node *newItem1, *newItem2, *newItem3, *newItem4;
	int val1 = 1, val2 = 2, val3 = 3, val4 = 4;

	newItem1 = NewItem();
	newItem1->val = val1;
	newItem2 = NewItem();
	newItem2->val = val2;
	newItem3 = NewItem();
	newItem3->val = val3;
	newItem4 = NewItem();
	newItem4->val = val4;

	AddQueue(&q, newItem1);
	AddQueue(&q, newItem2);
	AddQueue(&q, newItem3);
	AddQueue(&q, newItem4);

	//Queue is 1 2 3 4
	ASSERT(q.head->val == val1);
	ASSERT(q.tail->val == val4);

	RotateQ(&q);
	//Queue is 2 3 4 1
	ASSERT(q.head->val == val2);
	ASSERT(q.tail->val == val1);

	RotateQ(&q);
	//Queue is 3 4 1 2
	ASSERT(q.head->val == val3);
	ASSERT(q.tail->val == val2);

	RotateQ(&q);
	//Queue is 4 1 2 3
	ASSERT(q.head->val == val4);
	ASSERT(q.tail->val == val3);

	RotateQ(&q);
	//Queue is 1 2 3 4
	ASSERT(q.head->val == val1);
	ASSERT(q.tail->val == val4);


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
