#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct QueueNodeType {
	char data;
	struct QueueNodeType* pLink;

}QueueNode;

typedef struct LinkedQueueType {
	int currentCount;
	QueueNode *pFrontNode;
	QueueNode *pRearNode;
} LinkedQueue;

LinkedQueue *create() {
	LinkedQueue *pReturn = NULL;

	pReturn = (LinkedQueue *)malloc(sizeof(LinkedQueue));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(LinkedQueue));

	}
	else {
		printf("메모리 할당 오류", create());
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
			printf("메모리 할당 오류");
		}
	}
	return ret;
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
QueueNode *PeekQueue(LinkedQueue *pQueue) {
	QueueNode *pReturn = NULL;

	if (pQueue != NULL) {
		if (pQueue->currentCount != 0) {
			pReturn = pQueue->pFrontNode;
		}
	}
	return pReturn;
}

void display(LinkedQueue *pQueue) {
	QueueNode *pNode = NULL;
	int i = 0;
	if (pQueue != NULL) {
		pNode = pQueue->pFrontNode;
		printf("현재 큐 개수 : %d\n", pQueue->currentCount);

		while (pNode != NULL) {
			printf("[%d] - [%c]\n", i++, pNode->data);
			pNode = pNode->pLink;
		}
	}
}
int enQueueChar(LinkedQueue *pQueue, char data) {
	QueueNode node = { 0, };
	node.data = data;
	return enQueue(pQueue, node);
}
void main() {
	char value = 0;
	QueueNode *pNode = NULL;
	LinkedQueue *pQueue = NULL;
	pQueue = create();
	enQueueChar(pQueue, 'A');
	enQueueChar(pQueue, 'B');
	enQueueChar(pQueue, 'C');
	enQueueChar(pQueue, 'D');
	display(pQueue);

	pNode = deQueue(pQueue);
	if (pNode != NULL) {
		printf("%c\n", pNode->data);
		free(pNode);
	}
	display(pQueue);
	enQueueChar(pQueue, 'E');
	display(pQueue);

}