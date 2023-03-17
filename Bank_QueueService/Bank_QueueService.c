#include"MyQueue.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
	int nMin = 60;
	int totalWait1 = 0;
	int totalWait2 = 0;
	int totalCustomer1 = 0;
	int totalCustomer2 = 0;
	int serviceTime1 = 0;
	int serviceCustomer1 = 0;
	int serviceTime2 = 0;
	int serviceCustomer2 = 0;
	int customNo = 0;
	Qtype bankQ1;
	Qtype bankQ2;

	initQueue(&bankQ1);
	initQueue(&bankQ2);
	srand(time(NULL));
	for (int clock = 0; clock < nMin; clock++)
	{
		if (rand() % 10 < 3)
		{
			element customInfo;
			customInfo.arrivalTime = clock;
			customInfo.serviceTime = rand() % 3 + 1;
			customInfo.id = customNo++;
			//Q1 대기줄이 Q2대기줄 보다 짧거나 같으면, Q1으로
			if (bankQ1.qCount <= bankQ2.qCount)
			{
				Enqueue(&bankQ1, customInfo);
				totalCustomer1++;
				printf("고객 %d님이 대기열 1번에 %d분에 들어왔습니다. 업무처리 시간: %d\n",
				customInfo.id, customInfo.arrivalTime, customInfo.serviceTime);
			}
			//Q2대기줄이 짧으면 Q2로
			else
			{
				Enqueue(&bankQ2, customInfo);
				totalCustomer2++;
				printf("고객 %d님이 대기열 2번에 %d분에 들어왔습니다. 업무처리 시간: %d\n",
					customInfo.id, customInfo.arrivalTime, customInfo.serviceTime);
			}

		}
		//대기열 둘다 찬 상황
		if (serviceTime1 > 0)
		{
			printf("고객 %d 대기열 1번에서 업무 처리중 입니다.\n", serviceCustomer1);
			serviceTime1--;
		}
		if (serviceTime2 > 0)
		{
			printf("고객 %d 대기열 2번에서 업무 처리중 입니다.\n", serviceCustomer2);
			serviceTime2--;
		}
		//둘중 하나는 비거나 둘다 빈 상황
			//둘다 비면 Q1으로
		if (!isEmpty(&bankQ1) && serviceTime1 == 0)
		{
				element currentCustom = Dequeue(&bankQ1);
				serviceTime1 = currentCustom.serviceTime;
				serviceCustomer1 = currentCustom.id;
				totalWait1 += clock - currentCustom.arrivalTime;
				printf("고객 %d님이 %d분에 대기열 1번에서 업무를 시작합니다. 대기 시간은 %d분이었습니다.\n",
					currentCustom.id, clock, clock - currentCustom.arrivalTime);
		}
		//Q2만 비면 Q2로
		if(!isEmpty(&bankQ2) && serviceTime2 == 0)
		{
				element currentCustom = Dequeue(&bankQ2);
				serviceTime2 = currentCustom.serviceTime;
				serviceCustomer2 = currentCustom.id;
				totalWait2 += clock - currentCustom.arrivalTime;
				printf("고객 %d님이 %d분에 대기열 2번에서 업무를 시작합니다. 대기 시간은 %d분이었습니다.\n",
					currentCustom.id, clock, clock - currentCustom.arrivalTime);
		}
	}
	printf("전체 대기시간 : %d분", totalWait1 + totalWait2);

	return (0);
}

