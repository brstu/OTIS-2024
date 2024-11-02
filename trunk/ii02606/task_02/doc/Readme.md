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
<p align="right">Группы ИИ-26</p>
<p align="right">Карпович К. А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №2 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.

# Задание #
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.
---
# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <cmath>
#include <array>
#include <iomanip> 

using namespace std;

void executeControlLoop() {
    const double gainFactor = 0.097;     // пропорциональная составляющая
    const double integrationTime = 2.162;  // интегральная составляющая
    const double diffTime = 1.0;         // дифференциальная составляющая
    const double timeStep = 0.0001;      // шаг

    const double coeff_0 = gainFactor * (1.0 + (timeStep != 0 ? diffTime / timeStep : 0.0));
    const double coeff_1 = -gainFactor * (1.0 + 2.0 * diffTime / timeStep - timeStep / integrationTime);
    const double coeff_2 = (gainFactor * diffTime) / timeStep;

    const int numIterations = 10;       // количество итераций
    const double targetValue = 29.0;     

    cout << "START" << std::endl;
    cout << setw(8) << "Iteration" << setw(20) << "Output" << setw(20) << "Control" << endl;

    const double modelFactorA = 0.7;
    const double modelFactorB = 0.2;
    double outputVal = 0.0;
    double controlVar = 0.0;

    // функция вычисления для линейной модели
    auto computeLinearModel = [&](double output, double factorA, double factorB, double control) {
        return factorA * output + factorB * control; // формула линейной модели
        };

    // цикл вычисления outputVal для линейной модели
    array<double, 3> errorArray = { 0.0 }; // массив разности желаемого значения и текущего значения
    for (int i = 1; i <= numIterations; i++) {
        errorArray[2] = errorArray[1];
        errorArray[1] = abs(targetValue - outputVal);
        const double deltaControl = coeff_0 * errorArray[1] + coeff_1 * errorArray[2] + coeff_2 * errorArray[0]; // вычисление изменения управляющего сигнала
        const double prevControl = controlVar;
        controlVar = prevControl + deltaControl;
        outputVal = computeLinearModel(outputVal, modelFactorA, modelFactorB, controlVar); // вычисление текущего значения

        // Вывод результатов в столбиках
        cout << setw(8) << i << setw(22) << outputVal << setw(20) << controlVar << endl;
    }
}

int main() {
    executeControlLoop();
    return 0;
}
```     
```
START
Iteration              Output             Control
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

![График](unliner.png)