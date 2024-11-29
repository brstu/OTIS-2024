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
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Сугак В.А.</p>
<p align="right">Проверил:</p>
<p align="right">Ситковец Я.С.</p>
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

Task is to write program (**Julia**), which simulates this object temperature.

<hr>

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

double const a = 0.9;
double const b = 0.1;
double const c = 0.05;
double const d = 0.01;
double const u = 10.0;

std::vector<double> LinearMod(int t, double yt, double ut) {
    std::vector<double> linearResult(t);
    linearResult[0] = yt;
    for (int i = 1; i < t; i++) {
        linearResult[i] = a * linearResult[i - 1] + b * ut;
    }
    return linearResult;
}

std::vector<double> NonlinearMod(int t, double yt, double yt_1, double ut_1) {
    std::vector<double> nonlinearResult(t);
    nonlinearResult[0] = yt;
    if (t > 1) {
        nonlinearResult[1] = a * nonlinearResult[0] + c * ut_1 + d * sin(ut_1);
    }

    for (int i = 2; i < t; i++) {
        nonlinearResult[i] = a * nonlinearResult[i - 1] - b * pow(nonlinearResult[i - 2], 2) + c * ut_1 + d * sin(ut_1);
    }

    return nonlinearResult;
}

std::vector<double> PIDRegulator(int t, const std::vector<double>& setpoint, const std::vector<double>& state) {
    std::vector<double> output(t);
    double error, integralError = 0.0, previousError = 0.0;
    double Kp = 1.0, Ki = 0.1, Kd = 0.5;

    for (int i = 0; i < t; i++) {
        error = setpoint[i] - state[i];
        integralError += error;
        output[i] = Kp * error + Ki * integralError + Kd * (error - previousError);
        previousError = error;
    }

    return output;
}

int main() {
    setlocale(LC_ALL, "rus");

    double startTemperature;
    int times;
    std::vector<std::vector<double>> results;
    std::vector<double> setpoints;

    std::cout << "Введите стартовую температуру: ";
    std::cin >> startTemperature;
    std::cout << "Введите количество итераций: ";
    std::cin >> times;

    times += 1;

    for (int i = 0; i < times; i++) {
        setpoints.push_back(20.0 + 10.0 * sin(0.1 * i));
    }

    results.push_back(LinearMod(times, startTemperature, u));
    results.push_back(NonlinearMod(times, startTemperature, startTemperature, u));

    std::vector<double> pidOutput = PIDRegulator(times, setpoints, results[1]);

    std::cout << std::right << std::setw(10) << "Итерация   "
        << std::setw(15) << "Зад.температура"
        << std::setw(10) << "Линейная"
        << std::setw(13) << "Нелинейная"
        << std::setw(15) << "ПИД-регулятор" << std::endl;

    for (int i = 0; i < times; i++) {
        std::cout << std::right << std::setw(10) << i
            << std::setw(15) << setpoints[i]
            << std::setw(10) << results[0][i]
            << std::setw(13) << results[1][i]
            << std::setw(15) << pidOutput[i] << std::endl;
    }

    return 0;
}
'''
'''
Введите стартовую температуру: 5
Введите количество итераций: 10
Итерация   Зад.температура  Линейная   Нелинейная  ПИД-регулятор
         0             20         5            5             24
         1        20.9983       5.5      4.99456         19.606
         2        21.9867      5.95      2.48966        26.2937
         3        22.9552     6.355     0.240694        31.6448
         4        23.8942    6.7195    0.0913422        34.0488
         5        24.7943   7.04755     0.570974        36.5576
         6        25.6464    7.3428       1.0076        39.4346
         7        26.4422   7.60852       1.3688         42.386
         8        27.1736   7.84766      1.62495        45.4364
         9        27.8333    8.0629      1.76966        48.5777
        10        28.4147   8.25661       1.8232        51.7712

'''