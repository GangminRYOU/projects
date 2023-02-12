#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct NODE
{
	char szName[60];
	int Kscore;
	int Escore;
	int Mscore;
	int nTotal;
	int nAverage;
	struct NODE* pNext;
} NODE;

NODE g_head = { 0 };
NODE* g_pTail = 0;
int IndexNode(void)
{
	int i = 0;
	NODE* pTmp = &g_head;
	while (pTmp->pNext != NULL)
	{
		pTmp = pTmp->pNext;
		++i;
	}
	return (i);
}

int IsEmpty(void)
{
	if (g_head.pNext == 0)
		return (1);
	else
		return (0);
}
void WriteData(NODE* pNode)
{
	int index = IndexNode();
	NODE spNode = { 0 };
	NODE* sp = &spNode;
	memcpy(pNode, sp, sizeof(NODE));
	printf("%d번째 학생 이름 : ", index);
	scanf_s("%s", pNode->szName, sizeof(pNode->szName));
	printf("\n");
	printf("국어 점수 : ");
	scanf_s("%d%*c", &(pNode->Kscore));
	printf("\n");
	printf("영어 점수 : ");
	scanf_s("%d%*c", &(pNode->Escore));
	printf("\n");
	printf("수학 점수 : ");
	scanf_s("%d%*c", &(pNode->Mscore));
	printf("\n");
	pNode->nTotal = pNode->Kscore + pNode->Escore + pNode->Mscore;
	pNode->nAverage = pNode->nTotal / 3;
}

void PushData(void)
{
	NODE* pNode;
	pNode = (NODE*)malloc(sizeof(NODE));
	WriteData(pNode);
	if (IsEmpty())
	{
		g_head.pNext = pNode;
		g_pTail = pNode;
	}
	else
	{
		pNode->pNext = g_head.pNext;
		g_head.pNext = pNode;
	}
}


void PrintTable(void)
{
	printf("----------------------------------------");
	printf("\n");
	printf("  이름  국어  영어  수학  총점  평균  등수");
	printf("\n");
	printf("----------------------------------------");
	printf("\n");
}


void InnerSort(NODE* IScurrent)
{
		
	NODE* ISnext = IScurrent->pNext;
	NODE* pPrev = &g_head;
	while (IScurrent->pNext != NULL)
	{
		if (IScurrent->nTotal > ISnext->nTotal)
		{
			IScurrent->pNext = ISnext->pNext;
			pPrev->pNext = ISnext;
			ISnext->pNext = IScurrent;
		}
		pPrev = IScurrent;
		IScurrent = ISnext;
		ISnext = IScurrent->pNext;
	}
}

void SortList(void)
{
	NODE* OTcurrent = g_head.pNext;
	while (OTcurrent != NULL)
	{
		InnerSort(OTcurrent);
		OTcurrent = OTcurrent->pNext;
	}
}

int PopNode(NODE *Npop)
{
	if (IsEmpty())
		return (0);
	NODE* sp = g_head.pNext;
	memcpy(Npop, sp, sizeof(NODE));
	g_head.pNext = sp->pNext;
	free(sp);
	return (1);
}

void PopList(void)
{
	PrintTable();
	NODE pNode = { 0 };
	int i = 1;
	SortList();
	while (PopNode(&pNode) != 0)
	{
		printf("  %s  ", pNode.szName);
		printf("%d  ", pNode.Kscore);
		printf("%d  ", pNode.Escore);
		printf("%d  ", pNode.Mscore);
		printf("%d  ", pNode.nTotal);
		printf("%d  ", pNode.nAverage);
		printf("%d등  ", i);
		printf("\n");
		++i;
	}

}

void recurMenu(void)
{
	int SelectMenu = 0;
	printf("[ Menu ]\n1. 성적 입력\n2. 성적 확인\n3. 종료");
	printf("선택 ( 1 ~ 3 ) : ");
	scanf_s("%d", &SelectMenu);
	if (SelectMenu == 1)
		PushData();
	else if (SelectMenu == 2)
		PopList();
	else if (SelectMenu == 3)
		return ;
	else
	{
		printf("적절한 값을 입력하시오.");
		return ;
	}
	recurMenu();
}


int main(void)
{
	recurMenu();
	return (0);
}
