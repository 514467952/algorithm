#pragma once
#include<stdio.h>
#include<malloc.h>
#include<assert.h>
typedef struct Node{
	int value;
	struct Node *next;
}Node;

//ͷɾ+β��

typedef struct Queue{
	Node *front;  //�����һ�����
	Node *rear;   //�������һ�����
	int size;	//���ݸ���
};

//��ʼ��
void QueueInit(Queue *queue){
	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;
}
//����
void QueueDestroy(Queue *queue){
	Node *node, *next;
	for (node = queue->front; node != NULL; node = next){
		next = node->next;
		free(node);
	}

	queue->front = queue->rear = NULL;
	queue->size = 0;
}

//Push,��β���룬�������β��
void QueuePush(Queue *queue, int val){
	Node *node = (Node*)malloc(sizeof(Node));
	node->value = val;
	node->next = NULL;

	if (queue->rear != NULL){
		queue->rear->next = node;
		queue->rear = node;
	}
	else
	{
		queue->front = queue->rear = node;
	}
	queue->size++:
}

//Pop ��β���У��������ͷɾ
void QueuePop(Queue* queue){
	assert(queue->size > 0);
	queue->size--;
	Node *front = queue->front;
	queue->front = queue->front->next;
	free(front);

	if (queue->front == NULL){
		//����ֻ��һ���������
		queue->rear = NULL;
	}
}
//Front ���ض���Ԫ��
int QueueFront(const Queue *queue){
	return queue->front->value;
}
//Rear  ���ض�βԪ��
int QueueRear(const Queue *queue){
	return queue->rear->value;
}
//Empty �Ƿ�Ϊ��
int QueueEmpty(const Queue *queue){
	return queue->size == 0 ? 1 : 0;
}
//Size  
int QueueEmpty(const Queue *queue){
	return queue->size ;
}

