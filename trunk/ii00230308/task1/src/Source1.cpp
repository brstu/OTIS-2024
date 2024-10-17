#include <iostream>
#include <cmath>
using namespace std;

const double a = 0.95, b = 0.2, c = 1.0, d = 1.5;

double linear_model(double& y, double& u)
{
	y = a * y + b * u;
	return y;
}

double unlinear_model(double& y, double& y_pred, double& y_penultimate, double& u, bool& firstIter)
{
	if (firstIter)
	{
		y_penultimate = y;
		y_pred = a * y + c * u + d*sin(u);
		y = y_pred;
		firstIter = false;
		return y_pred;
	}
	else
	{
		y_pred = a * y - b * pow(y_penultimate, 2) + c * u + d * sin(u);
		y_penultimate = y;
		y = y_pred;
		return y_pred;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double u, y_linear, y_unlinear, y_pred, y_penultimate;
	int N;
	bool firstIter = true;

	cout << "¬ведите начальное значение температуры: ";
	cin >> y_linear;
	y_unlinear = y_linear;

	cout << "\n¬ведите значение тепла: "; 
	cin >> u;

	cout << "\n¬ведите количество итераций: ";
	cin >> N;

	cout << "\n–езультаты вычислений линейной модели: " << endl;
	for (size_t i = 0; i < N; i++)
		cout << i << ") " << linear_model(y_linear, u) << endl;

	cout << "\n–езультаты вычислений нелинейной модели: " << endl;
	for(size_t i=0; i<N; i++)
		cout << i << ") " << unlinear_model(y_unlinear, y_pred, y_penultimate, u, firstIter) << endl;

	return 0;
}