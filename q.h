#ifndef Q_H
#define Q_H

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


QUEUE_STATUS InitQueue(Queue *q);


Node * NewItem(void);


QUEUE_STATUS FreeItem(Node *item);


QUEUE_STATUS AddQueue(Queue *q, Node *n);

#endif
