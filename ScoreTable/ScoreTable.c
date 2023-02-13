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

typedef struct IDXL
{
	int idx;
	NODE* origin;
	struct IDXL* idxNext;
} IDXL;



IDXL* g_sortHead = NULL;
NODE g_head = { 0 };
NODE* g_pTail = 0;

int NodeLength(void)
{
	int i = 1;
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
	int index = NodeLength();
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

void IndexSort(NODE *pCurrent)
{
	IDXL* pIdx = (IDXL*)malloc(sizeof(IDXL));
	IDXL zIdx = { 0 };
	IDXL* clear = &zIdx;
	memcpy(pIdx, clear, sizeof(IDXL));
	pIdx->origin = pCurrent;
	IDXL* cSort = g_sortHead;
	IDXL* prevSort = g_sortHead;
	//인덱스 리스트가 비어있을 경우
	if (g_sortHead == NULL)
	{
		g_sortHead = pIdx;
	}
	//비어있지 않을 경우
	else
	{
		//가장 큰 값의 경우
		if (pIdx->origin->nTotal > g_sortHead->origin->nTotal)
		{
			pIdx->idxNext = g_sortHead;
			g_sortHead = pIdx;
		}
		//가장 큰 값이 아닌 경우
		else
		{
			while (cSort != NULL && pCurrent->nTotal < cSort->origin->nTotal)
			{
				prevSort = cSort;
				cSort = cSort->idxNext;
			}
			pIdx->idxNext = cSort;
			prevSort->idxNext = pIdx;
		}
	}
}

int SortedList(void)
{
	NODE* pCur = g_head.pNext;
	while (pCur != NULL)
	{
		IndexSort(pCur);
		pCur = pCur->pNext;
	}
	return (1);
}

void ReleaseIndex(void)
{
	IDXL* pIdxList = g_sortHead;

	while (pIdxList != NULL)
	{
		IDXL* pIdxDelete = pIdxList;
		pIdxList = pIdxList->idxNext;
		free(pIdxDelete);
	}
	g_sortHead = NULL;
}

void PopList(void)
{
	PrintTable();
	SortedList();
	IDXL* pCurrent = g_sortHead;
	int i = 1;
	while (pCurrent != 0)
	{
		printf("  %s  ", pCurrent->origin->szName);
		printf("%d  ", pCurrent->origin->Kscore);
		printf("%d  ", pCurrent->origin->Escore);
		printf("%d  ", pCurrent->origin->Mscore);
		printf("%d  ", pCurrent->origin->nTotal);
		printf("%d  ", pCurrent->origin->nAverage);
		printf("%d등  ", i);
		printf("\n");
		++i;
		pCurrent = pCurrent->idxNext;
	}
	ReleaseIndex();
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

void ReleaseList(void)
{
	NODE* pCurrent = g_head.pNext;
	while (pCurrent != NULL)
	{
		NODE* pDelete = pCurrent;
		pCurrent = pCurrent->pNext;
		printf("Deleting %s's score...\n", pDelete->szName);
		free(pDelete);
	}
	ReleaseIndex();
	puts("List Successfully Released\n");
	
	g_head.pNext = NULL;
	g_pTail = NULL;
	g_sortHead = NULL;
}


int main(void)
{
	recurMenu();
	ReleaseList();
	return (0);
}
