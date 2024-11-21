#include <iostream>
#include <cmath>
using namespace std;

const double m = 0.95, a = 0.2, r = 1.0, k = 1.5;

double linear_model(double& y, double& u)
{
	y = m * y + a * u;
	return y;
}

double unlinear_model(double& y, double& y_pred, double& y_penultimate, double& u, bool& firstIter)
{
	if (firstIter)
	{
		y_penultimate = y;
		y_pred = m * y + r * u + k*sin(u);
		y = y_pred;
		firstIter = false;
		return y_pred;
	}
	else
	{
		y_pred = m * y - a * pow(y_penultimate, 2) + r * u + k * sin(u);
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