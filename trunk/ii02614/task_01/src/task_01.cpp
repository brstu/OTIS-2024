#include<iostream>
#include<cmath>

using namespace std;

double a = 1.0, 
b = 0.5, 
c = 0.1, 
d = 0.9, 
u = 1.5;

void liner_model(double& y_liner)
{
	y_liner = a * y_liner + b * u;
	cout << "|" << y_liner  << endl;
}

void unliner_model(double& y_unliner, double& pre_y_unliner,bool& first)
{
	if (first) {
		pre_y_unliner = y_unliner;
		y_unliner = a * y_unliner + c * u + d * sin(u);
		first = false; // первая итерция закончена
		cout << "|" << y_unliner << endl;
	}
	else {
		double vr = 0; // переменная для хранения значения новой температуры 
		vr = a*y_unliner -b*pow(pre_y_unliner,2) + c * u + d * sin(u);
		pre_y_unliner = y_unliner; //устанавливаем новое значение для преведущего значения у
		y_unliner = vr;//устанавливаем новое значение для текущего значения у
		cout << "|" << y_unliner << endl;
	}
}


int main(){
	setlocale(LC_ALL, "rus");
	double y_liner = 0, y_unliner = 0, pre_y_unliner= 0; 
	bool first = true; //используется для определения первой итерации в функции нелинейной модели 
	cout << "Введите начальную температуру:";
	cin >> y_liner;
	y_unliner = y_liner;
	int N = 10;
	cout << "линейная модель:" << endl;
	for (int i = 0; i < N; i++) {
		liner_model(y_liner);
	}
	cout << "нелинейная модель:" << endl;
	for (int i = 0; i < N; i++) {
		unliner_model(y_unliner, pre_y_unliner,first);
	}
	return 0;
}