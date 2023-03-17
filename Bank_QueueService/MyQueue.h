#pragma once

#define MAX_QUEUE_SIZE 6


typedef struct element
{
	int id;
	int arrivalTime;
	int serviceTime;
}element;

typedef struct Qtype {
	int qCount;
	int qCap;
	int front;
	int rear;
	element qData[MAX_QUEUE_SIZE];
}Qtype;


void error(char* pMessage);
void initQueue(Qtype* newQ);
int isEmpty(Qtype* newQ);
int isFull(Qtype* newQ);
void Enqueue(Qtype* newQ, element qItem);
element Dequeue(Qtype* newQ);
element Peek(Qtype* newQ);
