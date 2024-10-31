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

double a = 0.5, b = 0.6,  c = 0.6, d = 0.6;
double K = 0.8, T0 = 1.1, TD = 1.0, T = 1.1;
double q0, q1, q2;
double d_val = 10;

void nonlinearModel() {
    q0 = K * (1 + (TD / T0)),
    q1 = -K * (1 + 2 * (TD / T0) - (T0 / T)),
    q2 = K * (TD / T0);

	double u = 1.0; 
	const int start = 2;
	vector<double> outputs = { start, start }; 
	vector<double> err = { d_val - start, d_val - start };  
	vector<double> u_p = { u, u };

	while (abs(d_val - outputs.back()) > 0.01) {
		err.push_back(d_val - outputs.back()); 
		u = u_p.back() + q0 * err.back() + q1 * err[err.size() - 2] + q2 * err[err.size() - 3];
		outputs.push_back(a * outputs.back() - b * outputs[outputs.size() - 2] + c * u + d * sin(u_p.back()));
		u_p.push_back(u);  
	}

	for (int i = 0; i < outputs.size(); i++) {
	    cout << i + 1 << ", " << outputs[i] << ", " << err[i] << ", " << u_prev[i] << endl;
	}
}

int main() {
	setlocale(LC_ALL, "ru");
    nonlinearModel();
    return 0;
}
```

Результат выполнения программы:

```
1, 2, 8, 1
2, 2, 8, 1
3, 4.74488, 8, 7.4
4, 7.47636, 5.25512, 9.60782
5, 7.76393, 2.52364, 11.6365
6, 8.03685, 2.23607, 15.2027
7, 9.72082, 1.96315, 16.7839
8, 9.0989, 0.279184, 15.981
9, 9.5825, 0.901105, 18.3789
10, 9.80518, 0.417502, 17.9089
11, 9.62104, 0.194816, 18.2545
12, 9.90322, 0.378962, 18.8536
13, 10.3365, 0.0967779, 18.5918
14, 10.001, -0.336495, 18.2128
```