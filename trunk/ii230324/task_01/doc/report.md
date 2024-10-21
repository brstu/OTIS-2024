<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Черноиван А.Н.</p>
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

using namespace std;

// Константы
const double a = 0.5;
const double b = 0.001;
const double c = 0.3;
const double d = 0.5;

// Функция для линейной модели
void linearModel(double u, int steps, double y) {
    for (int i = 1; i <= steps; ++i) {
        cout << "Time: " << i << ", Linear Output: " << y << endl;
        y = a * y + b * u; // Обновление значения
    }
    cout << "---------------------\n";
}

// Функция для нелинейной модели
void nonlinearModel(double u, int steps, double y, double y1) {
    for (int i = 1; i <= steps; ++i) {
        cout << "Time: " << i << ", Nonlinear Output: " << y << endl;
        double newY = a * y - b * y1 * y1 + c * u + d * sin(u); // Обновление значения
        y1 = y; // Сохранение предыдущего значения
        y = newY; // Обновление текущего значения
    }
}

int main() {
    double u;      // входное тепло
    int steps=30;     // количество шагов
    double y;      // начальное значение для линейной модели
    double y1;     // начальное значение для нелинейной модели

    // Ввод данных с клавиатуры
    cout << "Введите входное тепло (u): ";
    cin >> u;
    cout << "Введите начальное значение для линейной модели (y): ";
    cin >> y;
    cout << "Введите начальное значение для нелинейной модели (y1): ";
    cin >> y1;

    cout << "Линейная модель: \n";
    linearModel(u, steps, y);

    cout << "Нелинейная модель: \n";
    nonlinearModel(u, steps, y, y1);

    return 0;
}
```

Результат выполнения программы:

```
Введите входное тепло (u): 10
Введите начальное значение для линейной модели (y): 25
Введите начальное значение для нелинейной модели (y1): 30
Линейная модель: 
Time: 1, Linear Output: 25
Time: 2, Linear Output: 12.51
Time: 3, Linear Output: 6.265
Time: 4, Linear Output: 3.1425
Time: 5, Linear Output: 1.58125
Time: 6, Linear Output: 0.800625
Time: 7, Linear Output: 0.410312
Time: 8, Linear Output: 0.215156
Time: 9, Linear Output: 0.117578
Time: 10, Linear Output: 0.0687891
Time: 11, Linear Output: 0.0443945
Time: 12, Linear Output: 0.0321973
Time: 13, Linear Output: 0.0260986
Time: 14, Linear Output: 0.0230493
Time: 15, Linear Output: 0.0215247
Time: 16, Linear Output: 0.0207623
Time: 17, Linear Output: 0.0203812
Time: 18, Linear Output: 0.0201906
Time: 19, Linear Output: 0.0200953
Time: 20, Linear Output: 0.0200476
Time: 21, Linear Output: 0.0200238
Time: 22, Linear Output: 0.0200119
Time: 23, Linear Output: 0.020006
Time: 24, Linear Output: 0.020003
Time: 25, Linear Output: 0.0200015
Time: 26, Linear Output: 0.0200007
Time: 27, Linear Output: 0.0200004
Time: 28, Linear Output: 0.0200002
Time: 29, Linear Output: 0.0200001
Time: 30, Linear Output: 0.02
---------------------
Нелинейная модель: 
Time: 1, Nonlinear Output: 25
Time: 2, Nonlinear Output: 14.328
Time: 3, Nonlinear Output: 9.26698
Time: 4, Nonlinear Output: 7.15619
Time: 5, Nonlinear Output: 6.22021
Time: 6, Nonlinear Output: 5.78688
Time: 7, Nonlinear Output: 5.58274
Time: 8, Nonlinear Output: 5.48587
Time: 9, Nonlinear Output: 5.43976
Time: 10, Nonlinear Output: 5.41777
Time: 11, Nonlinear Output: 5.40729
Time: 12, Nonlinear Output: 5.40228
Time: 13, Nonlinear Output: 5.39989
Time: 14, Nonlinear Output: 5.39875
Time: 15, Nonlinear Output: 5.39821
Time: 16, Nonlinear Output: 5.39795
Time: 17, Nonlinear Output: 5.39782
Time: 18, Nonlinear Output: 5.39776
Time: 19, Nonlinear Output: 5.39773
Time: 20, Nonlinear Output: 5.39772
Time: 21, Nonlinear Output: 5.39771
Time: 22, Nonlinear Output: 5.39771
Time: 23, Nonlinear Output: 5.39771
Time: 24, Nonlinear Output: 5.39771
Time: 25, Nonlinear Output: 5.39771
Time: 26, Nonlinear Output: 5.39771
Time: 27, Nonlinear Output: 5.39771
Time: 28, Nonlinear Output: 5.39771
Time: 29, Nonlinear Output: 5.39771
Time: 30, Nonlinear Output: 5.39771
```