#include<iostream>
#include<cmath>

using namespace std;

double a = 1.0, 
b = 0.5, 
c = 0.1, 
d = 0.9, 
u = 1.5;

void liner_model(double& y0)
{
	y0 = a * y0 + b * u;
	cout << "|" << y0  << endl;
}

void unliner_model(double& y00, double& y01,bool& first)
{
	if (first) {
		y01 = y00;
		y00 = a * y00 + c * u + d * sin(u);
		first = false; // первая итерция закончена
		cout << "|" << y00 << endl;
	}
	else {
		double vr = 0; // переменная для хранения значения новой температуры 
		vr = a*y00 -b*pow(y01,2) + c * u + d * sin(u);
		y01 = y00; //устанавливаем новое значение для преведущего значения у
		y00 = vr;//устанавливаем новое значение для текущего значения у
		cout << "|" << y00 << endl;
	}
}


int main(){
	setlocale(LC_ALL, "rus");
	double y0 = 0, y00 = 0, y_01= 0; // переменная y0 и у00 это начальные значения температуры для линейной и нелинейной модели, у_01 - это пред. значение в нелинейной модели
	bool first = true; //используется для определения первой итерации в функции нелинейной модели 
	cout << "Введите начальную температуру:";
	cin >> y0;
	y00 = y0;
	int N = 10;
	cout << "линейная модель:" << endl;
	for (int i = 0; i < N; i++) {
		liner_model(y0);
	}
	cout << "нелинейная модель:" << endl;
	for (int i = 0; i < N; i++) {
		unliner_model(y00,y_01,first);
	}
	return 0;
}

