#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNodeType {
	char data;
	struct StackNodeType *pLink;
} StackNode;

typedef struct StackType {
	int currentCount;
	struct StackType *pTopElement;
}LinkedStack;
LinkedStack *createStack();
void PushList(LinkedStack *pStack, StackNode Node);
void display(LinkedStack *pStack);
StackNode *Pop(LinkedStack *pStack);
char *reverseString(char *pSource);
int checkBracketMatching(char *pSource);
void PushList(LinkedStack *pStack, StackNode Node) {
	StackNode *pNode = NULL;

	if (pStack != NULL) {
		pNode = (StackNode* )malloc(sizeof(StackNode));
		if (pNode != NULL) {
			memset(pNode, 0, sizeof(StackNode));
			*pNode = Node;
			pNode->pLink = pStack->pTopElement;
			pStack->pTopElement = pNode;
			pStack->currentCount++;

		}
		else {
			printf("메모리 할당 오류");
		}
	}
}
char *reverseString(char *pSource) {
	char *pReturn = NULL;
	int i = 0, size = 0;
	LinkedStack *pStack = NULL;
	StackNode *pNode = NULL;

	if (pSource == NULL) {
		return NULL;
	}
	size = strlen(pSource);
	if (size == 0) {
		return NULL;
	}
	pReturn = (char *)malloc(sizeof(char)*(size + 1));
	if (pReturn == NULL) {
		printf("메모리 할당 오류");
		return NULL;
	}

	pStack = createStack();
	if (pStack != NULL) {
		StackNode node;

		for (i = 0; i < size; i++) {
			node.data = pSource[i];
			PushList(pStack, node);
		}
		for (i = 0; i < size; i++) {
			pNode = Pop(pStack);
			if (pNode != NULL) {
				pReturn[i] = pNode->data;
				free(pNode);
			}
		}
		pReturn[i] = '\0';
	}
	return pReturn;
}
StackNode *Pop(LinkedStack *pStack) {
	StackNode *pNode = NULL;

	if (pStack != NULL) {
		pNode = pStack->pTopElement;
		printf("pop : %c\n", pNode->data);
		pStack->pTopElement = pNode->pLink;
	}
	return pNode;
}
LinkedStack *createStack() {
	LinkedStack *pReturn = NULL;
	int i = 0;

	pReturn = (LinkedStack *)malloc(sizeof(LinkedStack));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(LinkedStack));
	}
	else {
		printf("메모리 할당 오류");
		return NULL;
	}
	return pReturn;
}
void display(LinkedStack *pStack) {
	StackNode *Node = NULL;
	int i;
	if (pStack != NULL) {
		Node = pStack->pTopElement;
		i = pStack->currentCount;
		while (Node != NULL) {
			printf("[%d]-[%c]\n", i--, Node->data);
			Node = Node->pLink;
		}
	}
}
int checkBracketMatching(char *pSource) {
	int size = 0, i, ret = 0;

	char symbol = '\0', checkSymbol = '\0';
	LinkedStack *pStack = NULL;
	StackNode *pNode = NULL;

	if (pSource == NULL) {
		return 1;
	}
	size = strlen(pSource);
	if(size == 0) {
		return 1;
	}
	pStack = createStack();
	if (pStack != NULL) {
		StackNode node;
		for (i = 0; i < size && ret == 0; i++) {
			symbol = pSource[i];
			switch (symbol) {
			case '(' :
			case '[' :
			case '{' :
				node.data = symbol;
				PushList(pStack, node);
				break;

			case ')' :
			case ']' :
			case '}' :
				pNode = Pop(pStack);
				if (pNode == NULL) {
					ret = 1;
					break;
				}
				else {
					checkSymbol = pNode->data;
					if ((symbol == ')' && checkSymbol == '(') || (symbol == ']' && checkSymbol == '[') || (symbol == '}' && checkSymbol == '{')) {

					}
					else {
						ret = 1;

					}
					free(pNode);
				}
				break;
			}
		}
	}
	else {
		printf("오류 ");
		ret = 1;
	}
	return ret;
}
void main() {
	LinkedStack *pStack = NULL;
	char sourceStr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char successExprStr[] = "((A*B)/C)-{(D+E)&&(F-G)}";
	char failExprStr[] = "((A*B)/C-{(D+E)&&(F-G))}";
	int checkResult = 0;

	pStack = createStack();
	StackNode NodeA = { 'A' };
	StackNode NodeB = { 'B' };
	StackNode NodeC = { 'C' };
	StackNode NodeD = { 'D' };
	StackNode NodeE = { 'E' };

	checkResult = checkBracketMatching(successExprStr);
	if (checkResult == 0) {
		printf("SUCCESS, %s\n", successExprStr);
	}
	else {
		printf("FAIL, %s\n", successExprStr);
	}

	checkResult = checkBracketMatching(failExprStr);
	if (checkResult == 0) {
		printf("SUCCESS, %s\n", failExprStr);
	}
	else {
		printf("FAIL, %s\n", failExprStr);
	}

//	PushList(pStack, NodeA);
	//PushList(pStack, NodeB);
//	PushList(pStack, NodeC);
//	PushList(pStack, NodeD);
//	PushList(pStack, NodeE);
//	char *pReverseStr = reverseString(sourceStr);
	//if (pReverseStr != NULL) {
//		printf("[%s] => [%s]\n", sourceStr, pReverseStr);
//		free(pReverseStr);
//	}
//	display(pStack);
	//Pop(pStack);
	//Pop(pStack);
//	display(pStack);
}