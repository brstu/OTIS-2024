#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>  // Для форматирования вывода
using namespace std;

// Коэффициенты системы
double system_a, system_b, system_c, system_d;
// Параметры системы
double gain_factor, t_const_0, t_delay, t_const, target_output;
// Параметры регулятора
double regulator_0, regulator_1, regulator_2;

void run_simulation() {
    const double initial_value = 2.0;  // Начальное значение выхода
    double control_value = 1.0;        // Управляющий сигнал
    vector<double> outputs = { initial_value };  // Вектор выходных значений
    vector<double> errors = { target_output - initial_value };  // Вектор ошибок
    vector<double> controls = { control_value };  // История управляющего сигнала

    // Цикл продолжается, пока ошибка не станет меньше 0.01
    while (fabs(errors.back()) > 0.01) {
        // Вычисление новой ошибки
        errors.push_back(target_output - outputs.back());

        // Вычисление нового управляющего сигнала
        control_value = controls.back()
            + regulator_0 * errors.back()
            + regulator_1 * (errors.size() > 1 ? errors[errors.size() - 2] : 0.0)
            + regulator_2 * (errors.size() > 2 ? errors[errors.size() - 3] : 0.0);

        // Обновление выходного значения системы
        double next_output = system_a * outputs.back()
            - system_b * (outputs.size() > 1 ? outputs[outputs.size() - 2] : 0.0)
            + system_c * control_value
            + system_d * sin(controls.back());

        outputs.push_back(next_output);  // Добавляем новое значение в вектор выходов
        controls.push_back(control_value);  // Сохраняем управляющий сигнал
    }

    // Вывод результатов
    cout << fixed << setprecision(4);  // Форматирование вывода с 4 знаками после запятой
    cout << "Step\tOutput\tError\tControl Signal\n";
    for (size_t i = 0; i < outputs.size(); ++i) {
        cout << i + 1 << "\t"
            << outputs[i] << "\t"
            << errors[i] << "\t"
            << controls[i] << endl;
    }
}

int main() {
    // Ввод параметров системы
    setlocale(LC_ALL, "RU");
    cout << "Введите коэффициенты системы:\n";
    cout << "system_a: "; cin >> system_a;
    cout << "system_b: "; cin >> system_b;
    cout << "system_c: "; cin >> system_c;
    cout << "system_d: "; cin >> system_d;

    cout << "\nВведите параметры системы:\n";
    cout << "gain_factor: "; cin >> gain_factor;
    cout << "t_const_0: "; cin >> t_const_0;
    cout << "t_delay: "; cin >> t_delay;
    cout << "t_const: "; cin >> t_const;
    cout << "target_output (желаемое значение выхода): "; cin >> target_output;

    // Расчет параметров регулятора
    regulator_0 = gain_factor * (1 + (t_delay / t_const_0));
    regulator_1 = -gain_factor * (1 + 2 * (t_delay / t_const_0) - (t_const_0 / t_const));
    regulator_2 = gain_factor * (t_delay / t_const_0);

    // Запуск симуляции системы
    run_simulation();

    return 0;
}
