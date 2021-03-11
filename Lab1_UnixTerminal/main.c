#include <stdio.h>

// Counter the power of base with n.
double power(double base, double n) {
	double p = 1;
	for(int i = 0; i < n; i++) {
		p *= base;
	}
	return p;
}

int main() {
	int maxPower = 11;
	// count power 1 to 11
	for (int i=1; i < maxPower; i++) {
		printf("%d to the power 2 is: %f\n", i, power(2, i));
	}
	return 0;
}
