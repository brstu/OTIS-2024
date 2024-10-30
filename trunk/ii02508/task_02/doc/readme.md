<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “ПИД-регуляторы”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-25</p>
<p align="right">Елец Ю. А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

1. Написать отчет по выполненной лабораторной работе №2 в .md формате (*readme.md*) и с помощью **pull request** разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc**.
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
3. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2023/edit/main/readme.md?#L17-L17).

**Задание.**
На **C++** реализовать программу, моделирующую рассмотренный выше ПИД-регулятор.  В качестве объекта управления использовать математическую модель, полученную в предыдущей работе.
В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.

---

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double a = 0.5;
double b = 0.6; 
double c = 0.6; 
double d = 0.6;
double K = 0.8;
double T0 = 1.1;
double TD = 1.0;
double T = 1.1;
double q0, q1, q2;
double val = 10;

void nonlinearModel() {
	const int start = 2;
	vector<double> outputs = { start, start }; 

	double u = 1.0; 
	vector<double> err = { val - start, val - start };  
	vector<double> u_prev = { u, u };

	while (abs(val - outputs.back()) > 0.01) {
		err.push_back(val - outputs.back()); 
		u = u_prev.back() + q0 * err.back() + q1 * err[err.size() - 2] + q2 * err[err.size() - 3];
		outputs.push_back(a * outputs.back() - b * outputs[outputs.size() - 2] + c * u + d * sin(u_prev.back()));
		u_prev.push_back(u);  
	}

	for (int i = 0; i < outputs.size(); i++) {
		cout << "Шаг: " << i + 1 << endl;
		cout << "Start: " << outputs[i] << endl;
		cout << "Ошибка: " << err[i] << endl;
		cout << "u: " << u_prev[i] << endl;
	}
}

int main() {
	setlocale(LC_ALL, "ru");
    q0 = K * (1 + (TD / T0)),
    q1 = -K * (1 + 2 * (TD / T0) - (T0 / T)),
    q2 = K * (TD / T0);

	nonlinearModel();
    return 0;
}
```

Результат выполнения программы:

```
Шаг: 1
Start: 2
Ошибка: 8
u: 1
Шаг: 2
Start: 2
Ошибка: 8
u: 1
Шаг: 3
Start: 4.74488
Ошибка: 8
u: 7.4
Шаг: 4
Start: 7.47636
Ошибка: 5.25512
u: 9.60782
Шаг: 5
Start: 7.76393
Ошибка: 2.52364
u: 11.6365
Шаг: 6
Start: 8.03685
Ошибка: 2.23607
u: 15.2027
Шаг: 7
Start: 9.72082
Ошибка: 1.96315
u: 16.7839
Шаг: 8
Start: 9.0989
Ошибка: 0.279184
u: 15.981
Шаг: 9
Start: 9.5825
Ошибка: 0.901105
u: 18.3789
Шаг: 10
Start: 9.80518
Ошибка: 0.417502
u: 17.9089
Шаг: 11
Start: 9.62104
Ошибка: 0.194816
u: 18.2545
Шаг: 12
Start: 9.90322
Ошибка: 0.378962
u: 18.8536
Шаг: 13
Start: 10.3365
Ошибка: 0.0967779
u: 18.5918
Шаг: 14
Start: 10.001
Ошибка: -0.336495
u: 18.2128
```