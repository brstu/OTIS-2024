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
<p align="right">Мохорева Т. Д.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №2 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii230290\task_02\doc**.
2. Исходный код написанной программы разместить в каталоге: **trunk\ii230290\task_02\src**.

# Задание #
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.
---
# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <cmath>
#include <array>
#include <clocale>
#include <iomanip>

using namespace std;

void runControlLoop() {
    const double proportionalGain = 0.097;     // Пропорциональная составляющая
    const double integralTime = 2.162;  // Интегральная составляющая
    const double derivativeTime = 1.0;         // Дифференциальная составляющая
    const double stepSize = 0.0001;      // Шаг

    // Коэффициенты для вычисления
    const double coeff_0 = proportionalGain * (1.0 + (stepSize != 0 ? derivativeTime / stepSize : 0.0));
    const double coeff_1 = -proportionalGain * (1.0 + 2.0 * derivativeTime / stepSize - stepSize / integralTime);
    const double coeff_2 = (proportionalGain * derivativeTime) / stepSize;

    const int iterations = 10;       // Количество итераций
    const double setPoint = 29.0;     // Целевое значение

    cout << "Начало" << std::endl;
    cout << setw(8) << "Итерация" << setw(20) << "Выход" << setw(20) << "Управление" << endl;

    // Параметры линейной модели
    const double modelA = 0.7;
    const double modelB = 0.2;
    double outputValue = 0.0;
    double controlSignal = 0.0;

    // Лямбда-функция для линейной модели
    auto linearModel = [&](double output, double a, double b, double control) {
        return a * output + b * control; // Формула линейной модели
        };

    // Массив для хранения ошибок
    array<double, 3> errors = { 0.0 };

    // Цикл вычисления выходного значения для линейной модели
    for (int i = 1; i <= iterations; i++) {
        errors[2] = errors[1];
        errors[1] = abs(setPoint - outputValue);
        const double deltaControl = coeff_0 * errors[1] + coeff_1 * errors[2] + coeff_2 * errors[0]; // Вычисление изменения управляющего сигнала
        const double previousControl = controlSignal;
        controlSignal = previousControl + deltaControl;
        outputValue = linearModel(outputValue, modelA, modelB, controlSignal); // Вычисление текущего значения

        // Вывод результатов в столбиках
        cout << setw(8) << i << setw(22) << outputValue << setw(20) << controlSignal << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    runControlLoop();
    return 0;
}
```     
```
Начало
Итерация               Выход          Управление
       1               5626.56             28132.8
       2           1.08435e+06         5.40205e+06
       3           2.10046e+08         1.04644e+09
       4           4.06887e+10         2.02708e+11
       5           7.88191e+12         3.92672e+13
       6           1.52683e+15         7.60655e+15
       7           2.95766e+17         1.47348e+18
       8           5.72936e+19         2.85433e+20
       9           1.10985e+22          5.5292e+22
      10           2.14992e+24         1.07108e+25

![График](график.png)