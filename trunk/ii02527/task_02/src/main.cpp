#include <iostream>
#include <math.h>
#include <vector>

std::vector<double> values;
std::vector<double> measured;


double K = .00234f;
double T0 = 1, TD = 120, T = 100;

double	q0 = K + K / T0,
		q1 = -K * (1 + 2 * TD / T0 - T0 / T),
		q2 = K * TD / T0;

double	w0 = 15.23,
		w1 = 21.734,
		w2 = 43.5903;

double	e0 = 0.998,
		e1 = 0.979,
		e2 = 0.997;

double w(double t) {
	return w0 
		+ w1 * t 
		+ w2 * t;
}

double y(double t) {
	return (e0 * w0) 
		+ (e1 * w1) * t
		+ (e2 * w2) * t;
}

double e(double t) {
	return w(t) - y(t);
}

double du(double k) {
	if (k < 1)
		return .0;
	
	return du(k - 1) + q0 * e(k) + q1 * e(k - 1) + q2 * e(k - 2);
}

double u(double k) {
	if (k < 1)
		return .0;

	return u(k - 1) + du(k);
}

int main() {

	std::cout << q0 << ", " << q1 << ", " << q2 << std::endl;

	for (int i = 0; i < 100; i++) {
		values.push_back(w(i));
		measured.push_back(y(i));
	}

	// for (int i = 0; i < 100; i++)
	// 	std::cout << values[i] << "\t" << measured[i] << std::endl;

	for (int i = 0; i < 100; i++) {
		//std::cout << u(i) << std::endl;
		measured[i] -= K * u(i);
	}

	for (int i = 0; i < 100; i++)
		std::cout << values[i] << "\t" << measured[i] << std::endl;	


	return 0;
}