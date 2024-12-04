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
<p align="right">Андреюк М. О.</p>
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
double linearModel(double coeff_a, double coeff_b, double temp_linear, double heat_input) {
    return coeff_a * temp_linear + coeff_b * heat_input;
}

// Нелинейная модель
double nonlinearModel(double coeff_a, double coeff_b, double coeff_c, double coeff_d,
    double temp_nonlinear, double prev_temp_nonlinear,
    double prev_heat_input, double current_heat_input) {
    return coeff_a * temp_nonlinear - coeff_b * std::pow(prev_temp_nonlinear, 2)
        + coeff_c * current_heat_input + coeff_d * std::sin(prev_heat_input);
}

// Функция для ввода начальных данных
void inputInitialConditions(double& initial_temp, double& initial_heat) {
    std::cout << "Input initial temperature: ";
    std::cin >> initial_temp;
    std::cout << "Input initial heat input: ";
    std::cin >> initial_heat;
}

// Функция для выполнения симуляции
void runSimulation(int steps, double coeff_a, double coeff_b, double coeff_c, double coeff_d,
    double initial_temp, double initial_heat) {
    // Начальные условия
    double temp_linear = initial_temp;
    double temp_nonlinear = initial_temp;
    double current_heat_input = initial_heat;
    double prev_heat_input = initial_heat;
    double new_temp_linear;
    double new_temp_nonlinear;
    double prev_temp_nonlinear = initial_temp;

    std::cout << std::setw(30) << "Linear Model" << std::setw(30) << "Nonlinear Model" << std::endl;

    // Симуляция на несколько шагов
    for (int time_step = 0; time_step < steps; time_step++) {
        // Линейная модель
        new_temp_linear = linearModel(coeff_a, coeff_b, temp_linear, current_heat_input);
        std::cout << "Time Step: " << time_step << std::setw(20) << temp_linear;
        temp_linear = new_temp_linear;

        // Нелинейная модель
        new_temp_nonlinear = nonlinearModel(coeff_a, coeff_b, coeff_c, coeff_d,
            temp_nonlinear, prev_temp_nonlinear,
            prev_heat_input, current_heat_input);
        std::cout << std::setw(30) << temp_nonlinear << std::endl;
        prev_temp_nonlinear = temp_nonlinear;
        temp_nonlinear = new_temp_nonlinear;
    }
}

// Основная функция
int main(int argc, char* argv[]) {
    // Константы
    const double coeff_a = 0.5;
    const double coeff_b = 0.001;
    const double coeff_c = 0.2;
    const double coeff_d = 0.5;
    const int steps = 40; // число повторений

    double initial_temp; // начальная температура
    double initial_heat; // начальное тепло

    // Ввод данных
    inputInitialConditions(initial_temp, initial_heat);

    // Запуск симуляции
    runSimulation(steps, coeff_a, coeff_b, coeff_c, coeff_d, initial_temp, initial_heat);

    system("pause");
    return 0;
}
```

Результат выполнения программы:

```
Input initial temperature: 30
Input initial heat input: 1
                  Linear Model               Nonlinear Model
Time Step: 0                  30                            30
Time Step: 1              15.001                       14.7207
Time Step: 2              7.5015                        7.0811
Time Step: 3             3.75175                       3.94459
Time Step: 4             1.87687                       2.54289
Time Step: 5            0.939437                       1.87662
Time Step: 6            0.470719                       1.55258
Time Step: 7            0.236359                        1.3935
Time Step: 8             0.11918                       1.31508
Time Step: 9           0.0605898                       1.27633
Time Step: 10           0.0312949                       1.25717
Time Step: 11           0.0166475                       1.24769
Time Step: 12          0.00932373                         1.243
Time Step: 13          0.00566187                       1.24068
Time Step: 14          0.00383093                       1.23953
Time Step: 15          0.00291547                       1.23896
Time Step: 16          0.00245773                       1.23868
Time Step: 17          0.00222887                       1.23854
Time Step: 18          0.00211443                       1.23847
Time Step: 19          0.00205722                       1.23844
Time Step: 20          0.00202861                       1.23842
Time Step: 21           0.0020143                       1.23841
Time Step: 22          0.00200715                       1.23841
Time Step: 23          0.00200358                       1.23841
Time Step: 24          0.00200179                        1.2384
Time Step: 25          0.00200089                        1.2384
Time Step: 26          0.00200045                        1.2384
Time Step: 27          0.00200022                        1.2384
Time Step: 28          0.00200011                        1.2384
Time Step: 29          0.00200006                        1.2384
Time Step: 30          0.00200003                        1.2384
Time Step: 31          0.00200001                        1.2384
Time Step: 32          0.00200001                        1.2384
Time Step: 33               0.002                        1.2384
Time Step: 34               0.002                        1.2384
Time Step: 35               0.002                        1.2384
Time Step: 36               0.002                        1.2384
Time Step: 37               0.002                        1.2384
Time Step: 38               0.002                        1.2384
Time Step: 39               0.002                        1.2384
```