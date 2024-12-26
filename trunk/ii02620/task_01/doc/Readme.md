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
<p align="right">Хитренко А. А.</p>
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
#include <iomanip>

using namespace std;


const double a = 0.5;
const double b = 0.1;
const double c = 0.05;
const double d = 0.01;

const int n = 10; // количество шагов моделирования


void simulate_linear_system(const vector<double>& u, vector<double>& y) {
    y[0] = 0.0; 
    for (int i = 0; i < n; ++i) {
        y[i + 1] = a * y[i] + b * u[i];
    }
}

// функция моделирования нелинейной системы
void simulate_nonlinear_system(const vector<double>& u, vector<double>& y) {
    y[0] = 0.0; 
    y[1] = 0.1; // второе начальное условие для нелинейной системы
    for (int i = 1; i < n; ++i) {
        y[i + 1] = a * y[i] - b * y[i] * y[i] + c * y[i] + d * sin(u[i]);
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<double> y_linear(n + 1, 0.0); 
    vector<double> y_nonlinear(n + 1, 0.0);
    vector<double> u(n, 1.0); 

    simulate_linear_system(u, y_linear);

    simulate_nonlinear_system(u, y_nonlinear);

    // вывод результатов в табличном формате
    cout << "Результаты моделирования:\n\n";
    cout << setw(10) << "Шаг" << setw(15) << "Линейная система" << setw(15) << "Нелинейная система" << endl;
    cout << setprecision(4);
    for (int i = 0; i <= n; ++i) {
        cout << setw(10) << i << setw(15) << y_linear[i] << setw(15) << y_nonlinear[i] << endl;
    }

    return 0;
}

```     
Результаты моделирования:

       ШагЛинейная системаНелинейная система
         0              0              0
         1            0.1            0.1
         2           0.15        0.06241
         3          0.175        0.04235
         4         0.1875        0.03153
         5         0.1938        0.02566
         6         0.1969        0.02246
         7         0.1984        0.02072
         8         0.1992        0.01977
         9         0.1996        0.01925
        10         0.1998        0.01896