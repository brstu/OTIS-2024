#include <stdio.h>
#include <math.h>
#include <vector>

const double a = 0.52;
const double b = 0.0015;
const double c = 0.32;
const double d = 0.51;

double K = .154f;
double T0 = 140, TD = 90, T = 100;

double	q0 = K + K * TD / T0,
		q1 = -K * (1 + 2 * TD / T0 - T0 / T),
		q2 = K * TD / T0;

const double u0 = 3.0;

const double w  = 42.503;
const double yS = 40.32523;

double de(double y) {
	return abs(w - y);
}

int main() {

    std::vector<double> u = {u0, u0};
    std::vector<double> y = {yS, K * yS + c * u0 + d * sin(u0) };
    std::vector<double> e = {de(y[0]), de(y[1])};

    printf("%10s%10s%10s\n", "y", "u", "e");

    for (; e.back() > .001; ) {
        printf("%10.5f %10.5f %10.5f\n", y.back(), u.back(), e.back());

        e.push_back(de(y.back()));
        double u_0 = u.back() + q0 * e.back() + q1 * e[e.size() - 2] + q2 * e[e.size() - 3];
        y.push_back(K * y.back() - b * y[y.size() - 2] + c * u_0 + d * sin(u.back()));
        u.push_back(u_0);
    }

	return 0;
}