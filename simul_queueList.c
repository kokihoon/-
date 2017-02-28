#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef enum SistatusType {arrival, start, end} SimStatus;

typedef struct SimCustomerType {
	SimStatus status;
	int arrivalTime;
	int serviceTime;
	int startTime;
	int endTime;
} SimCustomer;

typedef struct QueueNodeType {
	SimCustomer data;
	struct QueueNodeType *pLink;
}QueueNode;

typedef struct LinkedQueueType {
	int currentCount;
	QueueNode *pFrontNode;
	QueueNode *pRearNode;
}LinkedQueue;
void printSimCustomer(int currentTime, SimCustomer customer);
int isLinkedQueueEmpty(LinkedQueue *pWaitQueue);
LinkedQueue *create() {
	LinkedQueue *pReturn = NULL;

	pReturn = (LinkedQueue *)malloc(sizeof(LinkedQueue));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(LinkedQueue));

	}
	else {
		printf("�޸� �Ҵ� ����\n");
	}
	return pReturn;
}
int enQueue(LinkedQueue *pQueue, QueueNode element) {
	QueueNode *pNode = NULL;
	int ret = FALSE;
	if (pQueue != NULL) {
		pNode = (QueueNode *)malloc(sizeof(QueueNode));
		*pNode = element;
		pNode->pLink = NULL;
		if (pNode != NULL) {
			if (pQueue->currentCount == 0) {
				pQueue->pFrontNode = pNode;
				pQueue->pRearNode = pNode;
			}
			else {
				pQueue->pRearNode->pLink = pNode;
				pQueue->pRearNode = pNode;
			}
			pQueue->currentCount++;
			ret = TRUE;
		}
		else {
			printf("�޸� �Ҵ� ����");
		}
	}
	return ret;
}
QueueNode *PeekQueue(LinkedQueue *pQueue) {
	QueueNode *pReturn = NULL;

	if (pQueue != NULL) {
		if (pQueue->currentCount != 0) {
			pReturn = pQueue->pFrontNode;
		}
	}
	return pReturn;
}
QueueNode *deQueue(LinkedQueue* pQueue) {
	QueueNode *pReturn = NULL;

	if (pQueue != NULL) {
		if (pQueue->currentCount != 0) {
			pReturn = pQueue->pFrontNode;
			pQueue->pFrontNode = pQueue->pFrontNode->pLink;
			pReturn->pLink = NULL;
			pQueue->currentCount--;
			if (pQueue->currentCount == 0) {
				pQueue->pRearNode = NULL;
			}
		}
	}
	return pReturn;
}
void insertCutomer(int arrvalTime, int serviceTime, LinkedQueue *pQueue) {
	if (pQueue != NULL) {
		QueueNode node = { 0, };
		node.data.status = arrival;
		node.data.arrivalTime = arrvalTime;
		node.data.serviceTime = serviceTime;
		node.data.startTime = 0;
		node.data.endTime = 0;
		enQueue(pQueue, node);
	}
}
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue) {
	QueueNode *pArrivalNode = NULL;
	int isEmpty = 0;
	isEmpty = isLinkedQueueEmpty(pArrivalQueue);
	while (isEmpty == FALSE) {
		pArrivalNode = PeekQueue(pArrivalQueue);
		if (pArrivalNode->data.arrivalTime == currentTime) {
			enQueue(pWaitQueue, *pArrivalNode);
			printSimCustomer(currentTime, pArrivalNode->data);
			free(deQueue(pArrivalQueue));
		}
		else {
			break;
		}
		isEmpty = isLinkedQueueEmpty(pArrivalQueue);
	}
}
void printSimCustomer(int currentTime, SimCustomer customer) {
	printf("[%d], ", currentTime);

	switch (customer.status) {
	case arrival :
		printf("������\n");
		break;
	case start :
		printf("���� ����");
		printf(",����-%d, ��� �ð�-%d\n", customer.arrivalTime, (customer.startTime - customer.arrivalTime));
		break;

	case end :
		printf("���� ����");
		printf(", ����-%d, ����-%d, ���ð�-%d, ���� �ð�-%d\n", customer.arrivalTime, customer.startTime, (customer.startTime - customer.arrivalTime), (customer.endTime-customer.startTime));
		break;
	}
}

QueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue) {
	QueueNode *pReturn = NULL;
	QueueNode *pServiceNode = NULL;
	int isEmpty = 0;

	if (pWaitQueue == NULL) {
		return NULL;
	}

	isEmpty = isLinkedQueueEmpty(pWaitQueue);
	if (isEmpty == FALSE) {
		pServiceNode = deQueue(pWaitQueue);
		if (pServiceNode != NULL) {
			pServiceNode->data.status = start;
			pServiceNode->data.startTime = currentTime;
			printSimCustomer(currentTime, pServiceNode->data);
			pReturn = pServiceNode;
		}
	}
	return pReturn;
}
int isLinkedQueueEmpty(LinkedQueue *pWaitQueue) {
	int ret = FALSE;
	if (pWaitQueue != NULL) {
		if (pWaitQueue->currentCount == 0) {
			ret = TRUE;
		}
	}
	return ret;
}

void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue) {
	printf("[%d], ���� ��� �� ��: %d\n", currentTime, pWaitQueue->currentCount);
}

void printReport(LinkedQueue *pWaitQueue, int serviceUserCount, int totalWaitTime) {
	printf("REPORT");
	printf("���� �� �� : %d\n", serviceUserCount);
	if (serviceUserCount > 0) {
		printf("��� ��� �ð�:%f\n", ((float)totalWaitTime / (float)serviceUserCount));
	}
	printf("���� ��� ���� ���� : %d\n", pWaitQueue->currentCount);
}

int LinkedQueueEmpty(LinkedQueue *pArrivalQueue) {
	int ret = FALSE;
	if (pArrivalQueue->currentCount == 0) {
		ret = TRUE;
	}
	return ret;
}
QueueNode *processServiceNodeEnd(int currentTime, QueueNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime) {
	int endTime = 0;
	int waitTime = 0;
	QueueNode *pReturn = NULL;

	if (pServiceNode == NULL || pServiceUserCount == NULL || pTotalWaitTime == NULL) {
		return NULL;
	}

	endTime = pServiceNode->data.startTime + pServiceNode->data.serviceTime;
	if (endTime <= currentTime) {
		waitTime = pServiceNode->data.startTime - pServiceNode->data.arrivalTime;

		(*pServiceUserCount)++;
		(*pTotalWaitTime) += waitTime;

		pServiceNode->data.status = end;
		pServiceNode->data.endTime = currentTime;
		printSimCustomer(currentTime, pServiceNode->data);

		free(pServiceNode);

		pReturn = NULL;

	}
	else {
		pReturn = pServiceNode;
	}
	return pReturn;
}

void main() {
	int currentTime = 0;
	int endTime = 10;
	int serviceUserCount = 0;
	int totalWaitTime = 0;

	LinkedQueue *pArrivalQueue = NULL, *pWaitQueue = NULL;
	QueueNode *pServiceNode1 = NULL;

	pArrivalQueue = create();
	pWaitQueue = create();

	if (pArrivalQueue != NULL && pWaitQueue == NULL){
		printf("����\n");
	}
	insertCutomer(0, 3, pArrivalQueue);   // ���� �ð� 0, ���� �ð� 3
	insertCutomer(2, 2, pArrivalQueue);
	insertCutomer(4, 1, pArrivalQueue);
	insertCutomer(6, 1, pArrivalQueue);
	insertCutomer(8, 3, pArrivalQueue);

	for (currentTime = 0; currentTime < endTime; currentTime++) {
		processArrival(currentTime, pArrivalQueue, pWaitQueue);
		if (pServiceNode1 != NULL) {
			pServiceNode1 = processServiceNodeEnd(currentTime, pServiceNode1, &serviceUserCount, &totalWaitTime);
		}

		if (pServiceNode1 == NULL) {
			pServiceNode1 = processServiceNodeStart(currentTime, pWaitQueue);
		}
		printWaitQueueStatus(currentTime, pWaitQueue);
	}
	printReport(pWaitQueue, serviceUserCount, totalWaitTime);
}