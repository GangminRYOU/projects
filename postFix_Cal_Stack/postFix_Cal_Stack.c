#include <stdio.h>
#include <stdlib.h>
#include "Mystack.h"
#include <string.h>

int calFunc(int operandA, int operandB, char ch)
{
	switch (ch)
	{
	case '+':
		return (operandA + operandB);
	case '-':
		return (operandA - operandB);
	case '*':
		return (operandA * operandB);
	case '/':
		return (operandA / operandB);
	}
}

int checkOP(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return (1);
	else if (ch >= '0' && ch <= '9')
		return (0);
	else
		return (-1);
}

int calPost(const char* pPfix)
{
	nStack newStack;
	int operandA;
	int operandB;
	int Value;
	int result;
	int index;

	index = -1;
	initnStack(&newStack);
	while (pPfix[++index])
	{
		if (checkOP(pPfix[index]) == 0)
		{
			Value = pPfix[index] - '0';
			nPush(&newStack, Value);
		}
		else if (checkOP(pPfix[index]) == 1)
		{
			operandB = nPop(&newStack);
			operandA = nPop(&newStack);
			result = calFunc(operandA, operandB, pPfix[index]);
			nPush(&newStack, result);
		}
		else
			fprintf(stderr, "fuction is not valid\n");
	}
	result = nPop(&newStack);
	if (!nEmpty(&newStack))
		return (-1);
	else
		return (result);
}

int opPriority(char chOperator)
{
	switch (chOperator)
	{
	case '(': case ')':
		return (0);
	case '+': case '-':
		return (1);
	case '*': case '/':
		return (2);
	}
}

char* ifTopf(const char* szParam)
{
	int index;
	int i;
	char ch;
	char topOP;
	char* pReturn;
	chStack newStack;
	initchStack(&newStack);

	index = 0;
	i = -1;
	pReturn = (char*)calloc(strlen(szParam) + 1, sizeof(char));
	while (szParam[++i])
	{
		ch = szParam[i];
		if (checkOP(ch) == 1)
		{
			while (!chEmpty(&newStack) && opPriority(ch) <= opPriority(chPeek(&newStack)))
			{
				pReturn[index] = chPop(&newStack);
				++index;
			}
			chPush(&newStack, ch);
		}
		else if (ch == '(')
			chPush(&newStack, ch);
		else if (ch == ')')
		{
			topOP = chPop(&newStack);
			if (topOP != '(')
			{
				pReturn[index] = topOP;
				++index;
			}
			while (chPeek(&newStack) != '(')
			{
				topOP = chPop(&newStack);
				pReturn[index] = topOP;
				index++;
			}
			chPop(&newStack);
		}
		else if (checkOP(ch) == 0)
		{
			pReturn[index] = ch;
			++index;
		}
		else if (checkOP(ch) == -1)
		{
			fprintf(stderr, "function is not valid\n");
			exit(-1);
		}
	}
	while (!chEmpty(&newStack))
	{
		pReturn[index] = chPop(&newStack, ch);
		++index;
	}
	return (pReturn);
}

int main(void)
{
	int result;

	result = 0;
	char* s = "4+(2+3)*4+9";
	printf("중위 표시 수식: %s\n", s);
	char* postFix = ifTopf(s);
	printf("후위 표시 수식: %s\n", postFix);
	result = calPost(postFix);
	printf("result is %d\n", result);

	return (0);
}
