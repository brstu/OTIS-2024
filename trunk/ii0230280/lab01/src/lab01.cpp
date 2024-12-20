#include <stdio.h>
#include <math.h>

const double a = 0.1;
const double b = 0.3;
const double c = 0.05;
const double d = 0.75;

const double a0 = 15.5;
const double u0 = 21;

const double y00 = 1.9248;
const double y01 = 3.2139;


double u(unsigned int t) {
	return a0 * t + u0;
}


double LinM(unsigned int t) {
	if (t < 1)
		return y00;

	return a * LinM(t - 1) + b * u(t - 1);
}

double nonlinM(unsigned int t) {
	if (t < 1)
		return y00;

	if (t < 2)
		return y01;

	return a * nonlinM(t - 1) - b * pow(nonlinM(t - 2), 2) + c * u(t - 1) + d * sin(u(t - 2));
}

int main() {

	printf("Lin model\n");
	for (int t = 1; t < 11; t++)
		printf("%d\t%.4f\n", t, LinM(t));

	printf("Nonlin model\n");
	for (int t = 1; t < 11; t++)
		printf("%d\t%.4f\n", t, nonlinM(t));

	return 0;
}