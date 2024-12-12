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
<p align="right">Группы ИИ-25</p>
<p align="right">Кулик Я.А.</p>
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
# Код программы: #
```C++
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double coeff_a, coeff_b, coeff_c, coeff_d;
double gain, time_const_0, time_delay, time_const, desired_output;
double reg_0, reg_1, reg_2;

void updateCoefficients() {
    cout << "Введите коэффициенты системы:\n";
    cout << "coeff_a: "; cin >> coeff_a;
    cout << "coeff_b: "; cin >> coeff_b;
    cout << "coeff_c: "; cin >> coeff_c;
    cout << "coeff_d: "; cin >> coeff_d;
}

void updateSystemParameters() {
    cout << "Введите параметры системы:\n";
    cout << "gain: "; cin >> gain;
    cout << "time_const_0: "; cin >> time_const_0;
    cout << "time_delay: "; cin >> time_delay;
    cout << "time_const: "; cin >> time_const;
    cout << "desired_output (желаемое значение выхода): "; cin >> desired_output;
}

void calculateRegulatorParameters() {
    reg_0 = gain * (1 + (time_delay / time_const_0));
    reg_1 = -gain * (1 + 2 * (time_delay / time_const_0) - (time_const_0 / time_const));
    reg_2 = gain * (time_delay / time_const_0);
}

void simulateSystem() {
    const short int initial_output = 2;
    vector<double> output = { initial_output, initial_output };
    vector<double> error = { desired_output - initial_output, desired_output - initial_output };
    vector<double> control_signal_history = { 1.0, 1.0 };
    double control_signal = 1.0;

    while (abs(desired_output - output.back()) > 0.01) {
        double current_output = output.back();
        error.push_back(desired_output - current_output);

        control_signal = control_signal_history.back() +
            reg_0 * error.back() +
            reg_1 * error[error.size() - 2] +
            reg_2 * error[error.size() - 3];

        control_signal_history.push_back(control_signal);

        double new_output = coeff_a * current_output -
            coeff_b * output[output.size() - 2] +
            coeff_c * control_signal +
            coeff_d * sin(control_signal_history[control_signal_history.size() - 2]);

        output.push_back(new_output);
    }

    cout << "Step\tOutput\tError\tControl Signal\n";
    for (size_t i = 0; i < output.size(); ++i) {
        cout << i + 1 << ";" << output[i] << ";" << error[i] << ";" << control_signal_history[i] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    updateCoefficients();
    updateSystemParameters();
    calculateRegulatorParameters();
    simulateSystem();

    return 0;
}

```     
Вывод программы: 
```
Введите коэффициенты системы:
coeff_a: 0.6
coeff_b: 0.4
coeff_c: 0.2
coeff_d: 0.4
Введите параметры системы:
gain: 0.8
time_const_0: 1
time_delay: 1.3
time_const: 1
desired_output (желаемое значение выхода): 10
Step    Output  Error   Control Signal
1;2;8;1
2;2;8;1
3;2.21659;8;7.4
4;3.56973;7.78341;13.4015
5;5.02449;6.43027;17.3637
6;5.43592;4.97551;21.2384
7;6.72016;4.56408;25.9747
8;7.69429;3.27984;27.6909
9;8.12047;2.30571;29.858
10;7.78089;1.87953;31.9315
11;8.51817;2.21911;34.5031
12;8.93402;1.48183;34.5687
13;9.09984;1.06598;35.7557
14;8.86092;0.900164;36.7359
15;8.96182;1.13908;38.0681
16;9.68603;1.03818;38.5452
17;10.156;0.313965;38.1481
18;10.0504;-0.156002;38.2878
19;9.95914;-0.0503782;38.8461
20;10.0927;0.0408643;38.8638
21;10.1506;-0.092699;38.5559
22;10.0584;-0.150602;38.5141
23;9.99056;-0.0583771;38.6235

