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
		printf("원판 1을 %c에서 %c로 옮겼습니다.\n", from, to);
	}
	else {
		Hanoi(n - 1, from, to, temp);
		printf("원판 %d를 %c에서 %c로 옮겼습니다.\n", n, from, to);
		Hanoi(n - 1, temp, from, to);
	}
}