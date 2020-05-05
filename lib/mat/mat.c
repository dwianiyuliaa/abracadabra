#include "mat.h"

int mod(int a, int b) {
	while (a >= b) {
		a = a - b;
	}
	return a;
}

//menghitung div
int div(int a, int b) {
	int q = 0;
	while (q * b <= a) {
		q = q + 1;
	}
	return q - 1;
}