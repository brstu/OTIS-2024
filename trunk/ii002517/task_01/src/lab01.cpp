#include <iostream>
#include <vector>
#include <cmath>
class TempratureControle {
public:
	double a;
	double b;
	double c;
	double d;
	double u;
	int t;
	std::vector<double>y{ 1.1, };
	std::vector<double>yy{ 1.1, };
	void linear_f() {
		double y_1 = a * y.back() + b * u;
		y.push_back(y_1);
	}
	void non_linear_f() {
		double y_1 = a * yy.back() - b * pow(yy.back(), 2) + c * u + d * sin(u);
		yy.push_back(y_1);
	}

	TempratureControle(double a, double b, double c, double d, double u, int t) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->u = u;
		this->t = t;
	}
};
int main() {
	TempratureControle obj(0.6, 0.8, 0.2, 1.0, 0.2, 15);
	for (int i = 0; i < obj.t; i++) {
		obj.linear_f();
	}
	for (int i = 0; i < obj.t; i++) {
		obj.non_linear_f();
	}
	for (int i = 0; i < obj.y.size(); i++) {
		std::cout << obj.y[i] << " ";
		std::cout << obj.yy[i] << std::endl;
	}
	return 0;
}