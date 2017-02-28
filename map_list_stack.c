#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_DIRECTION 4
#define WIDTH 8
#define HEIGHT 8
#define FALSE 1
#define TRUE 0

enum pos { Visit = 2, Wall = 1, Not_visit = 0 };

static int DIRECTION_OFFSETS[NUM_DIRECTION][2] = {
	{0, -1},  //위쪽
	{1, 0},   //오른쪽
	{0, 1},   //아래쪽
	{-1, 0}   // 왼쪽
};

typedef struct MapPositionType {
	int x;
	int y;
	int direction;
}MapPosition;

typedef struct StackNodeType {
	MapPosition data;
	struct StackNodeType *pLink;
} StackNode;

typedef struct StackType {
	int currentCount;
	struct StackType *pTopElement;
}LinkedStack;

int isLinkedStackEmpty(LinkedStack* pStack);
LinkedStack *createStack();
int PushList(LinkedStack *pStack, StackNode Node);
StackNode *Pop(LinkedStack *pStack);
void printMaze(int mazeArray[HEIGHT][WIDTH]);
int PushMapPosition(LinkedStack* pStack, MapPosition data) {
	StackNode node = { 0, };
	node.data = data;
	return PushList(pStack, node);
}

void findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos, MapPosition endPos, LinkedStack *pStack) {
	StackNode *pNode = NULL;
	int markArray[HEIGHT][WIDTH] = { 0, };
	int isEmpty = FALSE, isFound = FALSE, i = 0;
	
	if (pStack != NULL) {
		MapPosition newPosition = startPos;
		newPosition.direction = 0;
		PushMapPosition(pStack, newPosition);
		while (isEmpty == FALSE && isFound == FALSE) {
			pNode = Pop(pStack);
			if (pNode != NULL) {
				int x = pNode->data.x;
				int y = pNode->data.y;
				int direction = pNode->data.direction;
				while (isFound == FALSE && direction < NUM_DIRECTION) {
					int newX = x + DIRECTION_OFFSETS[direction][0];
					int newY = y + DIRECTION_OFFSETS[direction][1];

					if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && mazeArray[newY][newX] == Not_visit && markArray[newY][newX] == Not_visit) {
						MapPosition newPosition;
						newPosition.x = x;
						newPosition.y = y;
						newPosition.direction = direction + 1;
						PushMapPosition(pStack, newPosition);
						markArray[y][x] = Visit;
						x = newX;
						y = newY;
						direction = 0;

						if (newX == endPos.x && newY == endPos.y) {
							isFound = TRUE;
							newPosition.x = newX;
							newPosition.y = newY;
							newPosition.direction = 0;
							PushMapPosition(pStack, newPosition);
							markArray[newY][newX] = Visit;
						}
					}
					else {
						direction++;
					}
				}
				free(pNode);
			}
			isEmpty = isLinkedStackEmpty(pStack);
		}
	}
}

void showPath(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH]) {
	StackNode *pNode = NULL;
	int resultArray[HEIGHT][WIDTH] = { 0, };
	int isEmpty = FALSE;

	int i, j;

	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			resultArray[i][j] = mazeArray[i][j];
		}
	}

	if (pStack != NULL) {
		i = 0;
		while (isEmpty == FALSE) {
			pNode = Pop(pStack);
			if (pNode != NULL) {
				int x = pNode->data.x;
				int y = pNode->data.y;

				resultArray[y][x] = Visit;

				if (i > 0) {
					printf("<-");
				}
				printf("(%d,%d) ", x, y);

				i++;
				free(pNode);
			}
			isEmpty = isLinkedStackEmpty(pStack);
		}
		printf("\n");
		printMaze(resultArray);
	}
}

void printMaze(int mazeArray[HEIGHT][WIDTH]) {
	int i, j;

	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			if (mazeArray[i][j] == Wall) {
				printf("*");
			}
			else if (mazeArray[i][j] == Visit) {
				printf(".");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}
int isLinkedStackEmpty(LinkedStack* pStack) {
	int ret = 1;

	if (pStack != NULL) {
		if (pStack->currentCount == 0) {
			ret = 0;
		}
	}
	return ret;
}
int PushList(LinkedStack *pStack, StackNode Node) {
	StackNode *pNode = NULL;

	if (pStack != NULL) {
		pNode = (StackNode*)malloc(sizeof(StackNode));
		if (pNode != NULL) {
			memset(pNode, 0, sizeof(StackNode));
			*pNode = Node;
			pNode->pLink = pStack->pTopElement;
			pStack->pTopElement = pNode;
			pStack->currentCount++;
			return 0;
		}
		else {
			printf("메모리 할당 오류");
		}
	}
}

StackNode *Pop(LinkedStack *pStack) {
	StackNode *pNode = NULL;

	if (pStack != NULL) {
		if (isLinkedStackEmpty(pStack) == 1) {
			pNode = pStack->pTopElement;
			pStack->pTopElement = pNode->pLink;
			pNode->pLink = NULL;
			pStack->currentCount--;
		}

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

void main() {
	LinkedStack *pStack = NULL;

	MapPosition startPos, endPos;

	int mazeArray[HEIGHT][WIDTH] = {
		{0, 0, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 1, 1},
		{1, 1, 1, 0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1 ,1 ,1, 0}
	};

	pStack = createStack();

	if (pStack != NULL) {
		startPos.x = 0;
		startPos.y = 0;
		endPos.x = 7;
		endPos.y = 7;

		printMaze(mazeArray);

		findPath(mazeArray, startPos, endPos, pStack);

		showPath(pStack, mazeArray);

	}
}