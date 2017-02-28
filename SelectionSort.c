#include <stdio.h>

typedef struct HeapElementType {
	int key;
	char data;
}HeapNode;

typedef struct ArrayHeapNode {
	int maxElementCount;
	int currentElementCount;
	HeapNode *pElement;
} ArrayMaxHeap, ArrayMinHeap;

void printArray(int values[], int count);
void selectionSort(int values[], int count);
void BubbleSort(int values[], int count);
void BubbleSort(int values[], int count);
void quickSort(int values[], int start, int end);
int partitionQuickSort(int values[], int start, int end);
void insertionSort(int values[], int count);
void shellInsertionSort(int value[], int start, int end, int interval);
void shellSort(int value[], int count);

ArrayMaxHeap* CreateArrayMaxHeap(int maxElementCount) {
	ArrayMaxHeap *pReturn = NULL;
	int i = 0;

	if (maxElementCount > 0) {
		pReturn = (ArrayMaxHeap *)malloc(sizeof(ArrayMaxHeap));
		if (pReturn->pElement != NULL) {

			pReturn->currentElementCount = 0;
			pReturn->maxElementCount = maxElementCount;
			pReturn->pElement = (HeapNode *)malloc(sizeof(HeapNode)*(maxElementCount + 1));
			if (pReturn->pElement == NULL) {
				printf("메모리 할당 오류\n");
				free(pReturn);
				return NULL;
			}
			memset(pReturn->pElement, 0, sizeof(HeapNode)*(maxElementCount + 1));
		}
		else {
			printf("메모리 할당 오류\n");
		}
	}
	else {
		printf("최대 노드 개수 0개 보다 커야됨\n");
	}
	return pReturn;
}

void insertMaxHeapAH(ArrayMaxHeap *pHeap, HeapNode element) {
	int i = 0;

	if (pHeap != NULL) {
		if (pHeap->currentElementCount == pHeap->maxElementCount) {
			printf("히프가 가득찼습니다.\n");
			return;
		}
		pHeap->currentElementCount++;
		i = pHeap->currentElementCount;

		while ((i != 1) && (element.key > pHeap->pElement[i / 2].key)) {
			pHeap->pElement[i] = pHeap->pElement[i / 2];
			i /= 2;
		}
		pHeap->pElement[i] = element;

	}
}

HeapNode *deleteMaxHeapAH(ArrayMaxHeap *pHeap) {
	HeapNode *pReturn = NULL;
	HeapNode *pTemp = NULL;
	int i = 0, parent = 0, child = 0;
	if (pHeap != NULL) {
		pReturn = (HeapNode *)malloc(sizeof(HeapNode));
		*pReturn = pHeap->pElement[1];
		i = pHeap->currentElementCount;
		pTemp = &(pHeap->pElement[i]);
		pHeap->currentElementCount--;

		parent = 1;
		child = 2;
		while (child <= pHeap->currentElementCount) {
			if ((child < pHeap->currentElementCount) && pHeap->pElement[child].key < pHeap->pElement[child + 1].key) {
				child++;
			}
			if (pTemp->key >= pHeap->pElement[child].key) {
				break;
			}
			pHeap->pElement[parent] = pHeap->pElement[child];
			parent = child;
			child *= 2;

		}
		pHeap->pElement[parent] = *pTemp;
	}
	return pReturn;
}

int partitionQuickSort(int values[], int start, int end) {
	int pivot = 0;
	int temp = 0, left = 0, right = 0;
	left = start;
	right = end;
	pivot = end;

	while (left < right) {
		while ((values[left] < values[pivot]) && (left < right)) {
			left++;
		}
		while ((values[right] >= values[pivot]) && (left < right)) {
			right--;
		}

		if (left < right) {
			temp = values[left];

			values[left] = values[right];
			values[right] = temp;
			printf("start - [%d], end - [%d], pivot - [%d], in-loop,", start, end, values[pivot]);

			printArray(values, end - start + 1);
		}
 	}
	temp = values[pivot];
	values[pivot] = values[right];
	values[right] = temp;

	printf("start - [%d], end - [%d], pivot - [%d], out-loop,", start, end, values[right]);
	printArray(values, end - start + 1);
	
	return right;
}

void heapSort(int values[], int count) {
	int i = 0;
	ArrayMaxHeap *pHeap = NULL;

	pHeap = CreateArrayMaxHeap(8);

	if (pHeap != NULL) {
		HeapNode node;
		for (i = 0; i < count; i++) {
			node.key = values[i];
			insertMaxHeapAH(pHeap, node);
		}

		for (i = 0; i < count; i++) {
			HeapNode *pNode = deleteMaxHeapAH(pHeap);
			if (pNode != NULL) {
				values[i] = pNode->key;
				free(pNode);
			}
		}
	}
}
void main() {
	int values[] = {80, 50, 70, 10, 60, 20, 40, 30};

	printf("Before Sort\n");
	printArray(values, 8);

	//selectionSort(values, 8);
	//BubbleSort(values, 8);
	//quickSort(values, 0, 7);
	//insertionSort(values, 8);
	//shellSort(values, 8);
	heapSort(values, 8); // 내림 차순
	printf("\nAfter Sort\n");
	printArray(values, 8);


}
void insertionSort(int values[], int count) {
	int i = 0, pre = 0, next = 0, j = 0;
	int temp = 0;
	for (int i = 1; i < count; i++) {
		temp = values[i];
		j = i;
		while ((j > 0) && values[j - 1] > temp) {
			values[j] = values[j - 1];
			j--;
		}
		values[j] = temp;
		printf("Step - %d,", i);
		printArray(values, count);
	}
}

void quickSort(int values[], int start, int end) {
	int pivot = 0;
	if (start < end) {
		pivot = partitionQuickSort(values, start, end);
		quickSort(values, start, pivot - 1);
		quickSort(values, pivot + 1, end);
	}
}
void BubbleSort(int values[], int count) {
	int i = 0, j = 0, count1 = count, temp = 0;
	for (i = 0; i < count; i++) {
		for (j = 0; j < count1-1; j++) {
			if (values[j] > values[j + 1]) {
				temp = values[j + 1];
				values[j + 1] = values[j];
				values[j] = temp;
			}
		}
		count1--;
		printf("Step- %d ", i + 1);
		printArray(values, count);
	}
}

void selectionSort(int values[], int count) {
	int temp = 0;
	int i = 0, j = 0, min = 0, k = 0;

	for (i = 0; i < count; i++) {
		temp = values[i];
		min = values[i];
		for (j = i + 1; j < count; j++) {
			if (temp > values[j]) {
				temp = values[j];
				min = j;
			}
		} 
		values[min] = values[i];
		values[i] = temp;

		printf("Step- %d ", i + 1);
		printArray(values, count);

	}
}
void shellSort(int value[], int count) {
	int i = 0, interval = 0;

	interval = count / 2;

	while(interval >= 1) {
		for (i = 0; i < interval; i++) {
			shellInsertionSort(value, i, count - 1, interval);
		}
		printf("Interval-%d, ", interval);
		printArray(value, count);
		interval /= 2;
	}
}

void shellInsertionSort(int value[], int start, int end, int interval) {
	int i = 0;
	int item = 0, index = 0;

	for (i = start + interval; i <= end; i = i + interval) {
		item = value[i];
		index = i - interval;

		while ((index >= start) && item < value[index]) {
			value[index + interval] = value[index];
			index = index - interval;
		}

		value[index + interval] = item;
	}
}

void printArray(int values[], int count) {
	for (int i = 0; i < count; i++) {
		printf("%d ", values[i]);
	}
	printf("\n");
}