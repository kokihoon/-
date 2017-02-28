#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum PrecedenceType {lparen, rparen, times, divides, plus, minus, operand} Precedence;

typedef struct ExprTokenType {
	float value;
	Precedence type;
}ExprToken;

typedef struct StackNodeType {
	ExprToken data;
	struct StackNodeType *pLink;
} StackNode;

typedef struct StackType {
	int currentCount;
	struct StackType *pTopElement;
}LinkedStack;

StackNode *Peek(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);
LinkedStack *createStack();
int PushList(LinkedStack *pStack, StackNode Node);
StackNode *Pop(LinkedStack *pStack);

int PushListExprToken(LinkedStack* pStack, ExprToken data);
void convertInfixToPostfix(ExprToken *pExprTokens, int tokenCount);
int inStackPrecedence(Precedence oper);

int isLinkedStackEmpty(LinkedStack* pStack) {
	int ret = 1;

	if (pStack != NULL) {
		if (pStack->currentCount == 0) {
			ret = 0;
		}
	}
	return ret;
}
int outStackPrecedence(Precedence oper) {
	switch (oper) {
	case lparen:
		return 5;

	case rparen:
		return 4;

	case times:
	case divides:
		return 2;
	case plus:
	case minus:
		return 1;
	}
	return -1;
}

void printToken(ExprToken element) {
	switch (element.type) {
	case lparen:
		printf("(\n");
		break;

	case rparen:
		printf(")\n");
		break;
	
	case plus:
		printf("+\n");
		break;

	case minus:
		printf("-\n");
		break;

	case times:
		printf("*\n");
		break;

	case divides:
		printf("/\n");
		break;

	case operand:
		printf("%f\n", element.value);
		break;
	}
}

int inStackPrecedence(Precedence oper) {
	switch (oper) {
	case lparen:
		return 0;

	case rparen:
		return 4;

	case times:
	case divides:
		return 2;
	case plus:
	case minus:
		return 1;
	}
	return -1;
}

void convertInfixToPostfix(ExprToken *pExprTokens, int tokenCount) {
	LinkedStack *pStack = NULL;
	StackNode *pNode = NULL;
	Precedence tokenType;
	Precedence inStackTokenType;
	StackNode *pNode1 = NULL;
	int i = 0;

	if (pExprTokens == NULL) return;

	pStack = createStack();
	if (pStack != NULL) {
		for (i = 0; i < tokenCount; i++)  {
			tokenType = pExprTokens[i].type;
			switch (tokenType) {
			case operand :
				printf("%f\n", pExprTokens[i].value);
				break;

			case rparen :
				pNode = Pop(pStack);
				while (pNode != NULL && pNode->data.type != lparen) {
					printToken(pNode->data);
					free(pNode);

					pNode = Pop(pStack);
				}
				if (pNode != NULL) free(pNode);
				break;

			default :
				while (isLinkedStackEmpty(pStack) == 1)  {
					inStackTokenType = Peek(pStack)->data.type;
					if (outStackPrecedence(tokenType) <= inStackPrecedence(inStackTokenType)) {
						pNode = Pop(pStack);
						if (pNode != NULL) {
							printToken(pNode->data);
							free(pNode);
						}
					}
					else {
						break;
					}
				}
				PushListExprToken(pStack, pExprTokens[i]);
				break;
			}
		}

		while (isLinkedStackEmpty(pStack) == 1) {
			pNode = Pop(pStack);
			if (pNode != NULL) {
				printToken(pNode->data);
				free(pNode);
			}
		}
	}
}

StackNode *Peek(LinkedStack* pStack) {
	StackNode* pReturn = NULL;

	if (pStack != NULL) {
		if (isLinkedStackEmpty(pStack) == 1) {
			pReturn = pStack->pTopElement;
		}
	}
	return pReturn;
}

int PushListExprToken(LinkedStack* pStack, ExprToken data) {
	StackNode node = { 0, };
	node.data = data;
	return PushList(pStack, node);
}
int PushList(LinkedStack *pStack, StackNode Node) {
	StackNode *pNode = NULL;
	int ret = 1;
	if (pStack != NULL) {
		pNode = (StackNode*)malloc(sizeof(StackNode));
		if (pNode != NULL) {
			memset(pNode, 0, sizeof(StackNode));
			*pNode = Node;
			pNode->pLink = pStack->pTopElement;
			pStack->pTopElement = pNode;
			pStack->currentCount++;
			ret = 0;
		}
		else {
			printf("메모리 할당 오류");
		}
	}
	return ret;
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
void convert(ExprToken *pExprTokens, int tokenCount) {
	LinkedStack *pStack = NULL;
	StackNode *pNode = NULL;
	Precedence tokenType;
	Precedence inStackTokenType;
	int i = 0;

	if (pExprTokens == NULL) return;

	pStack = createStack();
	if (pStack != NULL) {
		for (i = 0; i < tokenCount; i++) {
			tokenType = pExprTokens[i].type;

			switch (tokenType) {
			case operand:
				printf("%f\n", pExprTokens[i].value);
				break;

			case rparen:
				pNode = Pop(pStack);
				while (pNode != NULL && pNode->data.type != lparen) {
					printToken(pNode->data);
					free(pNode);
					pNode = Pop(pStack);
				}

				if (pNode != NULL) free(pNode);
				break;


			default:
				while (isLinkedStackEmpty(pStack) == 1) {
					inStackTokenType = Peek(pStack)->data.type;
					if (outStackPrecedence(tokenType) <= inStackPrecedence(inStackTokenType)) {
						pNode = Pop(pStack);
						if (pNode != NULL) {
							printToken(pNode->data);
							free(pNode);
						}
					}
					else {
						break;
					}
				}
				PushListExprToken(pStack, pExprTokens[i]);
				break;
			}
		}
		while (isLinkedStackEmpty(pStack) == 1) {
			pNode = Pop(pStack);
			if (pNode != NULL) {
				printToken(pNode->data);
				free(pNode);
			}
		}
	}
}
void calcExpr(ExprToken *pExprTokens, int tokenCount) {
	LinkedStack *pStack = NULL;
	StackNode *pNode1 = NULL, *pNode2 = NULL;

	Precedence tokenType;

	int i = 0;
	if (pExprTokens == NULL) {
		return;
	}

	pStack = createStack();
	if (pStack != NULL) {
		for (i = 0; i < tokenCount; i++) {
			tokenType = pExprTokens[i].type;

			if (tokenType == operand) {
				PushListExprToken(pStack, pExprTokens[i]);
			}
			else {
				pNode2 = Pop(pStack);
				if (pNode2 != NULL) {
					pNode1 = Pop(pStack);
					if (pNode1 != NULL) {
						float op1 = pNode1->data.value;
						float op2 = pNode2->data.value;

						ExprToken newToken;
						newToken.type = operand;

						switch (tokenType) {
						case plus:
							newToken.value = op1 + op2;
							break;
						case minus: newToken.value = op1 - op2;
							break;
						case times:
							newToken.value = op1*op2;
							break;
						case divides:
							newToken.value = op1 / op2;
							break;
						}
						PushListExprToken(pStack, newToken);

						free(pNode1);
					}
					free(pNode2);
				}
			}
		}

		pNode1 = Pop(pStack);
		if (pNode1 != NULL) {
			printf("수식 결과 계산[%f]\n", pNode1->data.value);
			free(pNode1);
		}
		else {
			printf("오류");
		}
	}
}
void main() {
	int i = 0;

	ExprToken *pExprTokens = (ExprToken *)malloc(sizeof(ExprToken) * 8);
	
	pExprTokens[0].type = operand;
	pExprTokens[0].value = 2;
	pExprTokens[1].type = operand;
	pExprTokens[1].value = 3;
	pExprTokens[2].type = operand;
	pExprTokens[2].value = 4;
	pExprTokens[3].type = plus;
	pExprTokens[3].value = 0;
	pExprTokens[4].type = operand;
	pExprTokens[4].value = 5;
	pExprTokens[5].type = times;
	pExprTokens[5].value = 0;
	pExprTokens[6].type = minus;
	pExprTokens[6].value = 0;
	printf("Expression: 2 3 4 + 5 * -\n");
	calcExpr(pExprTokens, 7);
	free(pExprTokens);

	pExprTokens = (ExprToken *)malloc(sizeof(ExprToken) * 9);
	pExprTokens[0].type = operand;
	pExprTokens[0].value = 2;
	pExprTokens[1].type = minus;
	pExprTokens[1].value = 0;
	pExprTokens[2].type = lparen;
	pExprTokens[2].value = 0;
	pExprTokens[3].type = operand;
	pExprTokens[3].value = 3;
	pExprTokens[4].type = plus;
	pExprTokens[4].value = 0;
	pExprTokens[5].type = operand;
	pExprTokens[5].value = 4;
	pExprTokens[6].type = rparen;
	pExprTokens[6].value = 0;
	pExprTokens[7].type = times;
	pExprTokens[7].value = 0;
	pExprTokens[8].type = operand;
	pExprTokens[8].value = 5;

	printf("Infix Expression : 2 - (3 + 4) * 5\n");
	printf("Postfix Expreesion: \n");

	convertInfixToPostfix(pExprTokens, 9);
	free(pExprTokens);
}