#include <iostream>
#include <math.h>
#include <vector>

class Function {
public:

	const double a = 0.4;
	const double b = 0.4;
	const double c = 0.8;
	const double d = 1.2;
	double u = 1.1;

	const int time = 5;

	std::vector<double> first_function{ 1.2 };
	std::vector<double> second_function{ 0.2 };

	void linear_function() {

		double y1 = a * first_function.back() + b * u;
		first_function.push_back(y1);

	}

	void non_linear_function() {

		double y1 = a * second_function.back() - b * pow(second_function[second_function.size() - 1], 2) + c * u + d * sin(u);
		second_function.push_back(y1);

	}

};







int main() {

	Function func;

	for (int i = 0; i < func.time; i++) {

		func.linear_function();

	}

	for (int i = 0; i < func.time; i++) {

		func.non_linear_function();

	}

	for (int i = 0; i < func.time; i++) {
		
		std::cout << i + 1 << "  " << func.first_function[i + 1] << "  ";
		std::cout << func.second_function[i + 1] << std::endl;
	}


	return 0;
}
