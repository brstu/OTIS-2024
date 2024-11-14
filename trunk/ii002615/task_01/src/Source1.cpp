#include<iostream>
#include<cmath>



double coeff_a = 1.0,
b = 0.5,
c = 0.1,
d = 0.9,
U = 1.5;

using namespace std;

void LINEYKA(double& TLEN);
void nonLINEYKA(double& temp_nonlinear, double& prev_temp_nonlinear, bool& is_first_iteration);


int main() {
	setlocale(LC_ALL, "rus");
	double TLEN = 0, temp_nonlinear = 0, prev_temp_nonlinear = 0;
	bool is_first_iteration = true; // используется для определения первой итерации в функции нелинейной модели 
	cout << "какая начальная температура?";
	cin >> TLEN;
	temp_nonlinear = TLEN;


	int iterations = 10;
	cout << "линейная модель:" << endl;
	for (int i = 0; i < iterations; i++) {
		LINEYKA(TLEN);
	}

	cout << "нелинейная модель:" << endl;
	for (int i = 0; i < iterations; i++) {
		nonLINEYKA(temp_nonlinear, prev_temp_nonlinear, is_first_iteration);
	}

	return 0;
}
void LINEYKA(double& TLEN)
{
	TLEN = coeff_a * TLEN + b * U;
	cout << "////" << TLEN <<  "////" << endl;
}
void nonLINEYKA(double& temp_nonlinear, double& prev_temp_nonlinear, bool& is_first_iteration)
{
	if (is_first_iteration) {
		prev_temp_nonlinear = temp_nonlinear;
		temp_nonlinear = coeff_a * temp_nonlinear + c * U + d * sin(U);
		is_first_iteration = false; // первая итерация закончена
		cout << "////"   << temp_nonlinear << "////" << endl;
	}
	else {
		double temp_new = 0; // переменная для хранения значения новой температуры 
		temp_new = coeff_a * temp_nonlinear - b * pow(prev_temp_nonlinear, 2) + c * U + d * sin(U);
		prev_temp_nonlinear = temp_nonlinear; // устанавливаем новое значение для предыдущего значения
		temp_nonlinear = temp_new; // устанавливаем новое значение для текущего значения
		cout << "////"  << temp_nonlinear << "////" << endl;
	}
}