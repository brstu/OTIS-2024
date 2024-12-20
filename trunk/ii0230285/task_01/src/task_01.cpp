#include <iostream>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    double coeff_a = 1.0,
        coeff_b = 0.5,
        coeff_c = 0.1,
        coeff_d = 0.9,
        input_u = 1.5;

    double initial_temp = 0, current_nonlinear_temp = 0, previous_nonlinear_temp = 0;
    bool first_iteration = true; // используется для определения первой итерации

    cout << "Введите начальную температуру: ";
    cin >> initial_temp;

    current_nonlinear_temp = initial_temp;
    int iterations = 10;

    cout << "Линейная модель:" << endl;
    for (int i = 0; i < iterations; i++) {
        initial_temp = coeff_a * initial_temp + coeff_b * input_u;
        cout << "=" << initial_temp << endl;
    }

    cout << "Нелинейная модель:" << endl;
    for (int i = 0; i < iterations; i++) {
        if (first_iteration) {
            previous_nonlinear_temp = current_nonlinear_temp;
            current_nonlinear_temp = coeff_a * current_nonlinear_temp + coeff_c * input_u + coeff_d * sin(input_u);
            first_iteration = false; // первая итерация завершена
            cout << "=" << current_nonlinear_temp << endl;
        }
        else {
            double new_value = coeff_a * current_nonlinear_temp - coeff_b * pow(previous_nonlinear_temp, 2) + coeff_c * input_u + coeff_d * sin(input_u);
            previous_nonlinear_temp = current_nonlinear_temp; // обновляем предыдущее значение
            current_nonlinear_temp = new_value; // обновляем текущее значение
            cout << "=" << current_nonlinear_temp << endl;
        }
    }

    return 0;
}
