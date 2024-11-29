<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “ПИД-регуляторы”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Петручик Д.А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.

# Задание #
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.
---
# Код программы: #
```C++
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double a, b, c, d;
double k, tau0, delay, tau, target_output;
double ctrl_0, ctrl_1, ctrl_2;

void simulate_nonlinear_system() {
    const double initial_y = 2.0;
    vector<double> y = { initial_y, initial_y };  
    double u = 1.0;  
    vector<double> e = { target_output - initial_y, target_output - initial_y };  
    vector<double> prev_u = { u, u };  

    while (fabs(target_output - y.back()) > 0.01) {
        e.push_back(target_output - y.back());  
        u = prev_u.back() + ctrl_0 * e.back() + ctrl_1 * e[e.size() - 2] + ctrl_2 * e[e.size() - 3];

        y.push_back(a * y.back() - b * y[y.size() - 2] + c * u + d * sin(prev_u.back()));
        prev_u.push_back(u);  
    }

    cout << "Step\tOutput\tError\tControl Signal\n";
    for (int i = 0; i < y.size(); ++i) {
        cout << i + 1 << ";" << y[i] << ";" << e[i] << ";" << prev_u[i] << endl;
    }
}

int main() {

    setlocale(LC_ALL, "RU");
   
    cout << "Введите коэффициенты системы:\n";
    cout << "a: "; cin >> a;
    cout << "b: "; cin >> b;
    cout << "c: "; cin >> c;
    cout << "d: "; cin >> d;

    cout << "Введите параметры системы:\n";
    cout << "k : "; cin >> k;
    cout << "tau0 : "; cin >> tau0;
    cout << "delay : "; cin >> delay;
    cout << "tau : "; cin >> tau;
    cout << "target_output (желаемое значение выхода): "; cin >> target_output;

    ctrl_0 = k * (1 + delay / tau0);
    ctrl_1 = -k * (1 + 2 * delay / tau0 - tau0 / tau);
    ctrl_2 = k * (delay / tau0);

    simulate_nonlinear_system();

    return 0;
}

```     
Вывод программы: 
```
Введите коэффициенты системы:
a: 1
b: 2
c: 3
d: 1
Введите параметры системы:
k : 2
tau0 : 1
delay : 1
tau : 2
target_output (желаемое значение выхода): 10
Step    Output  Error   Control Signal
1;2;8;1
2;2;8;1
3;25.8415;8;9
4;-212.844;-15.8415;-78.3659
5;2459.95;222.844;908.218
6;-27227.1;-2449.95;-10037.5
7;302673;27237.1;111607
8;-3.36326e+06;-302663;-1.24013e+06
9;3.73736e+07;3.36327e+06;1.37808e+07
10;-4.15306e+08;-3.73736e+07;-1.53135e+08
11;4.615e+09;4.15306e+08;1.70168e+09
12;-5.12832e+10;-4.615e+09;-1.89096e+10
13;5.69873e+11;5.12832e+10;2.10129e+11
14;-6.33259e+12;-5.69873e+11;-2.33501e+12
15;7.03695e+13;6.33259e+12;2.59473e+13

![График](unliner.png)

