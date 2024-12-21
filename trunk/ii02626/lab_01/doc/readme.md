<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Яшков П.А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
3. Выполнить рецензирование ([review](https://linearb.io/blog/code-review-on-github), [checklist](https://linearb.io/blog/code-review-checklist)) запросов других студентов (минимум 2-е рецензии).
4. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2023/edit/main/readme.md?#L17-L17).

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC}$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$ (2)
$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

## Код программы
```C++
#include <iostream>
#include <math.h>


const double a = 0.52;
const double b = 0.0015;
const double c = 0.32;
const double d = 0.51;

using namespace std;

/*
 * non-linear model
 */
void linear(double u, double y0, int t) {
    cout << "Linear model: " << endl;
    for (int i = 0; i < t; i++) {
        cout << "\ty" << i + 1 << " = " << y0 << endl;
        y0 = a * y0 + b * u;
    }
}

/*
 * non-linear model
 */
void nonLinear(double u, double y0, double y1, int t) {
    cout << "Non-linear model: " << endl;
    for (int i = 0; i < t; i++) {
        cout << "\ty" << i + 1 << " = " << y0 << endl;
        double temp = a * y0 - b * pow(y1, 2) + c * u + d * sin(u);
        y1 = y0;
        y0 = temp;
    }
}

int main() {

    double u, y0;

    cout << "u0 > "; 
    cin >> u;
    cout << "y0 > "; 
    cin >> y0;

    linear(u, y0, 10);
    nonLinear(u, y0, y0 + 0.015, 10);

    return 0;
}
```

## Результат работы программы
```
u0 > 10   
y0 > 25
Linear model:
        y1 = 25
        y2 = 13.015
        y3 = 6.7828
        y4 = 3.54206
        y5 = 1.85687
        y6 = 0.980572
        y7 = 0.524897
        y8 = 0.287947
        y9 = 0.164732
        y10 = 0.100661
Non-linear model:
        y1 = 25
        y2 = 14.9839
        y3 = 9.77669
        y4 = 7.66965
        y5 = 6.76739
        y6 = 6.35336
        y7 = 6.1576
        y8 = 6.06395
        y9 = 6.01893
        y10 = 5.99724
```