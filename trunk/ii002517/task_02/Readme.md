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
<p align="right">Нешумаев А.К.</p>
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
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

double regulator1, regulator2, regulator3;

double paramA, paramB, paramC, paramD;

double backG, Time, delTime, time_const, target;

void simulation() {
    const short int start = 2;
    vector<double> outputs = { start, start };
    double controlInput = 1.0;
    vector<double> deviation = { target - start, target - start };
    vector<double> lastControlInputs = { controlInput, controlInput };

    while (abs(target - outputs.back()) > 0.01) {
        deviation.push_back(target - outputs.back());
        controlInput = lastControlInputs.back() + regulator1 * deviation.back() + regulator2 * deviation[deviation.size() - 2] + regulator3 * deviation[deviation.size() - 3];
        outputs.push_back(paramA * outputs.back() - paramB * outputs[outputs.size() - 2] + paramC * controlInput + paramD * sin(lastControlInputs.back()));
        lastControlInputs.push_back(controlInput);
    }

    cout << "SteptOutputtErrortControl Inputn";
    for (int i = 0; i < outputs.size(); i++)
        cout << i + 1 << ";" << outputs[i] << ";" << deviation[i] << ";" << lastControlInputs[i] << endl;
}



int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите коэффициенты системы: (paramA, paramB, paramC, paramD)" << endl;
    cin >> paramA >> paramB >> paramC >> paramD;

    cout << "Введите параметры системы:\n";
    cout << "feedbackGain: "; cin >> backG;
    cout << "initialTimeConst: "; cin >> Time;
    cout << "delayTime: "; cin >> delTime;
    cout << "timeConstant: "; cin >> time_const;
    cout << "targetOutput (желаемое значение выхода): "; cin >> target;

    regulator1 = backG * (1 + (delTime / Time));
    regulator2 = -backG * (1 + 2 * (delTime / Time) - (Time / time_const));
    regulator3 = backG * (delTime / Time);

    simulation();
}
```     
Вывод программы: 
```

Введите коэффициенты системы: (paramA, paramB, paramC, paramD)
0.6
0.4
0.2
0.4
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