<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Modeling controlled object”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-25</p>
<p align="right">Гродзинский А.Д.</p>
<p align="right">Проверил:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.


<hr>

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Константы для модели
const double a = 0.7;
const double b = 0.6;
const double c = 0.2;
const double d = 5;

// Функция линейной модели
void LinearModel(int Steps, double Y0, double U, double YT) {
    vector<double> temperaturesLinear; // Вектор для хранения температур
    double y = Y0; // Начальное значение температуры

    // Цикл для расчета температуры в каждом шаге
    for (int tau = 0; tau < Steps; ++tau) {
        U = U + YT; // Обновление управляющего сигнала
        y = a * y + b * U; // Расчет новой температуры
        temperaturesLinear.push_back(y); // Сохранение температуры в вектор
    }

    // Вывод результатов линейной модели
    cout << "Линейные модель температуры:\n";
    for (size_t i = 0; i < temperaturesLinear.size(); ++i) {
        cout << "Время " << i + 1 << ": " << temperaturesLinear[i] << "\n"; // Вывод температуры в каждый момент времени
    }
}

// Функция нелинейной модели
void NonlinearModel(int Steps, double Y0, double U, double YT) {
    vector<double> temperaturesNonlinear; // Вектор для хранения температур
    double y = Y0; // Начальное значение температуры
    double y_prev = Y0; // Предыдущее значение температуры

    // Цикл для расчета температуры в каждом шаге
    for (int tau = 0; tau < Steps; ++tau) {
        U = U + YT; // Обновление управляющего сигнала
        y = a * y - b * y_prev * y_prev + c * U + d * sin(U - 1); // Расчет новой температуры с учетом нелинейностей
        temperaturesNonlinear.push_back(y); // Сохранение температуры в вектор
        y_prev = y; // Обновление предшествующей температуры
    }

    // Вывод результатов нелинейной модели
    cout << "Нелинейной модель температуры:\n";
    for (size_t i = 0; i < temperaturesNonlinear.size(); ++i) {
        cout << "Время " << i + 1 << ": " << temperaturesNonlinear[i] << "\n"; // Вывод температуры в каждый момент времени
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    int Steps = 7; // Количество шагов
    double Y0 = 30; // Начальная температура
    double U = 5; // Начальное значение управляющего сигнала
    double YT = 1.5; // Шаг изменения управляющего сигнала
    LinearModel(Steps, Y0, U, YT); // Вызов линейной модели
    NonlinearModel(Steps, Y0, U, YT); // Вызов нелинейной модели

    return 0; // Завершение программы
}
'''
Вывод:
'''
Линейные модель температуры:
Время 1: 24.9
Время 2: 22.23
Время 3: 21.261
Время 4: 21.4827
Время 5: 22.5379
Время 6: 24.1765
Время 7: 26.2236
Нелинейной модель температуры:
Время 1: -521.228
Время 2: -163367
Время 3: -1.60134e+10
Время 4: -1.53857e+20
Время 5: -1.42032e+40
Время 6: -1.21038e+80
Время 7: -8.7901e+159
'''
![График](./graphic.png)