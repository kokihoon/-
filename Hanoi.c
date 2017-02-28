#include <stdio.h>

void Hanoi(int n, char from, char temp, char to);
void main() {
	char from = 'A';
	char temp = 'B';
	char to = 'C';

	Hanoi(3, from, temp, to);

	
}

void Hanoi(int n, char from, char temp, char to) {
	
	if (n == 1) {
		printf("���� 1�� %c���� %c�� �Ű���ϴ�.\n", from, to);
	}
	else {
		Hanoi(n - 1, from, to, temp);
		printf("���� %d�� %c���� %c�� �Ű���ϴ�.\n", n, from, to);
		Hanoi(n - 1, temp, from, to);
	}
}