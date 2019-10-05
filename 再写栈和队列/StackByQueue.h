#pragma once
#include"Queue.h"

typedef struct{
	Queue queue;
	int maxSize;
}MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate(int maxSize) {
	MyStack *stack = (MyStack *)malloc(sizeof(MyStack));

	QueueInit(&(stack->queue));
	stack->maxSize = maxSize;

	return stack;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
	QueuePush(&(obj->queue), x);
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
	int size = QueueSize(&(obj->queue));
	for (int i = 0; i < size - 1; i++){
		int val = QueueFront(&(obj->queue));
		QueuePop(&(obj->queue));
		QueuePush(&(obj->queue), val);
	}

	int val = QueueFront(&(obj->queue));
	QueuePop(&(obj->queue));
	return val;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
	int size = QueueSize(&(obj->queue));
	for (int i = 0; i < size - 1; i++){
		int val = QueueFront(&(obj->queue));
		QueuePop(&(obj->queue));
		QueuePush(&(obj->queue), val);
	}

	int val = QueueFront(&(obj->queue));
	QueuePop(&(obj->queue));
	QueuePush(&(obj->queue),val);
	return val;
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
	return QueueEmpty(&(obj->queue));
}

void myStackFree(MyStack* obj) {
	QueueDestroy(&(obj->queue));
	free(obj);
}