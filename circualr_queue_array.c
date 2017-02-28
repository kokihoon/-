#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct ArrayQueueNodeType {
	char element;
}ArrayQueueNode;

typedef struct ArrayQueueType {
	int currentQueue;
	int maxQueue;
	int front;
	int rear;
	ArrayQueueNode *pElement;
}ArrayQueue;

ArrayQueue *createQueue(int maxElemenet) {
	ArrayQueue *pReturn = NULL;
	ArrayQueueNode *pNode = NULL;
	if (maxElemenet > 0) {
		pReturn = (ArrayQueue *)malloc(sizeof(ArrayQueue));

		if (pReturn != NULL) {
			memset(pReturn, 0, sizeof(ArrayQueue));
			pReturn->maxQueue = maxElemenet;
			pReturn->front = -1;
			pReturn->rear = -1;
		}
		else {
			printf("할당 오류\n");
			return NULL;
		}
	}
	else {
		printf("할당 오류\n");
		return NULL;
	}
	pReturn->pElement = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode)*maxElemenet);

	if (pReturn->pElement != NULL) {
		memset(pReturn->pElement, 0, sizeof(ArrayQueueNode)*maxElemenet);
	}
	else {
		printf("메모리 할당 오류");
		free(pReturn);
		return NULL;
	}
	return pReturn;
}
int isArrayQueueFull(ArrayQueue *pQueue) {
	int ret = FALSE;
	if (pQueue != NULL) {
		if (pQueue->currentQueue == pQueue->maxQueue) {
			ret = TRUE;
		}
	}
	return ret;
}
int isArrayQueueEmpty(ArrayQueue *pQueue) {
	int ret = FALSE;
	if (pQueue != NULL) {
		if (pQueue->currentQueue == 0) {
			ret = TRUE;
		}
	}
	return ret;
}
ArrayQueueNode *deQueue(ArrayQueue* pQueue) {
	ArrayQueueNode *pNode = NULL;
	if (pQueue != NULL) {
		if (isArrayQueueEmpty(pQueue) == FALSE) {
			pNode = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode));
			if (pNode != NULL) {
				pQueue->front = (pQueue->front +1)% pQueue->maxQueue;
				pNode->element = pQueue->pElement[pQueue->front].element;
				pQueue->currentQueue--;
			}
		}
	}
	return pNode;
}

ArrayQueueNode *Peek(ArrayQueue *pQueue) {
	ArrayQueueNode *pReturn = NULL;

	if (pQueue != NULL) {
		if (isArrayQueueEmpty(pQueue) == FALSE) {
			pReturn = &(pQueue->pElement[pQueue->front + 1]);
		}
	}
	return pReturn;
}
int enQueue(ArrayQueue *pQueue, ArrayQueueNode element) {
	int ret = FALSE;
	int i = 0;

	if (pQueue != NULL) {
		if (isArrayQueueFull(pQueue) == FALSE) {
			pQueue->rear = (pQueue->rear + 1) %pQueue->maxQueue;
			pQueue->pElement[pQueue->rear] = element;
			pQueue->currentQueue++;
			ret = TRUE;
		}
		else {
			printf("큐가 풀임\n");
		}
	}
	return ret;
}
int enQueueChar(ArrayQueue *pQueue, char data) {
	ArrayQueueNode node = { 0, };
	node.element = data;
	return enQueue(pQueue, node);
}
void display(ArrayQueue *pQueue) {
	int i = 0, maxElement = 0, pos = 0;
	if (pQueue != NULL) {
		printf("큐의 크기 : %d, 현재 노드 개수 : %d\n", pQueue->maxQueue, pQueue->currentQueue);
		maxElement = pQueue->front + pQueue->maxQueue;
		for (i = pQueue->front + 1; i <= maxElement; i++) {
			pos = i % pQueue->maxQueue;
			printf("[%d] - [%c]\n", pos, pQueue->pElement[pos].element);
		}
	}
}

void main() {
	ArrayQueue *pQueue = NULL;
	ArrayQueueNode *pNode = NULL;
	char value = 0;

	pQueue = createQueue(4);
	enQueueChar(pQueue, 'A');
	enQueueChar(pQueue, 'B');
	enQueueChar(pQueue, 'C');
	enQueueChar(pQueue, 'D');
	display(pQueue);

	pNode = deQueue(pQueue);
	if (pNode != NULL) {
		printf("%c\n", pNode->element);
		free(pNode);
	}
	display(pQueue);
	enQueueChar(pQueue, 'E');
	display(pQueue);

}