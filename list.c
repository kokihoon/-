#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeType {
	int data;
	struct Node* pLink;
}Node;
typedef struct HeadNodeType {
	int  currentNodeCurrent;
	Node headerNode;
}HeadNode;
void reverse(HeadNode* pList);
HeadNode* createList();
void Remove(HeadNode *pList, int position);
void addElement(HeadNode *pList, int position, Node element);


void addElement(HeadNode *pList, int position, Node element) {
	Node* pPreNode = NULL;
	Node* pNewNode = NULL;
	int i = 0;
	pNewNode = (Node *)malloc(sizeof(Node));
	if (pNewNode != NULL) {
		*pNewNode = element;
		pNewNode->pLink = NULL;
		pPreNode = &(pList->headerNode);
		for (i = 0; i < position; i++) {
			pPreNode = pPreNode->pLink;
		}
		pNewNode->pLink = NULL;
		pPreNode->pLink = pNewNode;

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
HeadNode *createList() {
	HeadNode *pList = NULL;

	pList = (HeadNode*)malloc(sizeof(HeadNode));

	if (pList != NULL) {
		memset(pList, 0, sizeof(HeadNode));
	}
	return pList;
}
void reverse(HeadNode* pList) {
	Node *next = NULL, *current = NULL, *Pre = NULL;
	next = pList->headerNode.pLink;
	while (next != NULL) {
		Pre = current;
		current = next;
		next = next->pLink;
		current->pLink = Pre;
	}
	pList->headerNode.pLink = current;
}
int main(int argc, char *argv[]) {
	HeadNode* pList = NULL;
	Node *pNode = NULL;
	Node node;

	pList = createList();
	if (pList != NULL) {
		node.data = 0;
		addElement(pList, 0, node);
		node.data = 1;
		addElement(pList, 1, node);
		node.data = 2;
		addElement(pList, 2, node);
		node.data = 3;
		addElement(pList, 3, node);
	//	display(pList);
//		Remove(pList, 3);
		//display(pList);
		node.data = 26;
		addElement(pList, 4, node);
		reverse(pList);
		display(pList);
	}
}