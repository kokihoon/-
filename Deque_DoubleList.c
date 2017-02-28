#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct DequeNodeType {
	char data;
	struct DequeNodeType* pLLink;
	struct DequeNodeType* pRLink;
}DequeNode;

typedef struct LinkedDequeType {
	int currentCount;
	DequeNode *pFrontNode;
	DequeNode *pRearNode;
} LinkedDeque;

LinkedDeque* Create() {
	LinkedDeque* pReturn = NULL;

	pReturn = (LinkedDeque*)malloc(sizeof(LinkedDeque));

	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(LinkedDeque));
	}
	else {
		printf("메모리 오류 할당 실패\n");
		return NULL;
	}
	return pReturn;
}

int insertFront(LinkedDeque *pDeque, DequeNode element) {
	int ret = FALSE;
	DequeNode *pNode = NULL;

	if (pDeque != NULL) {
		pNode = (DequeNode*)malloc(sizeof(DequeNode));
		if (pNode != NULL) {
			*pNode = element;
			pNode->pLLink = NULL;
			pNode->pRLink = NULL;
			if (pDeque->currentCount == 0) {
				pDeque->pFrontNode = pNode;
				pDeque->pRearNode = pNode;
			}
			else {
				pNode->pRLink = pDeque->pFrontNode;
				pDeque->pFrontNode->pLLink = pNode;
				pDeque->pFrontNode = pNode;
			}
			pDeque->currentCount++;
			ret = TRUE;
		}
		else {
			printf("메모리 할당 오류\n");
		}
	}
	return ret;
}

int insertRear(LinkedDeque *pDeque, DequeNode element) {
	int ret = FALSE;
	DequeNode *pNode = NULL;

	if (pDeque != NULL) {
		pNode = (DequeNode *)malloc(sizeof(DequeNode));
		if (pNode != NULL) {
			*pNode = element;
			pNode->pLLink = NULL;
			pNode->pRLink = NULL;
			if (pDeque->currentCount == 0) {
				pDeque->pFrontNode = pNode;
				pDeque->pRearNode = pNode;
			}
			else {
				pNode->pLLink = pDeque->pRearNode;
				pDeque->pRearNode->pRLink = pNode;
				pDeque->pRearNode = pNode;
			}
			pDeque->currentCount++;
			ret = TRUE;
		}
		else {
			printf("메모리 할당 오류\n");
		}
	}
	return ret;
}

DequeNode *deleteFront(LinkedDeque *pDeque) {
	DequeNode *pNode = NULL;

	if (pDeque != NULL) {
		if (pDeque->currentCount == 0) {
			return pNode;
		}
		else {
			if (pDeque->currentCount == 1) {
				pNode = pDeque->pFrontNode;
				pDeque->pFrontNode = NULL;
				pDeque->pRearNode = NULL;
			}
			else {
				pNode = pDeque->pFrontNode;
				pDeque->pFrontNode = pDeque->pFrontNode->pRLink;
				pNode->pRLink = NULL;
				pDeque->pFrontNode->pLLink = NULL;
			}
			pDeque->currentCount--;
		}
	}
	return pNode;
}

DequeNode *PeekFront(LinkedDeque* pQueue) {
	DequeNode *pNode = NULL;

	if (pQueue != NULL) {
		if (pQueue->currentCount != 0) {
			pNode = pQueue->pFrontNode;
		}
	}
	return pNode;
}

DequeNode *deleteRear(LinkedDeque *pQueue) {
	DequeNode *pNode = NULL;

	if (pQueue != NULL) {
		if (pQueue->currentCount == 0) {
			return NULL;
		}
		else {
			if (pQueue->currentCount == 1) {
				pNode = pQueue->pRearNode;
				pQueue->pFrontNode = NULL;
				pQueue->pRearNode = NULL;
			}
			else {
				pNode = pQueue->pRearNode;
				pQueue->pRearNode = pNode->pLLink;
				pNode->pLLink->pRLink = NULL;
			}
			pQueue->currentCount--;
		}
	}
	return pNode;
}

DequeNode *PeekRear(LinkedDeque *pQueue) {
	DequeNode *pNode = NULL;

	if (pQueue != NULL) {
		if (pQueue->currentCount != 0) {
			pNode = pQueue->pRearNode;
		}
	}
	return pNode;
}

int insertFrontChar(LinkedDeque *pQueue, char data) {
	DequeNode node = { 0, };
	node.data = data;

	return insertFront(pQueue, node);
}
int insertRearChar(LinkedDeque *pQueue, char data) {
	DequeNode node = { 0, };
	node.data = data;

	return insertRear(pQueue, node);
}

void Display(LinkedDeque *pQueue) {
	DequeNode *pNode = NULL;
	int i = 0;
	if (pQueue != NULL) {
		printf("현제 노드 개수 : %d\n", pQueue->currentCount);
		pNode = pQueue->pFrontNode;
		while (pNode != NULL) {
			printf("[%d] - [%c] \n", i++, pNode->data);
			pNode = pNode->pRLink;
		}
	}
}

void main() {
	LinkedDeque *pDeque = NULL;
	DequeNode *pNode = NULL;

	pDeque = Create();

	if (pDeque != NULL) {
		insertFrontChar(pDeque, 'A');
		insertFrontChar(pDeque, 'B');
		insertRearChar(pDeque, 'C');
		insertRearChar(pDeque, 'D');
		Display(pDeque);
		pNode = deleteFront(pDeque);
		if (pNode != NULL) {
			printf("delete front : %c\n", pNode->data);
		}
		Display(pDeque);
		pNode = deleteRear(pDeque);
		if (pNode != NULL) {
			printf("delete rear : %c\n", pNode->data);
		}
		Display(pDeque);
		pNode = deleteRear(pDeque);
		if (pNode != NULL) {
			printf("delete rear : %c\n", pNode->data);
		}
		Display(pDeque);
		pNode = deleteFront(pDeque);
		if (pNode != NULL) {
			printf("delete rear : %c\n", pNode->data);
		}
		Display(pDeque);
	}
}