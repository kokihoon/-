#include <stdio.h>
#define TRUE 1
#define FALSE 0
typedef struct BinSearchTreeNodeType {
	int key;
	char value;

	struct BinSearchTreeNodeType *pLeftChild;
	struct BinSearchTreeNodeType *pRightChild;
}BinSearchTreeNode;

typedef struct BinSearchTreeType {
	BinSearchTreeNode *pRootNode;
}BinSearchTree;

BinSearchTree *createBinSearchTree() {
	BinSearchTree *pReturn = NULL;
	pReturn = (BinSearchTree *)malloc(sizeof(BinSearchTree));
	if (pReturn != NULL) {
		pReturn->pRootNode = NULL;
	}
	else {
		printf("메모리 할당 오류\n");
	}
	return pReturn;
}
int insertElementBST(BinSearchTree *pBinSearchTree, BinSearchTreeNode element) {
	int ret = TRUE;
	BinSearchTreeNode *pNode = NULL;
	BinSearchTreeNode *pParent = NULL;
	if (pBinSearchTree != NULL) {
		pParent = pBinSearchTree->pRootNode;
		while (pParent != NULL) {
			if (pParent->key == element.key) {
				printf("중복있습니다\n");
				ret = FALSE;
				return ret;
			}
			else if (element.key < pParent->key) {
				if (pParent->pLeftChild == NULL) {
					break;
				}
				else {
					pParent = pParent->pLeftChild;
				}
			}
			else {
				if (pParent->pRightChild == NULL) {
					break;
				}
				else {
					pParent = pParent->pRightChild;
				}
			}
		}
		pNode = (BinSearchTreeNode *)malloc(sizeof(BinSearchTreeNode));
		if (pNode != NULL) {
			pNode->pLeftChild = NULL;
			pNode->pRightChild = NULL;
			*pNode = element;
			if (pParent == NULL) {
				pBinSearchTree->pRootNode = pNode;
			}
			else {
				if(pNode->key < pParent->key) {
					pParent->pLeftChild = pNode;
				}
				else {
					pParent->pRightChild = pNode;
				}
			}
			ret = TRUE;

		}
		else {
			printf("메모리 할당 오류\n");
			ret = FALSE;
		}
		
	}
	return ret;
}
/*
int insertElementBST(BinSearchTree *pBinSearchTree, BinSearchTreeNode element) {
	int ret = TRUE;
	BinSearchTreeNode *pNode = NULL;
	BinSearchTreeNode *pParent = NULL;
	if (pBinSearchTree != NULL) {
		pNode = (BinSearchTreeNode *)malloc(sizeof(BinSearchTreeNode));
		if (pNode != NULL) {
			pNode->pLeftChild = NULL;
			pNode->pRightChild = NULL;
			*pNode = element;
			pParent = pBinSearchTree->pRootNode;
			if (pParent == NULL) {
				pParent = pNode;
				return ret;
			}
			while (pParent != NULL) {
				if (pParent->key > pNode->key) {
					if (pParent->pLeftChild == NULL) {
						pParent->pLeftChild = pNode;
						break;
					}
					else {
						pParent = pParent->pLeftChild;
					}
				}
				else if (pParent->key == pNode->key) {
					printf("중복있습니다\n");
					ret = FALSE;
					return ret;
				}
				else {
					if (pParent->pRightChild == NULL) {
						pParent->pRightChild = pNode;
						break;
					}
					else {
						pParent = pParent->pRightChild;
					}
				}
			}
		}
	}
	return ret;
}
*/
int deleteElementBST(BinSearchTree *pBinSearchTree, int key) {
	int ret = TRUE;
	BinSearchTreeNode *pNode = NULL, *pParent = NULL, *pPredecessor = NULL, *pSuccessor = NULL, *pChild = NULL;

	if (pBinSearchTree == NULL) {
		ret = FALSE;
		return ret;
	}
	pParent = 
	pNode = pBinSearchTree->pRootNode;
	while(pNode != NULL) {

		if (pNode->key == key) {
			break;
		}
		pParent = pNode;
		if (key < pNode->key) {
			pNode = pNode->pLeftChild;
		}
		else {
			pNode = pNode->pRightChild;
		}
		if (pNode == NULL) {
			printf("오류 존재하지 않은 key\n");
			ret = FALSE;
			return ret;
		}
	}
	if (pNode->pLeftChild == NULL && pNode->pRightChild == NULL) {
		if (pParent != NULL) {
			if (pParent->pLeftChild == pNode) {
				pParent->pLeftChild = NULL;
			}
			else if (pParent->pRightChild == pNode) {
				pParent->pRightChild = NULL;
			}
		}
		else {
			pBinSearchTree->pRootNode = NULL;
		}
	}

	else if (pNode->pLeftChild != NULL && pNode->pRightChild != NULL) {
		pPredecessor = pNode;
		pSuccessor = pNode->pLeftChild;
		while (pSuccessor->pRightChild != NULL) {
			pPredecessor = pSuccessor;
			pSuccessor = pSuccessor->pRightChild;
		}

		pPredecessor->pRightChild = pSuccessor->pLeftChild;
		pSuccessor->pLeftChild = pNode->pLeftChild;
		pSuccessor->pRightChild = pNode->pRightChild;

		if (pParent != NULL) {
			if (pParent->pLeftChild == pNode) {
				pParent->pLeftChild = pSuccessor;
			}
			else {
				pParent->pRightChild = pSuccessor;
			}
		}
		else {
			pBinSearchTree->pRootNode = pSuccessor;
		}
	}
	else {
		if (pParent->pLeftChild == pNode) {
			pChild = pNode->pLeftChild;
		}
		else {
			pChild = pNode->pRightChild;
		}

		if (pParent != NULL) {
			if (pParent->pLeftChild == pNode) {
				pParent->pLeftChild = pChild;
			}
			else {
				pParent->pRightChild = pChild;
			}
		}
		else {
			pBinSearchTree->pRootNode = pChild;
		}
	}
	free(pNode);
	return ret;
}

void main() {
	BinSearchTree *pBinTree = NULL;
	BinSearchTreeNode element1 ={ 0, };
	pBinTree = createBinSearchTree();
	element1.key = 1;
	insertElementBST(pBinTree, element1);

	element1.key = 2;
	insertElementBST(pBinTree, element1);


	element1.key = 3;
	insertElementBST(pBinTree, element1);


	element1.key = 5;
	insertElementBST(pBinTree, element1);

	element1.key = 4;
	insertElementBST(pBinTree, element1);

	element1.key = 7;
	insertElementBST(pBinTree, element1);

	element1.key = 8;
	insertElementBST(pBinTree, element1);
	deleteElementBST(pBinTree, 1);
}