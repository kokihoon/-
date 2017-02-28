#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef struct StackType {
	int currentCount;
	struct StackType *pTopElement;
}LinkedStack;

typedef struct BinTreeNodeType {
	char data;
	struct BinTreeNodeType *pLeftChild;
	struct BinTreeNodeType *pRightChild;
}BinTreeNode;

typedef struct StackNodeType {
	char data;
	struct StackNodeType* pLink;
}StackNode;

typedef struct BinTreeType {
	struct BinTreeNodeType *pRootNode;
}BinTree;
void preBinTree(BinTree *pBinTree);
void inorderRecursiveTreeNode(BinTreeNode *pNode);
void preRecursiveTree(BinTree *pBinTree);
void postRecursiveTreeNode(BinTree *pBinTree);
void preRecursiveTreeNode(BinTreeNode *pNode);
void PushList(LinkedStack *pStack, StackNode Node);

void PushTreeNode(LinkedStack* pStack, BinTreeNode *pNode) {
	StackNode node = { 0, };
	node.data = pNode->data;
	PushList(pStack, node);
}

void PushList(LinkedStack *pStack, StackNode Node) {
	StackNode *pNode = NULL;

	if (pStack != NULL) {
		pNode = (StackNode*)malloc(sizeof(StackNode));
		if (pNode != NULL) {
//			memset(pNode, 0, sizeof(StackNode));
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

StackNode *Pop(LinkedStack *pStack) {
	StackNode *pNode = NULL;

	if (pStack != NULL) {
		pNode = pStack->pTopElement;
		pStack->pTopElement = pNode->pLink;
		pNode->pLink = NULL;
		pStack->currentCount--;
	}
	return pNode;
}
BinTree *Create(BinTreeNode RootNode) {
	BinTree *pReturn = NULL;
	pReturn = (BinTree *)malloc(sizeof(BinTree));
	pReturn->pRootNode = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (pReturn != NULL) {
		if (pReturn->pRootNode != NULL) {
			*(pReturn->pRootNode) = RootNode;
			pReturn->pRootNode->pLeftChild = NULL;
			pReturn->pRootNode->pRightChild = NULL;
		}
	}
	return pReturn;
}
BinTreeNode *InsertRightNode(BinTreeNode *pParentNode, BinTreeNode element) {
	BinTreeNode *childNode1 = NULL;
	if (pParentNode != NULL) {
		if (pParentNode->pRightChild == NULL) {
			pParentNode->pRightChild = (BinTreeNode *)malloc(sizeof(BinTreeNode));
			if (pParentNode->pRightChild != NULL) {
				*(pParentNode->pRightChild) = element;
				pParentNode->pRightChild->pLeftChild = NULL;
				pParentNode->pRightChild->pRightChild = NULL;
				childNode1 = pParentNode->pRightChild;
			}
		}
	}
	return childNode1;
}
BinTreeNode *InsertLeftNode(BinTreeNode *pParentNode, BinTreeNode element) {
	BinTreeNode *childNode = NULL;
	if (pParentNode != NULL) {
		if (pParentNode->pLeftChild == NULL) {
			pParentNode->pLeftChild = (BinTreeNode *)malloc(sizeof(BinTreeNode));
			if (pParentNode->pLeftChild != NULL) {
				*(pParentNode->pLeftChild) = element;
				pParentNode->pLeftChild->pLeftChild = NULL;
				pParentNode->pLeftChild->pRightChild = NULL;
				childNode = pParentNode->pLeftChild;
			}
		}
	}
	return childNode;
}
BinTreeNode *getRootNode(BinTree *pBinTree) {
	BinTreeNode *pReturn = NULL;

	if (pBinTree != NULL) {

		pReturn = pBinTree->pRootNode;
	}
	return pReturn;
}
void main() {
	BinTree *pBinTree = NULL;
	BinTreeNode *pNodeA = NULL, *pNodeB = NULL, *pNodeC = NULL;
	BinTreeNode *pNodeD = NULL, *pNodeE = NULL, *pNodeF = NULL;
	BinTreeNode node = { 0, };

	node.data = 'A';
	pBinTree = Create(node);

	if (pBinTree != NULL) {
		pNodeA = getRootNode(pBinTree);

		node.data = 'B';

		pNodeB = InsertLeftNode(pNodeA, node);

		node.data = 'C';
		pNodeC = InsertRightNode(pNodeA, node);

		node.data = 'D';
		pNodeD = InsertLeftNode(pNodeB, node);

		node.data = 'E';
		pNodeE = InsertLeftNode(pNodeC, node);
		node.data = 'F';
		pNodeF = InsertRightNode(pNodeC, node);

		preBinTree(pBinTree);
	}
}

void preBinTree(BinTree *pBinTree) {
	LinkedStack *pStack = NULL;

	StackNode *pStackNode = NULL;
	BinTreeNode *pRootNode = NULL, *pLeftNode = NULL, *pRightNode = NULL;

	if (pBinTree == NULL) {
		return;
	}
	pRootNode = getRootNode(pBinTree);
	if (pRootNode == NULL) {
		return;
	}
	
	pStack = createStack();

	if (pStack == NULL) {
		return;
	}
	PushTreeNode(pStack, pRootNode);
	while (1) {
		if (pStack->currentCount == 0) {
			break;
		}
		else {
			pStackNode = Pop(pStack);
			if (pStackNode != NULL) {
				pRootNode = pStackNode->data;
				printf("%c ", pRootNode->data);
				pLeftNode = pRootNode->pLeftChild;
				pRightNode = pRootNode->pRightChild;
				if (pRightNode != NULL) {
					PushTreeNode(pStack, pRightNode);
				}
				if (pLeftNode != NULL) {
					PushTreeNode(pStack, pLeftNode);
				}
				free(pStackNode);
			}
		}
	}
}