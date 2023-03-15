#include <stdio.h>
#include <stdlib.h>
#include "Mystack.h"

int initchStack(chStack* newStack)
{
	newStack->sTop = -1;
	newStack->sCap = 1;
	newStack->eData = (char*)calloc(newStack->sCap, sizeof(char));
	if (newStack->eData == NULL)
		return (-1);
}
int initnStack(nStack* newStack)
{
	newStack->sTop = -1;
	newStack->sCap = 1;
	newStack->eData = (int*)calloc(newStack->sCap, sizeof(int));
	if (newStack->eData == NULL)
		return (-1);
}

int chFull(chStack* newStack)
{
	return (newStack->sTop == newStack->sCap - 1);
}

int chEmpty(chStack* newStack)
{
	return (newStack->sTop == -1);
}

int nFull(nStack* newStack)
{
	return (newStack->sTop == newStack->sCap - 1);
}

int nEmpty(nStack* newStack)
{
	return (newStack->sTop == -1);
}

void chPush(chStack* newStack, char item)
{
	char* isNull = newStack->eData;
	if (chFull(newStack))
	{
		newStack->sCap *= 2;
		if (newStack->sCap > MAX_STACK_SIZE)
		{
			fprintf(stderr, "Exceded Max stack size!\n");
			exit(-1);
		}
		newStack->eData = (char*)realloc(newStack->eData, newStack->sCap * sizeof(char));
		if (newStack->eData == NULL)
		{
			free(isNull);
			fprintf(stderr, "Memory allocation fail!\n");
			exit(-1);
		}
	}
	newStack->eData[++(newStack->sTop)] = item;
}

void nPush(nStack* newStack, int item)
{
	int* isNull = newStack->eData;
	if (nFull(newStack))
	{
		newStack->sCap *= 2;
		if (newStack->sCap > MAX_STACK_SIZE)
		{
			fprintf(stderr, "Exceded Max stack size!\n");
			exit(-1);
		}
		newStack->eData = (int*)realloc(newStack->eData, newStack->sCap * sizeof(int));
		if (newStack->eData == NULL)
		{
			free(isNull);
			fprintf(stderr, "Memory allocation fail!\n");
			exit(-1);
		}
	}
	newStack->eData[++(newStack->sTop)] = item;
}

char chPop(chStack* newStack)
{
	if (chEmpty(newStack))
	{
		fprintf(stderr, "Stack is empty!\n");
		exit(-1);
	}
	return(newStack->eData[(newStack->sTop)--]);
}
int nPop(nStack* newStack)
{
	if (nEmpty(newStack))
	{
		fprintf(stderr, "Stack is empty!\n");
		exit(-1);
	}
	return(newStack->eData[(newStack->sTop)--]);
}

char chPeek(chStack* newStack)
{
	if (chEmpty(newStack))
	{
		fprintf(stderr, "Stack is empty!\n");
		exit(-1);
	}
	return(newStack->eData[newStack->sTop]);
}

int nPeek(nStack* newStack)
{
	if (nEmpty(newStack))
	{
		fprintf(stderr, "Stack is empty!\n");
		exit(-1);
	}
	return(newStack->eData[newStack->sTop]);
}
