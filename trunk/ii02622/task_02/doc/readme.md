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
<p align="right">Цурукова В.А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.

# Задание #
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.


<hr>

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <locale>

// Константы модели
constexpr double kAlpha = 0.9;
constexpr double kBeta = 0.3;
constexpr double kGamma = 0.4;
constexpr double kDelta = 0.1;

// Параметры системы управления
constexpr double kCoeffK = 0.9;
constexpr double kTime0 = 0.5;
constexpr double kTimeC = 1.0;
constexpr double kTimeD = 0.5;
constexpr double kTargetOutput = 20.0;

// Вычисленные параметры регулятора
constexpr double kParam1 = kCoeffK * (1.0 + (kTimeD / kTime0));
constexpr double kParam2 = -kCoeffK * (1.0 + 2.0 * (kTimeD / kTime0) - (kTime0 / kTimeC));
constexpr double kParam3 = kCoeffK * (kTimeD / kTime0);

void SimulateControlSystem() {
    // Начальные условия
    constexpr int kInitialValue = 2;
    std::vector<double> systemOutputs = {kInitialValue, kInitialValue};
    std::vector<double> errors = {kTargetOutput - kInitialValue, kTargetOutput - kInitialValue};
    double controlSignal = 1.0;
    std::vector<double> controlSignals = {controlSignal, controlSignal};

    // Цикл моделирования
    while (std::fabs(kTargetOutput - systemOutputs.back()) > 0.01) {
        double currentError = kTargetOutput - systemOutputs.back();
        errors.push_back(currentError);

        // Проверяем длину ошибок, добавляем нули при необходимости
        while (errors.size() < 3) {
            errors.insert(errors.begin(), 0.0);
        }

        // Рассчитываем новый контрольный сигнал
        controlSignal += kParam1 * errors.back() + kParam2 * errors[errors.size() - 2] + kParam3 * errors[errors.size() - 3];
        controlSignals.push_back(controlSignal);

        // Вычисляем следующий выход системы
        double nextOutput = kAlpha * systemOutputs.back() - kBeta * systemOutputs[systemOutputs.size() - 2] + kGamma * controlSignal + kDelta * std::sin(controlSignal);
        systemOutputs.push_back(nextOutput);
    }

    // Вывод данных
    std::cout << std::setw(12) << "Step"
              << std::setw(12) << "Output"
              << std::setw(12) << "Error"
              << std::setw(12) << "Control" << std::endl;

    for (size_t i = 0; i < systemOutputs.size(); ++i) {
        double error = (i < errors.size()) ? errors[i] : 0.0;
        double control = (i < controlSignals.size()) ? controlSignals[i] : 0.0;
        std::cout << std::setw(12) << i + 1
                  << std::setw(12) << systemOutputs[i]
                  << std::setw(12) << error
                  << std::setw(12) << control << std::endl;
    }
}

int main() {
    // Установка локали для поддержки русского текста
    std::locale::global(std::locale(""));

    SimulateControlSystem();
    return 0;
}
'''
Вывод:
'''
 Step      Output       Error     Control
           1    2.000000   18.000000    1.000000
           2    2.000000   18.000000    1.000000
           3    4.871910   18.000000    9.100000
           4    8.545890   15.128090   12.030562
           5   12.231852   11.454110   14.809757
           6   15.019241    7.768148   16.635957
           7   17.179856    4.980759   18.431690
           8   18.715995    2.820144   19.292574
           9   19.664703    1.284005   19.741143
          10   20.171992    0.335297   19.993796
          11   20.383983   -0.171992   20.085396
          12   20.421540   -0.383983   20.082976
          13   20.370146   -0.421540   20.033373
          14   20.284695   -0.370146   19.969991
          15   20.196880   -0.284695   19.910983
          16   20.122316   -0.196880   19.864031
          17   20.066376   -0.122316   19.830616
          18   20.028603   -0.066376   19.809159
          19   20.005793   -0.028603   19.796934
'''
![График](./otis.png)