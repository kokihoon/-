#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DoubleListNodeType {
	int data;
	struct DoubleListNodeType *pRLink;
	struct DoubleListNodeType *pLLink;
} DoubleListNode;

typedef struct DoubleListType {
	int currentCount;
	DoubleListNode HeaderNode;
} DoubleList;

DoubleList* createList();
void addListNode(DoubleList *pList, int position, DoubleListNode node);
void disPlayList(DoubleList *pList);
void Concat(DoubleList *ListA, DoubleList *ListB);
DoubleList* createList(){
	DoubleList *pList = NULL;
	int i = 0;
	pList = (DoubleList*)malloc(sizeof(DoubleList));
	if (pList != NULL) {
		memset(pList, 0, sizeof(DoubleList));
		pList->HeaderNode.pLLink = &(pList->HeaderNode);
		pList->HeaderNode.pRLink = &(pList->HeaderNode);
	}
	return pList;
}

void addListNode(DoubleList *pList, int position, DoubleListNode node) {
	DoubleListNode *NewNode = NULL, *PreNode = NULL;
	int i = 0;
	NewNode = (DoubleListNode *)malloc(sizeof(DoubleListNode));

	*NewNode = node;
	NewNode->pLLink = NULL;
	NewNode->pRLink = NULL;
	PreNode = &(pList->HeaderNode);
	
	if (position == 0) {
		if (pList->currentCount == 0) {
			NewNode->pLLink = PreNode;
			PreNode->pRLink = NewNode;
		}

		else {
			NewNode->pLLink = PreNode;
			NewNode->pRLink = PreNode->pRLink;
			PreNode->pRLink = NewNode;
		}
	}
	else if (position < pList->currentCount) {
			for (i = 0; i < position; i++) {
				PreNode = PreNode->pRLink;
			}
			NewNode->pLLink = PreNode;
			NewNode->pRLink = PreNode->pRLink;
			PreNode->pRLink = NewNode;
			PreNode->pRLink->pLLink = NewNode;
		}
		else {
			for (i = 0; i < position; i++) {
				PreNode = PreNode->pRLink;

			}
			NewNode->pLLink = PreNode;
			PreNode->pRLink = NewNode;
			NewNode->pRLink = NULL;
		}
		pList->currentCount++;

}

void disPlayList(DoubleList *pList) {
	int i;
	DoubleListNode *Node = NULL;
	Node = &(pList->HeaderNode);
	Node = Node->pRLink;
	for (i = 0; i < Node != NULL; i++) {
		printf("[%d] : %d\n", i, Node->data);
		Node = Node->pRLink;
	}
}
void Concat(DoubleList *ListA, DoubleList *ListB) {
	DoubleListNode *concatNode1 = NULL, *concatNode2 = NULL;
	concatNode1 = &(ListA->HeaderNode);
	concatNode2 = &(ListB->HeaderNode);
	

	for (int i = 0; i < ListA->currentCount; i++) {
		concatNode1 = concatNode1->pRLink;
	}
	concatNode2 = &(ListB->HeaderNode);
	concatNode2 = concatNode2->pRLink;
	concatNode1->pRLink = concatNode2;
	concatNode2->pLLink = concatNode1;
}
int main(int argc, char argv[]) {
	DoubleList *ListA = NULL, *ListB = NULL;
	DoubleListNode node;

	ListA = createList();
	ListB = createList();
	if (ListA != NULL && ListB != NULL) {
		node.data = 1;
		addListNode(ListA, 0, node);
		node.data = 2;
		addListNode(ListA, 0, node);
		node.data = 3;
		addListNode(ListA, 0, node);
		node.data = 4;
		addListNode(ListA, 3, node);
	//	disPlayList(ListA);

		node.data = 3;
		addListNode(ListB, 0, node);
		node.data = 3;
		addListNode(ListB, 0, node);
		node.data = 3;
		addListNode(ListB, 0, node);
		Concat(ListA, ListB);
		disPlayList(ListA);

	}
	return 0;
}
