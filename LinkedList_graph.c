#include<stdio.h>
#define USED 1
#define NOT_USED 0
#define TRUE 1
#define FALSE 0
#define GRAPH_UNDIRECTED 1
#define GRAPH_DIRECTED 2
#define SUCCESS 1
#define FAIL 0
typedef struct GraphVertexType {
	int vertexID;
	int weight;

}GraphVertex;
typedef struct ListNodeType {
	GraphVertex data;
	struct ListNodeType *pLink;
}ListNode;
typedef struct LinkedListType {
	int currentElementCount;
	ListNode headerNode;
} LinkedList;
typedef struct LinkedGraphType {
	int maxVertexCount;
	int currentVertexCount;
	int currentEdgeCount;
	int graphType;
	LinkedList **ppAdjEdge;
	int *pVertex;
}LinkedGraph;
typedef struct StackNodeType {
	char data;
	struct StackNodeType *pLink;
} StackNode;
typedef struct LinkedStackType {
	int currentElementCount;
	StackNode *pTopElemnt;
}LinkedStack;

typedef struct QueueNodeType {
	char data;
	struct QueueNodeType* pLink;

}QueueNode;

typedef struct LinkedQueueType {
	int currentCount;
	QueueNode *pFrontNode;
	QueueNode *pRearNode;
} LinkedQueue;

LinkedList *createLinkedList();
void traversalDFS(LinkedGraph *pGraph, int startVertexID);
void traversalBFS(LinkedGraph *pGraph, int startVertexID);
int addEdgewithWeightLG(LinkedGraph *pGraph, int fromVertexID, int toVertexID, int weight);

LinkedQueue *create() {
	LinkedQueue *pReturn = NULL;

	pReturn = (LinkedQueue *)malloc(sizeof(LinkedQueue));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(LinkedQueue));

	}
	else {
		printf("메모리 할당 오류", create());
	}
	return pReturn;
}
int enQueue(LinkedQueue *pQueue, QueueNode element) {
	QueueNode *pNode = NULL;
	int ret = FALSE;
	if (pQueue != NULL) {
		pNode = (QueueNode *)malloc(sizeof(QueueNode));

		if (pNode != NULL) {
			*pNode = element;
			pNode->pLink = NULL;
			if (pQueue->currentCount == 0) {
				pQueue->pFrontNode = pNode;
				pQueue->pRearNode = pNode;
			}
			else {
				pQueue->pRearNode->pLink = pNode;
				pQueue->pRearNode = pNode;
			}
			pQueue->currentCount++;
			ret = TRUE;
		}
		else {
			printf("메모리 할당 오류");
		}
	}
	return ret;
}
QueueNode *deQueue(LinkedQueue* pQueue) {
	QueueNode *pReturn = NULL;

	if (pQueue != NULL) {
		if (pQueue->currentCount != 0) {
			pReturn = pQueue->pFrontNode;
			pQueue->pFrontNode = pQueue->pFrontNode->pLink;
			pReturn->pLink = NULL;
			pQueue->currentCount--;
			if (pQueue->currentCount == 0) {
				pQueue->pRearNode = NULL;
			}
		}
	}
	return pReturn;
}

LinkedGraph *createLinkedGraph(int maxVertexCount) {
	int i = 0, j = 0;
	LinkedGraph *pReturn = NULL;

	if (maxVertexCount > 0) {
		pReturn = (LinkedGraph *)malloc(sizeof(LinkedGraph));
		if (pReturn == NULL) {
			printf("메모리 할당 오류\n");
			return NULL;
		}
		pReturn->graphType = GRAPH_UNDIRECTED;
		pReturn->maxVertexCount = maxVertexCount;
		pReturn->currentVertexCount = 0;
		pReturn->currentEdgeCount = 0;

	}
	else {
		printf("최대 노드 수 0개보다 커야됨\n");
		return NULL;
	}
	pReturn->pVertex = (int *)malloc(sizeof(int) * maxVertexCount);
	if (pReturn->pVertex == NULL) {
		printf("메모리 할당 오류1\n");
		return NULL;
	}
	memset(pReturn->pVertex, NOT_USED, sizeof(int)*maxVertexCount);
	pReturn->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList*) *maxVertexCount);
	if (pReturn->ppAdjEdge == NULL) {
		printf("메모리 할당 오류2\n");
		return NULL;
	}
	for (i = 0; i < maxVertexCount; i++) {
		pReturn->ppAdjEdge[i] = createLinkedList();
		if (pReturn->ppAdjEdge[i] == NULL) {
			printf("메모리 할당 오류3\n");
			return NULL;
		}
	}
	return pReturn;
}
LinkedGraph *createLinkedDirectedGraph(int maxVertexCount) {
	LinkedGraph *pReturn = NULL;
	
	pReturn = createLinkedGraph(maxVertexCount);
	if (pReturn != NULL) {
		pReturn->graphType = GRAPH_DIRECTED;
	}
	return pReturn;
}

LinkedList *createLinkedList() {
	LinkedList *pReturn = NULL;

	pReturn = (LinkedList *)malloc(sizeof(LinkedList));
	if (pReturn == NULL) {
		printf("메모리 할당 4\n");
		return NULL;
	}
	memset(pReturn, 0, sizeof(LinkedList));
	return pReturn;
}

int addVertexLG(LinkedGraph *pGraph, int vertexID) {
	int ret = SUCCESS;
	if (pGraph != NULL) {
		if (vertexID < pGraph->maxVertexCount) {
			if (pGraph->pVertex[vertexID] == NOT_USED) {
				pGraph->pVertex[vertexID] = USED;
				pGraph->currentVertexCount++;
			}
			else {
				printf("오류 노드");
				ret = FAIL;
			}
		}
		else {
			printf("오류 노드 개수 초과");
			ret = FAIL;
		}
	}
	return ret;
}
int addLLElement(LinkedList *pList, int position, ListNode node) {
	int ret = FALSE;
	int i = 0;
	ListNode *pPreNode = NULL;
	ListNode *pNewNode = NULL;

	if (pList != NULL) {
		if(position >= 0 && position <= pList->currentElementCount) {
			pNewNode = (ListNode*)malloc(sizeof(ListNode));
			if (pNewNode != NULL) {
				*pNewNode = node;
				pNewNode->pLink = NULL;
				pPreNode = &(pList->headerNode);
				for (i = 0; i < position; i++) {
					pPreNode = pPreNode->pLink;
				}

				pNewNode->pLink = pPreNode->pLink;
				pPreNode->pLink = pNewNode;
				pList->currentElementCount++;
				ret = TRUE;
			}
		}
	}
	return ret;
}
int addEdgeLG(LinkedGraph *pGraph, int fromVertexID, int toVertexID) {
	return addEdgewithWeightLG(pGraph, fromVertexID, toVertexID, USED);
}

int addLLElementForVertex(LinkedList *pList, int position, GraphVertex vertex) {
	ListNode node = { 0, };
	node.data = vertex;
	return addLLElement(pList, position, node);
}
int pushLSForDFS(LinkedGraph *pStack, int nodeID) {
	StackNode node = { 0, };
	node.data = nodeID;
	return pushLS(pStack, node);
}

int pushLS(LinkedStack *pStack, StackNode element) {
	int ret = FALSE;
	StackNode *pNode = NULL;

	if (pStack != NULL) {
		pNode = (StackNode *)malloc(sizeof(StackNode));

		if (pNode != NULL) {
			memset(pNode, 0, sizeof(StackNode));
			*pNode = element;
			pNode->pLink = pStack->pTopElemnt;
			pStack->pTopElemnt = pNode;
			pStack->currentElementCount++;
			ret = TRUE;
		}
	}
	return ret;
}

int addEdgewithWeightLG(LinkedGraph *pGraph, int fromVertexID, int toVertexID, int weight) {
	int ret = SUCCESS;
	GraphVertex toNode = { 0, };
	if (pGraph != NULL) {
		if (checkVertexVaild(pGraph, fromVertexID) != SUCCESS) {
			ret = FAIL;
			return ret;
		}
		if (checkVertexVaild(pGraph, toVertexID) != SUCCESS) {
			ret = FAIL;
			return ret;
		}
		toNode.vertexID = toVertexID;
		toNode.weight = weight;
		addLLElementForVertex(pGraph->ppAdjEdge[fromVertexID], 0, toNode);
		pGraph->currentEdgeCount++;

		if (pGraph->graphType == GRAPH_UNDIRECTED) {
			GraphVertex fromNode;
			fromNode.vertexID = fromVertexID;
			fromNode.weight = weight;
			addLLElementForVertex(pGraph->ppAdjEdge[toVertexID], 0, fromNode);
			pGraph->currentEdgeCount++;
		}
	}
	return ret;
}

LinkedStack *createLinkedStack() {
	LinkedStack *pReturn = NULL;
	pReturn = (LinkedStack *)malloc(sizeof(LinkedStack));
	memset(pReturn, 0, sizeof(LinkedStack));
	return pReturn;
}
StackNode *PopLS(LinkedStack *pStack) {

	StackNode *pReturn = NULL;

	if (pStack != NULL) {
		pReturn = pStack->pTopElemnt;
		pStack->pTopElemnt = pReturn->pLink;
		pReturn->pLink = NULL;
		pStack->currentElementCount--;
	}
	return pReturn;
}
void traversalDFS(LinkedGraph *pGraph, int startVertexID) {
	int i = 0;
	int  vertexID = 0;
	LinkedStack *pStack = NULL;
	StackNode *pStackNode = NULL;
	ListNode *pListNode = NULL;

	int *pVisited = NULL;

	if (pGraph == NULL) {
		return ;
	}

	pStack = createLinkedStack();

	if (pStack == NULL) {
		return ;
	}

	pVisited = (int *)malloc(sizeof(int)*pGraph->maxVertexCount);
	if (pVisited == NULL) {
		printf("오류\n");
		return NULL;
	}
	for (i = 0; i < pGraph->maxVertexCount; i++) {
		pVisited[i] = FALSE;
	}

	pVisited[startVertexID] = TRUE;
	pushLSForDFS(pStack, startVertexID);

	while(pStack->currentElementCount != 0) {
		pStackNode = PopLS(pStack);
		if (pStackNode != NULL) {
			vertexID = pStackNode->data;
			printf("[%d]-방문\n", vertexID);
			pListNode = pGraph->ppAdjEdge[vertexID]->headerNode.pLink;
			while (pListNode != NULL) {
				int vertexID = pListNode->data.vertexID;
				if (pVisited[vertexID] == FALSE) {
					pVisited[vertexID] = TRUE;
					pushLSForDFS(pStack, vertexID);

				}
				pListNode = pListNode->pLink;
			}
		}
	}
	free(pVisited);
}

int enqueueLQForBFS(LinkedQueue *pQueue, int nodeID) {
	QueueNode node = { 0, };
	node.data = nodeID;
	return enQueue(pQueue, node);
}
void traversalBFS(LinkedGraph *pG1, int startVertexID) {

	int i = 0, vertexID = 0;
	QueueNode *pTop = NULL;
	LinkedQueue *pQueue = NULL;
	QueueNode *pQueueNode = NULL;
	ListNode *pListNode = NULL;
	int *pVisited = NULL;

	if (pG1 == NULL) {
		return;
	}

	pVisited = (int *)malloc(sizeof(int)*pG1->maxVertexCount);
	pQueue = create();
	if (pVisited == NULL) {
		printf("메모리 할당 오류\n");
		return NULL;
	}

	for (i = 0; i < pG1->maxVertexCount; i++) {
		pVisited[i] = FALSE;
	}
	pVisited[startVertexID] = TRUE;
	enqueueLQForBFS(pQueue, startVertexID);
	while (pQueue->currentCount != 0) {
		pQueueNode = deQueue(pQueue);

		if (pQueueNode != NULL) {
			vertexID = pQueueNode->data;
			printf("[%d] - visited\n", vertexID);

			pListNode = pG1->ppAdjEdge[vertexID]->headerNode.pLink;
			while (pListNode != NULL) {
				int vertexID = pListNode->data.vertexID;
				if (pVisited[vertexID] == FALSE) {
					pVisited[vertexID] = TRUE;
					enqueueLQForBFS(pQueue, vertexID);

				}
				pListNode = pListNode->pLink;
			}
		}
	}
	free(pVisited);
}
int checkVertexVaild(LinkedGraph *pGraph, int vertexID) {
	int ret = SUCCESS;

	if (vertexID >= pGraph->maxVertexCount || pGraph->pVertex[vertexID] == NOT_USED) {
		printf("오류 노드\n");
		ret = FAIL;
	}
	return ret;
}

void main() {
	int i = 0;
	LinkedGraph *pG1 = NULL;

	pG1 = createLinkedGraph(8);
	if (pG1 != NULL) {
		for (i = 0; i < 8; i++) {
			addVertexLG(pG1, i);
		}
	}
	addEdgeLG(pG1, 0, 1);
	addEdgeLG(pG1, 0, 2);
	addEdgeLG(pG1, 1, 3);
	addEdgeLG(pG1, 1, 4);
	addEdgeLG(pG1, 2, 5);
	addEdgeLG(pG1, 2, 6);
	addEdgeLG(pG1, 3, 7);
	addEdgeLG(pG1, 4, 5);

	printf("G1:\n");
//	displayLinkedGraph(pG1);

	printf("\nDFS traversal:\n");
	traversalDFS(pG1, 0);
	printf("\nBFS traversal:\n");
	traversalBFS(pG1, 0);
}
/*

void displayLinkedGraph(LinkedGraph *pGraph) {

}
*/
