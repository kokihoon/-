#include <stdio.h>
void printArray(int values[], int count);
void selectionSort(int values[], int count);
void BubbleSort(int values[], int count);
void BubbleSort(int values[], int count);
void quickSort(int values[], int start, int end);
int partitionQuickSort(int values[], int start, int end);
void insertionSort(int values[], int count);
void shellInsertionSort(int value[], int start, int end, int interval);
void shellSort(int value[], int count);

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
void main() {
	int values[] = {80, 50, 70, 10, 60, 20, 40, 30};

	printf("Before Sort\n");
	printArray(values, 8);

	//selectionSort(values, 8);
	//BubbleSort(values, 8);
	//quickSort(values, 0, 7);
	//insertionSort(values, 8);
	shellSort(values, 8);
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