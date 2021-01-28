#include <stdio.h>

double power(double base, double n) {
	double p = 1;
	for(int i = 0; i < n; i++) {
		p *= base;
	}
	return p;
}

int main() {
	double num1 = power(2, 1);
	double num2 = power(2, 10);
	printf("1 to the power 2 is: %f\n", num1);
	printf("10 to the power 2 is: %f\n", num2);
	return 0;
}
