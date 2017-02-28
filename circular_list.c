#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeType {
	int data;
	struct Node* pLink;
}Node;
typedef struct HeadNodeType {
	int  currentNodeCurrent;
	Node* headerNode;
}HeadNode;

HeadNode* createcircularList();
void Remove(HeadNode *pList, int position);
void addcircularElement(HeadNode *pList, int position, Node element);

void addcircularElement(HeadNode *pList, int position, Node element) {
	Node* pNewNode = NULL;
	Node* pLastNode = NULL;
	Node* pPreNode = NULL;
	int i = 0;
	pNewNode = (Node *)malloc(sizeof(Node));
	if (pNewNode != NULL) {
		*pNewNode = element;
		pNewNode->pLink = NULL;

		if (position == 0) {
			if (pList->currentNodeCurrent == 0) {
				pList->headerNode = pNewNode;
				pNewNode->pLink = pNewNode;
			}
			else {
				pLastNode = pList->headerNode;
				
				while (pLastNode != pList->headerNode) {
					pLastNode = pLastNode->pLink;
				}
				pList->headerNode = pNewNode;
				pNewNode->pLink = pLastNode->pLink;
				pLastNode->pLink = pNewNode;
				
			}	
		}
		else {
			pPreNode = pList->headerNode;

			for (i = 0; i < position - 1; i++) {
				pPreNode = pPreNode->pLink;
			}

			pNewNode->pLink = pPreNode->pLink;
			pPreNode->pLink = pNewNode;
		}
		pList->currentNodeCurrent++;
	}
}

void display(HeadNode *pList) {
	Node* displayNode = NULL;
	int i = 0;
	displayNode = &(pList->headerNode);
	displayNode = displayNode->pLink;
	printf("%d\n", pList->currentNodeCurrent);
	for (i = 0; i < displayNode != NULL; i++) {
		printf("[%d] : %d\n", i, displayNode->data);
		displayNode = displayNode->pLink;
	}
}
void Remove(HeadNode *pList, int position) {
	Node *findNode = NULL;

	findNode = &(pList->headerNode);

	for (int i = 0; i < position; i++) {
		findNode = findNode->pLink;
	}
	free(findNode->pLink);
	findNode->pLink = NULL;
	pList->currentNodeCurrent--;
}
HeadNode *createcircularList() {
	HeadNode *pList = NULL;

	pList = (HeadNode*)malloc(sizeof(HeadNode));

	if (pList != NULL) {
		memset(pList, 0, sizeof(HeadNode));
	}
	return pList;
}

void displayList(HeadNode* pList) {
	Node* list = NULL;
	list = pList->headerNode;
	int i = 0;
	for (i = 0; i < pList->currentNodeCurrent; i++) {
		printf("%d\n", list->data);
		list = list->pLink;
	}
}
int main(int argc, char *argv[]) {
	HeadNode *pList = NULL;
	Node *pNode = NULL;
	Node node;

	pList = createcircularList();
	if (pList != NULL) {
		node.data = 144;
		addcircularElement(pList, 0, node);
		node.data = 144;
		addcircularElement(pList, 0, node);
		node.data = 144;
		addcircularElement(pList, 0, node);
		node.data = 144;
		addcircularElement(pList, 0, node);
		node.data = 144;
		addcircularElement(pList, 0, node);
		displayList(pList);
	}
}