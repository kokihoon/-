#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct HeapElementType {
	int key;
	char data;
}HeapNode;

typedef struct ArrayHeapNode {
	int maxElementCount;
	int currentElementCount;
	HeapNode *pElement;
} ArrayMaxHeap, ArrayMinHeap;

ArrayMaxHeap* CreateArrayMaxHeap(int maxElementCount) {
	ArrayMaxHeap *pReturn = NULL;
	int i = 0;

	if (maxElementCount > 0) {
		pReturn = (ArrayMaxHeap *)malloc(sizeof(ArrayMaxHeap));
		if (pReturn->pElement != NULL) {

			pReturn->currentElementCount = 0;
			pReturn->maxElementCount = maxElementCount;
			pReturn->pElement = (HeapNode *)malloc(sizeof(HeapNode)*(maxElementCount + 1));
			if (pReturn->pElement == NULL) {
				printf("메모리 할당 오류\n");
				free(pReturn);
				return NULL;
			}
			memset(pReturn->pElement, 0, sizeof(HeapNode)*(maxElementCount + 1));
		}
		else {
			printf("메모리 할당 오류\n");
		}
	}
	else {
		printf("최대 노드 개수 0개 보다 커야됨\n");
	}
	return pReturn;
}

void insertMaxHeapAH(ArrayMaxHeap *pHeap, HeapNode element) {
	int i = 0;

	if (pHeap != NULL) {
		if (pHeap->currentElementCount == pHeap->maxElementCount) {
			printf("히프가 가득찼습니다.\n");
			return;
		}
		pHeap->currentElementCount++;
		i = pHeap->currentElementCount;

		while ((i != 1) && (element.key > pHeap->pElement[i / 2].key)) {
			pHeap->pElement[i] = pHeap->pElement[i / 2];
			i /= 2;
		}
		pHeap->pElement[i] = element;

	}
}

HeapNode *deleteMaxHeapAH(ArrayMaxHeap *pHeap) {
	HeapNode *pReturn = NULL;
	HeapNode *pTemp = NULL;
	int i = 0, parent = 0, child = 0;
	if (pHeap != NULL) {
		pReturn = (HeapNode *)malloc(sizeof(HeapNode));
		*pReturn = pHeap->pElement[1];
		i = pHeap->currentElementCount;
		pTemp = &(pHeap->pElement[i]);
		pHeap->currentElementCount--;

		parent = 1;
		child = 2;
		while (child <= pHeap->currentElementCount) {
			if ((child < pHeap->currentElementCount) && pHeap->pElement[child].key < pHeap->pElement[child + 1].key) {
				child++;
			}
			if (pTemp->key >= pHeap->pElement[child].key) {
				break;
			}
			pHeap->pElement[parent] = pHeap->pElement[child];
			parent = child;
			child *= 2;

		}
		pHeap->pElement[parent] = *pTemp;
	}
	return pReturn;
}

void display(ArrayMaxHeap *pHeap) {
	int i = 0;
	for (i = 0; i < pHeap->currentElementCount; i++) {
		printf("[%d], %d\n", i, pHeap->pElement[i]);
	}
}

void main() {
	int maxHeapSize = 20;

	ArrayMaxHeap *pHeap = NULL;
	HeapNode *pNode = NULL;
	HeapNode e1 = { 10 };
	HeapNode e2 = { 40 };
	HeapNode e3 = { 30 };
	HeapNode e4 = { 20 };
	HeapNode e5 = { 50 };
	HeapNode e6 = { 100 };
	pHeap = CreateArrayMaxHeap(maxHeapSize);
	if (pHeap != NULL) {
		insertMaxHeapAH(pHeap, e1);
		insertMaxHeapAH(pHeap, e2);
		insertMaxHeapAH(pHeap, e3);
		insertMaxHeapAH(pHeap, e4);
		insertMaxHeapAH(pHeap, e5);
		insertMaxHeapAH(pHeap, e6);
		printf("Max Heap:\n");
		display(pHeap);

		pNode = deleteMaxHeapAH(pHeap);
		if (pNode != NULL) {
			printf("delete[%d]\n", pNode->key);
			free(pNode);
		}

		printf("max Heap\n");
		display(pHeap);
	}
}