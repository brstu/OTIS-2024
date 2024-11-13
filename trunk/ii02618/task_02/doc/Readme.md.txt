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
<p align="right">Суховило В.С.</p>
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

// System coefficients
double system_coeff_a, system_coeff_b, system_coeff_c, system_coeff_d;
// System parameters
double controller_gain, time_constant_0, time_delay, time_constant, target_output;
// Controller parameters
double controller_param_0, controller_param_1, controller_param_2;

void simulate_nonlinear_system() {
    // Initial parameters
    const short int initial_output_value = 2;
    vector<double> system_output = { initial_output_value, initial_output_value };  // Output values
    double control_signal = 1.0;  // Control signal
    vector<double> error_values = { target_output - initial_output_value, target_output - initial_output_value };  // Error
    vector<double> previous_control_signals = { control_signal, control_signal };  // Previous control signal values

    // Loop until error is smaller than the threshold
    while (abs(target_output - system_output.back()) > 0.01)
    {
        error_values.push_back(target_output - system_output.back());  // Update error
        control_signal = previous_control_signals.back() + controller_param_0 * error_values.back() + controller_param_1 * error_values[error_values.size() - 2] + controller_param_2 * error_values[error_values.size() - 3];
        // Calculate new system output value
        system_output.push_back(system_coeff_a * system_output.back() - system_coeff_b * system_output[system_output.size() - 2] + system_coeff_c * control_signal + system_coeff_d * sin(previous_control_signals.back()));
        previous_control_signals.push_back(control_signal);  // Save control signal
    }

    // Output results
    cout << "Step\tOutput\tError\tControl Signal\n";
    for (int i = 0; i < system_output.size(); i++)
        cout << i + 1 << ";" << system_output[i] << ";" << error_values[i] << ";" << previous_control_signals[i] << endl;
}

int main() {
    // Input system coefficients
    cout << "Enter system coefficients:\n";
    cout << "system_coeff_a: "; cin >> system_coeff_a;
    cout << "system_coeff_b: "; cin >> system_coeff_b;
    cout << "system_coeff_c: "; cin >> system_coeff_c;
    cout << "system_coeff_d: "; cin >> system_coeff_d;

    // Input system parameters
    cout << "Enter system parameters:\n";
    cout << "controller_gain: "; cin >> controller_gain;
    cout << "time_constant_0: "; cin >> time_constant_0;
    cout << "time_delay: "; cin >> time_delay;
    cout << "time_constant: "; cin >> time_constant;
    cout << "target_output (desired output value): "; cin >> target_output;

    // Calculate controller parameters
    controller_param_0 = controller_gain * (1 + (time_delay / time_constant_0));
    controller_param_1 = -controller_gain * (1 + 2 * (time_delay / time_constant_0) - (time_constant_0 / time_constant));
    controller_param_2 = controller_gain * (time_delay / time_constant_0);

    // Run simulation
    simulate_nonlinear_system();

    return 0;
}
```     
Вывод программы: 
```
Enter system coefficients:
system_coeff_a: 0.5
system_coeff_b: 0.3
system_coeff_c: 0.4
system_coeff_d: 1
Enter system parameters:
controller_gain: 1
time_constant_0: 1
time_delay: 1
time_constant: 1
target_output (desired output value): 1
Step    Output  Error   Control Signal
1;2;-1;1
2;2;-1;1
3;1.24147;-1;0
4;0.227559;-0.241471;0.517058
5;0.853616;0.772441;1.54488
6;1.37872;0.146384;0.051297
7;0.393961;-0.378723;-0.226477
8;0.314591;0.606039;1.88943
9;1.65655;0.685409;1.66945
10;1.56566;-0.65655;-0.408431
11;0.072198;-0.565663;0.458752
12;1.12488;0.927802;2.78913
13;0.933229;-0.124883;0.1181
14;0.818659;0.0667706;1.42921
15;1.73274;0.181341;1.53347
16;1.52891;-0.732741;-0.227926
17;0.163107;-0.528906;0.361085
18;0.920148;0.836893;2.35994
19;1.24238;0.0798518;0.316954
20;0.860574;-0.242376;0.509392
21;1.08636;0.139426;1.35285
22;1.52491;-0.0863598;0.6589
23;1.01728;-0.524911;-0.0787758
24;0.312521;-0.0172845;0.850117
25;1.29633;0.687479;1.73473
26;1.44093;-0.296326;-0.250161
27;0.14325;-0.440935;0.1481
28;0.765761;0.85675;2.44714
29;1.28434;0.234239;0.761186
30;1.33453;-0.284342;0.580775
31;1.11649;-0.334534;0.714631
32;1.15977;-0.116489;0.866378
33;1.18504;-0.159774;0.445274
34;0.786595;-0.185039;0.278256
35;0.678613;0.213405;0.91537
36;1.27463;0.321387;0.946294
37;1.23205;-0.274634;-0.0323423
38;0.350983;-0.23205;0.374212
39;0.916101;0.649017;1.86171
40;1.51051;0.0838995;0.499427
41;0.943198;-0.510508;-0.0403703
42;0.449347;0.0568017;1.17815
43;1.52775;0.550653;1.65534
44;1.44763;-0.52775;-0.444662
45;-0.0581713;-0.447634;0.266223
46;0.899747;1.05817;2.75008
47;1.00355;0.100253;0.386613

![График](unliner.png)