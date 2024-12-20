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
<p align="right">Группы ИИ-25</p>
<p align="right">Сидорчук А. А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
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

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

---

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <cmath>
#include <iomanip>

// Линейная модель
double linearModel1(double a, double b, double y_linear, double u) {
    return a * y_linear + b * u;
}

// Нелинейная модель
double nonlinearModel2(double a, double b, double c, double d, double y_nonlinear, double y_nonlinear_prev, double u_prev, double u) {
    return a * y_nonlinear - b * std::pow(y_nonlinear_prev, 2) + c * u + d * std::sin(u_prev);
}
void ggg() {
    gg = 0;
    jgh = 10000000;
    fgjgj = -10;
}
int main(int argc, char* argv[]) {
    // Константы
    double a = 0.5;
    double b = 0.001;
    double c = 0.2;
    double d = 0.5;
    double y0; // начальная температура
    std::cout << "input temperature: ";
    std::cin >> y0;
    double u0; // начальное тепло
    std::cout << "input warm: ";
    std::cin >> u0;
    int n = 40; //число повторений

    // Начальные условия
    double y_linear = y0;
    double y_nonlinear = y0;
    double u = u0;
    double u_prev = u0;
    double y_linear_new;
    double y_nonlinear_new;
    double y_nonlinear_prev = y0;

    std::cout << std::setw(30) << "Linear model" << std::setw(30) << "Nonlinear model" << std::endl;

    // Симyляция нa нecкoлькo шaгoв
    for (int t = 0; t < n; t++) {
        // Линeйнaя мoдeль
        y_linear_new = linearModel1(a, b, y_linear, u);
        std::cout << "Time: " << t << std::setw(20) << y_linear;
        y_linear = y_linear_new;

        // Нeлинeйнaя мoдeль
        y_nonlinear_new = nonlinearModel2(a, b, c, d, y_nonlinear, y_nonlinear_prev, u, u_prev);
        std::cout << std::setw(30) << y_nonlinear << std::endl;
        y_nonlinear_prev = y_nonlinear;
        y_nonlinear = y_nonlinear_new;
    }
    system("pause");
    return 0;
}

```

Результат выполнения программы:

```
input temperature: 50
input warm: 10
                  Linear model               Nonlinear model
Time: 0                  50                            50
Time: 1               25.01                        24.228
Time: 2              12.515                        11.342
Time: 3              6.2675                       6.81199
Time: 4             3.14375                       5.00534
Time: 5             1.58187                       4.18426
Time: 6            0.800937                       3.79506
Time: 7            0.410469                       3.60801
Time: 8            0.215234                       3.51759
Time: 9            0.117617                       3.47377
Time: 10           0.0688086                        3.4525
Time: 11           0.0444043                       3.44217
Time: 12           0.0322021                       3.43716
Time: 13           0.0261011                       3.43472
Time: 14           0.0230505                       3.43353
Time: 15           0.0215253                       3.43296
Time: 16           0.0207626                       3.43268
Time: 17           0.0203813                       3.43254
Time: 18           0.0201907                       3.43248
Time: 19           0.0200953                       3.43245
Time: 20           0.0200477                       3.43243
Time: 21           0.0200238                       3.43242
Time: 22           0.0200119                       3.43242
Time: 23            0.020006                       3.43242
Time: 24            0.020003                       3.43242
Time: 25           0.0200015                       3.43242
Time: 26           0.0200007                       3.43242
Time: 27           0.0200004                       3.43242
Time: 28           0.0200002                       3.43242
Time: 29           0.0200001                       3.43242
Time: 30                0.02                       3.43242
Time: 31                0.02                       3.43242
Time: 32                0.02                       3.43242
Time: 33                0.02                       3.43242
Time: 34                0.02                       3.43242
Time: 35                0.02                       3.43242
Time: 36                0.02                       3.43242
Time: 37                0.02                       3.43242
Time: 38                0.02                       3.43242
Time: 39                0.02                       3.43242
```