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
<p align="right">Заседатель Н. С.</p>
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

// Коэффициенты системы
double paramA, paramB, paramC, paramD;
// Параметры системы
double feedbackGain, initialTimeConst, delayTime, timeConstant, targetOutput;
// Параметры регулятора
double regulator1, regulator2, regulator3;

void simulateNonlinearSystem() {
    // Начальные параметры
    const short int startOutput = 2;
    vector<double> outputs = { startOutput, startOutput };  // Выходные значения
    double controlInput = 1.0;  // Управляющий сигнал
    vector<double> deviation = { targetOutput - startOutput, targetOutput - startOutput };  // Ошибка
    vector<double> lastControlInputs = { controlInput, controlInput };  // Предыдущие значения управляющего сигнала

    // Цикл, пока ошибка не станет меньше заданного порога
    while (abs(targetOutput - outputs.back()) > 0.01) {
        deviation.push_back(targetOutput - outputs.back());  // Обновление ошибки
        controlInput = lastControlInputs.back() + regulator1 * deviation.back() + regulator2 * deviation[deviation.size() - 2] + regulator3 * deviation[deviation.size() - 3];
        // Рассчитываем новое значение выхода системы
        outputs.push_back(paramA * outputs.back() - paramB * outputs[outputs.size() - 2] + paramC * controlInput + paramD * sin(lastControlInputs.back()));
        lastControlInputs.push_back(controlInput);  // Сохраняем управляющий сигнал
    }

    // Вывод результатов
    cout << "SteptOutputtErrortControl Inputn";
    for (int i = 0; i < outputs.size(); i++)
        cout << i + 1 << ";" << outputs[i] << ";" << deviation[i] << ";" << lastControlInputs[i] << endl;
}

int main() {
    // Ввод параметров системы
    cout << "Введите коэффициенты системы:n";
    cout << "paramA: "; cin >> paramA;
    cout << "paramB: "; cin >> paramB;
    cout << "paramC: "; cin >> paramC;
    cout << "paramD: "; cin >> paramD;

    // Ввод параметров системы
    cout << "Введите параметры системы:n";
    cout << "feedbackGain: "; cin >> feedbackGain;
    cout << "initialTimeConst: "; cin >> initialTimeConst;
    cout << "delayTime: "; cin >> delayTime;
    cout << "timeConstant: "; cin >> timeConstant;
    cout << "targetOutput (желаемое значение выхода): "; cin >> targetOutput;

    // Расчет параметров регулятора
    regulator1 = feedbackGain * (1 + (delayTime / initialTimeConst));
    regulator2 = -feedbackGain * (1 + 2 * (delayTime / initialTimeConst) - (initialTimeConst / timeConstant));
    regulator3 = feedbackGain * (delayTime / initialTimeConst);

    // Запуск моделирования
    simulateNonlinearSystem();

    return 0;
}
```     
Вывод программы: 
```
Введите коэффициенты системы:
Введите коэффициенты системы:
paramA: 0.8
paramB: 0.4
paramC: 0.4
paramD: 0.7
Введите параметры системы:
feedbackGain: 0.9
initialTimeConst: 1
delayTime: 1.2
timeConstant: 1
targetOutput (желаемое значение выхода): 20
SteptOutputtErrortControl Inputn1;2;18;1
2;2;18;1
3;8.26903;18;17.2
4;13.5123;11.731;20.9873
5;19.2663;6.48768;27.934
6;21.4589;0.73367;28.0428
7;21.8517;-1.45888;30.5761
8;20.718;-1.85169;30.8533
9;20.2027;-0.717983;31.8558
10;20.5752;-0.202669;31.0055
11;19.9114;-0.575224;29.5289
12;19.3249;0.0885996;30.728
13;19.5517;0.675083;31.252
14;20.108;0.448305;30.7772
15;19.978;-0.108018;30.324
16;19.752;0.0219984;31.0851
17;20.1478;0.248028;31.412
18;20.4576;-0.147781;30.6074
19;19.9161;-0.457645;30.2883
20;19.6308;0.0839447;31.2835
21;20.1813;0.369192;31.3389
22;20.3481;-0.181328;30.2731
23;19.7188;-0.348092;30.3742
24;19.6263;0.28124;31.4871
25;20.3608;0.373654;31.2436
26;20.3284;-0.3608;30.0258
27;19.6532;-0.328365;30.5585
28;19.6878;0.346821;31.5648
29;20.4245;0.312167;31.0792
30;20.2087;-0.424513;29.9389
31;19.6121;-0.208737;30.7797
32;19.8063;0.387859;31.5401
33;20.431;0.193672;30.8603
34;20.056;-0.431004;30.0075
35;19.5963;-0.0560459;31.0367
36;19.9921;0.403699;31.4915
![График](unliner.png)

