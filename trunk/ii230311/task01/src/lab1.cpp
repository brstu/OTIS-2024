#include <iostream>
#include <cmath>
using namespace std;
 // Неизменные
const double  A = 0.6;
const double B = 0.002;
const double C = 0.4;
const double D = 0.6;
// Функция для линейной модели
void linearMod(double U, int totalSteps, double Y) {
	for (int i = 1; i <= totalSteps; ++i) {
		cout << "Time:" << i << ", LinearOut : " << Y << endl;
		Y = A * Y + B * U; // Обновление значения
	}
	cout << "---------------------\"n";
}
			// Функция для нелинейной модели
			 void nonlinearMod(double U, int totalSteps, double Y, double Y1) {
			for (int i = 1; i <= totalSteps; ++i) {
				cout << "Time: " << i << ", NonlinearOut: " << Y << endl;
				double newY = A * Y - B * Y1 * Y1 + C * U + D * sin(U); // Обновление значения; // Сохранение предыдущего значения; // Обновление текущего значения
			}
		}
		int main() {
			setlocale(LC_ALL, "rus");
			double U; // Начальное тепло
			int totalSteps = 45; // Количество итераций
			double Y; // Нулевое значение для линейной модели 
			double Y1;  // Нулевое значение для нелинейной модели
		
				
				// Ввод данных вручную
			cout << "Введите входное тепло: ";
				cin >> U;
			cout <<"Введите начальное значение для линейной модели: ";
			cin >> Y;
			cout << "Введите начальное значение для нелинейной модели: ";
			cin >> Y1;
			cout << "linear model: \n";
				linearMod(U, totalSteps, Y);
			cout << "Nonlinear model: \n";
			nonlinearMod(U, totalSteps, Y, Y1);
			return 0;
		}