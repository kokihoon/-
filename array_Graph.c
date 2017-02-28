#include <stdio.h>

#define USED 1
#define NOT_USED 0
#define SUCCESS 1
#define FAIL 0
#define TRUE 1
#define FALSE 0
#define GRAPH_UNDIRECTED 1
#define GRAPH_DIRECTED 2
typedef struct ArrayGraphType {
	int maxVertexCount;
	int currentVertexCount;
	int graphType;
	int **ppAdjEdge;
	int *pVertex;
} ArrayGraph;
ArrayGraph *createArrayGraph(int maxVertexCount);
ArrayGraph *createArrayDirectedGraph(int maxVertCount);
int addEdgewithWeightAG(ArrayGraph *pGraph, int fromVertexID, int toVertexID, int weight);
int addVertexAg(ArrayGraph *pGraph, int vertexID);
int checkVertexVaild(ArrayGraph *pGraph, int vertexID);
int addEdgeAG(ArrayGraph *pGraph, int fromVertexID, int toVertexID);
void displayArrayGraph(ArrayGraph *pG);

ArrayGraph *createArrayGraph(int maxVertexCount) {
	int i = 0, j = 0;
	ArrayGraph *pReturn = NULL;

	if (maxVertexCount > 0) {
		pReturn = (ArrayGraph *)malloc(sizeof(ArrayGraph));
		if (pReturn == NULL) {
			printf("메모리 할당 오류\n");
			return NULL;
		}
		pReturn->graphType = GRAPH_UNDIRECTED;
		pReturn->maxVertexCount = maxVertexCount;
	}
	else {
		printf("오류 최대 노드 개수 0보다 커야댐\n");
	}
	pReturn->pVertex = (int *)malloc(sizeof(int)*maxVertexCount);
	if (pReturn->pVertex == NULL) {
		printf("메모리 오류 할당 실패\n");
		return NULL;
	}
	pReturn->ppAdjEdge = (int **)malloc(sizeof(int *)*maxVertexCount);
	if (pReturn->ppAdjEdge == NULL) {
		printf("메모리 할당 오류\n");
		free(pReturn->pVertex);
		free(pReturn);
		return NULL;
	}
	for (i = 0; i < maxVertexCount; i++) {
		pReturn->ppAdjEdge[i] = (int *)malloc(sizeof(int)*maxVertexCount);
		if (pReturn->ppAdjEdge[i] == NULL) {
			printf("메모리 할당 오류\n");

			for (j = 0; j < i - 1; j++) {
				if (pReturn->ppAdjEdge[j] != NULL) {
					free(pReturn->ppAdjEdge[j]);
				}
			}
			if (pReturn->ppAdjEdge != NULL) { free(pReturn->ppAdjEdge); }
			if (pReturn->pVertex != NULL) { free(pReturn->pVertex); }
			if (pReturn != NULL) { free(pReturn); }
			return NULL;
			
		}
	}
	memset(pReturn->pVertex, NOT_USED, sizeof(int)*maxVertexCount);
	for (i = 0; i < maxVertexCount; i++) {
		memset(pReturn->ppAdjEdge[i], 0, sizeof(int)*maxVertexCount);
	}
	return pReturn;
}

ArrayGraph *createArrayDirectedGraph(int maxVertCount) {
	
	ArrayGraph *pReturn = NULL;
	pReturn = createArrayGraph(maxVertCount);
	if (pReturn != NULL) {
		pReturn->graphType = GRAPH_DIRECTED;
	}
	return pReturn;
}

int addVertexAg(ArrayGraph *pGraph, int vertexID) {
	int ret = SUCCESS;

	if (pGraph != NULL) {
		if (vertexID < pGraph->maxVertexCount) {
			if (pGraph->pVertex[vertexID] == NOT_USED) {
				pGraph->pVertex[vertexID] = USED;
				pGraph->currentVertexCount++;
			}
			else {
				printf("오류 이미 존재함\n");
				ret = FAIL;
			}
		}
		else {
			printf("오류 노드 개수 초과\n");
			ret = FAIL;
		}
	}
	return ret;
}

int addEdgewithWeightAG(ArrayGraph *pGraph, int fromVertexID, int toVertexID, int weight) {
	int ret = SUCCESS;
	if (pGraph != NULL) {
		if (checkVertexVaild(pGraph, fromVertexID) != SUCCESS) {
			ret = FAIL;
			return ret;
		}

		if (checkVertexVaild(pGraph, toVertexID) != SUCCESS) {
			ret = FAIL;
			return ret;
		}
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;

		if (pGraph->graphType == GRAPH_UNDIRECTED) {
			pGraph->ppAdjEdge[toVertexID][fromVertexID] = weight;
		}
	}
	return ret;
}

int checkVertexVaild(ArrayGraph *pGraph, int vertexID) {
	int ret = SUCCESS;

	if (vertexID >= pGraph->maxVertexCount || pGraph->pVertex[vertexID] == NOT_USED) {
		printf("오류 노드정보[%d]\n", vertexID);
		ret = FAIL;
	}
	return ret;
}
int addEdgeAG(ArrayGraph *pGraph, int fromVertexID, int toVertexID) {
	return addEdgewithWeightAG(pGraph, fromVertexID, toVertexID, USED);
}

int removeEdgeAG(ArrayGraph *pGraph, int fromVertexID, int toVertexID) {
	int ret = SUCCESS;

	if (pGraph != NULL) {
		if (checkVertexVaild(pGraph, fromVertexID) != SUCCESS) {
			ret = FAIL;
			return ret;
		}
		if (checkVertexVaild(pGraph, toVertexID) != SUCCESS) {
			ret = FAIL;
			return ret;
		}
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = 0;
		if (pGraph->graphType == GRAPH_UNDIRECTED) {
			pGraph->ppAdjEdge[toVertexID][fromVertexID] = 0;
		}
	}
	return ret;
}

int removeVertexAG(ArrayGraph *pGraph, int vertexID) {
	int ret = SUCCESS;
	int i = 0;

	if (pGraph != NULL) {
		if (checkVertexVaild(pGraph, vertexID) != SUCCESS) {
			ret = FAIL;
			return ret;
		}

		for (i = 0; i < pGraph->maxVertexCount; i++) {
			removeEdgeAG(pGraph, vertexID, i);
			removeEdgeAG(pGraph, i, vertexID);
		}

		pGraph->pVertex[vertexID] = NOT_USED;
	}
	return ret;
}

void main() {
	int i = 0;
	ArrayGraph *pG1 = NULL, *pG2 = NULL, *pG4 = NULL;

	pG1 = createArrayGraph(6);
	pG2 = createArrayDirectedGraph(6);
	pG4 = createArrayDirectedGraph(6);

	if (pG1 != NULL && pG2 != NULL && pG4 != NULL) {
		
		for (i = 0; i < 6; i++) {
			addVertexAg(pG1, i);
			addVertexAg(pG2, i);
			addVertexAg(pG4, i);
		}

		addEdgeAG(pG1, 0, 1);
		addEdgeAG(pG1, 0, 2);
		addEdgeAG(pG1, 1, 2);
		addEdgeAG(pG1, 2, 3);
		addEdgeAG(pG1, 3, 4);
		addEdgeAG(pG1, 3, 5);
		addEdgeAG(pG1, 4, 5);
		addEdgeAG(pG2, 0, 1);
		addEdgeAG(pG2, 1, 2);
		addEdgeAG(pG2, 2, 0);
		addEdgeAG(pG2, 2, 1);
		addEdgeAG(pG2, 2, 3);
		addEdgeAG(pG2, 3, 2);
		addEdgeAG(pG1, 3, 4);
		addEdgeAG(pG1, 4, 5);
		addEdgeAG(pG1, 5, 3);
		addEdgewithWeightAG(pG4, 0, 1, 4);
		addEdgewithWeightAG(pG4, 1, 2, 1);
		addEdgewithWeightAG(pG4, 2, 0, 2);
		addEdgewithWeightAG(pG4, 2, 1, 3);
		addEdgewithWeightAG(pG4, 2, 3, 2);
		addEdgewithWeightAG(pG4, 3, 2, 1);
		addEdgewithWeightAG(pG4, 3, 4, 1);
		addEdgewithWeightAG(pG4, 4, 5, 1);
		addEdgewithWeightAG(pG4, 5, 3, 2);

		printf("G1: Undirected\n");
		displayArrayGraph(pG1);
		printf("G1: Directed\n");
		displayArrayGraph(pG2);
		printf("G1: Directed Weighted\n");
		displayArrayGraph(pG4);
		
	}

}

void displayArrayGraph(ArrayGraph *pG) {
	int i, j;
	for (i = 0; i < pG->maxVertexCount; i++) {
		for (j = 0; j < pG->maxVertexCount; j++) {
			printf("%d ", pG->ppAdjEdge[i][j]);
		}
		printf("\n");
	}
}