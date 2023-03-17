#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyQueue.h"

void error(char* pMessage)
{
	fprintf(stderr, "%s\n", pMessage);
	exit(-1);
}

void initQueue(Qtype* newQ)
{
	newQ->qCount = 0;
	newQ->qCap = 1;
	newQ->front = 0;
	newQ->rear = 0;
}

int isEmpty(Qtype* newQ)
{
	if (newQ->front == newQ->rear)
		return (1);
	else
		return (0);
}

int isFull(Qtype* newQ)
{
	if ((newQ->rear + 1) % MAX_QUEUE_SIZE == newQ->front)
		return (1);
	else
		return (0);
}

void Enqueue(Qtype* newQ, element qItem)
{
	if (isFull(newQ))
		error("Queus is full!");
	newQ->rear = (newQ->rear + 1) % MAX_QUEUE_SIZE;
	newQ->qData[newQ->rear] = qItem;
	newQ->qCount++;
}

element Dequeue(Qtype* newQ)
{
	if (isEmpty(newQ))
		error("Queue is Empty!");
	newQ->front = (newQ->front + 1) % MAX_QUEUE_SIZE;
	newQ->qCount--;
	return (newQ->qData[newQ->front]);
}

element Peek(Qtype* newQ)
{
	if (isEmpty(newQ))
		error("Queue is Empty!");
	return (newQ->qData[(newQ->front + 1) % MAX_QUEUE_SIZE]);
}

