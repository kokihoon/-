#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef struct BinTreeNodeType {
	char data;

	struct BinTreeNodeType *pLeftChild;
	struct BinTreeNodeType *pRightChild;
}BinTreeNode;

typedef struct BinTreeType {
	struct BinTreeNodeType *pRootNode;
}BinTree;
void inorderRecursiveTreeNode(BinTreeNode *pNode);
void preRecursiveTree(BinTree *pBinTree);
void postRecursiveTreeNode(BinTree *pBinTree);
void preRecursiveTreeNode(BinTreeNode *pNode);
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
		
		preRecursiveTree(pBinTree);
	}
}
void preRecursiveTree(BinTree *pBinTree) {
	if (pBinTree != NULL) {
		postRecursiveTreeNode(pBinTree->pRootNode);
	}
}
/*
void inorderRecursiveTreeNode(BinTreeNode *pNode) {
	if (pNode != NULL) {
		inorderRecursiveTreeNode(pNode->pLeftChild);
		printf("%c ", pNode->data);
		inorderRecursiveTreeNode(pNode->pRightChild);
	}
}*/
/*
void preRecursiveTreeNode(BinTreeNode *pNode) {
	if (pNode != NULL) {

		printf("%c ", pNode->data);
		preRecursiveTreeNode(pNode->pLeftChild);
		preRecursiveTreeNode(pNode->pRightChild);
	}
}
*/
void postRecursiveTreeNode(BinTreeNode *pNode) {
	if (pNode != NULL) {
		postRecursiveTreeNode(pNode->pLeftChild);
		postRecursiveTreeNode(pNode->pRightChild);
		printf("%c ", pNode->data);
	}
}