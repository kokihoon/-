#include <stdio.h>

void main() {
	int n = 5, sum = 0;
	sum = Recursion(n);
	printf("sum : %d\n", sum);
}
/*
int Recursion(int n) {
	int ret = 0;
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}

	else {
		ret = Recursion(n - 1) + Recursion(n - 2);
	}
	return ret;
}
*/
int Recursion(int n) {
	int ret = 0;

	if (n < 2) {
		ret = n;
	}
	else {
		int i = 0, temp = 0, current = 1, last = 0;
		for (i = 2; i <= n; i++) {
			temp = current;
			current += last;
			last = temp;
		}
		ret = current;
	}
	return ret;
}