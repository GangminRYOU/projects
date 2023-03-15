
#pragma once

#define MAX_STACK_SIZE 100

typedef struct chStack
{
	int sTop;
	int sCap;
	char* eData;
}chStack;

typedef struct nStack
{
	int sTop;
	int sCap;
	int* eData;
}nStack;

int initchStack(chStack* newStack);
int chFull(chStack* newStack);
int chEmpty(chStack* newStack);
int nFull(nStack* newStack);
int nEmpty(nStack* newStack);
void chPush(chStack* newStack, char item);
char chPop(chStack* newStack);
char chPeek(chStack* newStack);
int initnStack(nStack* newStack);
void nPush(nStack* newStack, int item);
int nPop(nStack* newStack);
int nPeek(nStack* newStack);
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
Mystack.h [unix] (08:59 01/01/1970)                                    0,0-1 All
"Mystack.h" [New]

