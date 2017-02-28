#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct ArrayStackNodeType {
	char data;
}ArrayStackNode;

typedef struct ArrayStackType {
	int maxCount;
	int currentCount;
	ArrayStackNode *pElement;
}ArrayStack;

ArrayStack *createStack(int size) {
	ArrayStack *pReturn = NULL;
	int i = 0;

	if (size > 0) {
		pReturn = (ArrayStack *)malloc(sizeof(ArrayStack));
		if (pReturn != NULL) {
			memset(pReturn, 0, sizeof(ArrayStack));
			pReturn->maxCount = size;
		}
		else {
			printf("���� �޸� �Ҵ�");
			return NULL;
		}
		pReturn->pElement = (ArrayStackNode *)malloc(sizeof(ArrayStackNode)*size);
		if (pReturn->pElement != NULL) {
			memset(pReturn->pElement, 0, sizeof(ArrayStackNode)*size);
		}
		else {
			printf("���� �޸� �Ҵ�");
			free(pReturn);
			return NULL;
		}
	}
	else {
		printf("���� ���� 0 �̻��̿�����");
		return NULL;
	}
	return pReturn;
}

void Push(ArrayStack *pStack, ArrayStackNode element) {
	if (pStack != NULL) {
		if (isArrayStackFull(pStack) == 0) {
			pStack->pElement[pStack->currentCount] = element;
			pStack->currentCount++;
		}
		else {
			printf("���� �� á���ϴ�.");
		}
	}
}
ArrayStackNode * Pop(ArrayStack *pStack) {
	ArrayStackNode *pNode = NULL;
	if (pStack != NULL) {
		if (isArrayStackFull(pStack) == 0) {
			pNode = (ArrayStackNode *)malloc(sizeof(ArrayStackNode));
			if (pNode != NULL) {
				*pNode = pStack->pElement[pStack->currentCount - 1];
				pStack->currentCount--;
			}
			else {
				printf("�޸� �Ҵ� ����");
			}
		}
	}
	return pNode;
}

ArrayStackNode *Peek(ArrayStack *pStack) {
	ArrayStackNode *pNode = NULL;
	
	if (pStack != NULL) {
		if (isArrayStackFull(pStack) == 0) {
			pNode = (ArrayStackNode *)malloc(sizeof(ArrayStackNode));
			if (pNode != NULL) {
				*pNode = pStack->pElement[pStack->currentCount - 1];
			}
		}
	}
	return pNode;
}

int isArrayStackFull(ArrayStack *pStack) {

	if (pStack != NULL) {
		if (pStack->currentCount == pStack->maxCount) {
			return 1;
		}
	}
	return 0;
}

void display(ArrayStack *pStack) {
	int size, top, i;
	size = pStack->maxCount;
	top = pStack->currentCount;

	printf("���� ũ�� : %d, ���� ��� ���� : %d\n", size, top);

	for (i = size-1; i >= top; i--) {
		printf("[%d] - [empty]\n", i);
	}

	for (i = top-1; i >= 0; i--) {
		printf("[%d] - [%c]\n", i, pStack->pElement[i].data);
	}
}
void main() {

	ArrayStack *pStack = NULL;
	ArrayStackNode *pNode = NULL;

	char value = 0;
	pStack = createStack(6);
	if (pStack != NULL) {
		ArrayStackNode NodeA = { 'A' };
		ArrayStackNode NodeB = { 'B' };
		ArrayStackNode NodeC = { 'C' };
		ArrayStackNode NodeD = { 'D' };

		Push(pStack, NodeA);
		Push(pStack, NodeB);
		Push(pStack, NodeC);
		Push(pStack, NodeD);

		display(pStack);

		pNode = Pop(pStack);
		if (pNode != NULL) {
			printf("pop�� [%c]\n", pNode->data);
			free(pNode);
		}
		pNode = Pop(pStack);
		if (pNode != NULL) {
			printf("pop�� [%c]\n", pNode->data);
			free(pNode);
		}
		pNode = Peek(pStack);
		if (pNode != NULL) {
			printf("peek�� [%c]\n", pNode->data);
		}
		display(pStack);
		Push(pStack, NodeD);
		display(pStack);
		pNode = Peek(pStack);
		if (pNode != NULL) {
			printf("peek�� [%c]\n", pNode->data);
		}
	}
}