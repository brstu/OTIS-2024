<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Заруцкий В. Я.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02102**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation, we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

<hr>

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double a = 0.8;
const double b = 0.6;
const double c = 0.4;
const double d = 2.2;
const double u = 0.8;

// Функция для расчета линейной модели
vector<double> liney(int step, double tem) {
    vector<double> result(step);
    result[0] = tem; // Устанавливаем начальное значение
    for (int t = 1; t < step; ++t) {
        result[t] = a * result[t - 1] + b * u; // Формула линейной модели
    }
    return result;
}

// Функция для расчета нелинейной модели
vector<double> noliney(int step, double tem) {
    vector<double> result(step);
    result[0] = tem; // Устанавливаем начальное значение

    if (step > 1) {
        result[1] = a * result[0] + c * u + d * sin(u); // Вычисляем y1 для второго шага
    }
    for (int t = 2; t < step; ++t) {
        result[t] = a * result[t - 1] - b * pow(result[t - 2], 2) + c * u + d * sin(u); // Формула нелинейной модели
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double tem; // Переменная для начальной температуры
    int step; // Переменная для количества шагов

    // Ввод данных
    cout << "Введите начальную температуру: ";
    cin >> tem;
    cout << "Введите количество шагов: ";
    cin >> step;

    // Вычисляем результаты для обеих моделей
    vector<double> lineyres = liney(step + 1, tem);
    vector<double> nolineyres = noliney(step + 1, tem);

    // Вывод результатов для линейной модели
    cout << "Линейная модель:\n";
    for (int t = 0; t <= step; ++t) {
        cout << lineyres[t] << "\n";
    }

    // Вывод результатов для нелинейной модели
    cout << "Нелинейная модель:\n";
    for (int t = 0; t <= step; ++t) {
        cout << nolineyres[t] << "\n";
    }

    return 0;
}
```     
```
Введите начальную температуру: 36
Введите количество шагов: 10
Линейная модель:
36
29.28
23.904
19.6032
16.1626
13.41
11.208
9.44643
8.03714
6.90972
6.00777
Нелинейная модель:
36
30.6982
-751.143
-1164.44
-339459
-1.08512e+06
-6.91405e+10
-7.61807e+11
-2.86824e+21
-3.50505e+23
-4.93609e+42

![График](imagegraf.png)