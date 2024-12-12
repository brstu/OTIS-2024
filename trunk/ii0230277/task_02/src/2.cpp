#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double a, b, c, d;
double gain, time_const_0, time_delay, time_const, desired_output;
double reg0, reg1, reg2;

void nonlinear_system() {
    const short int initial_output = 2;
    double output[1000] = { initial_output, initial_output };
    double control_signal = 1.0;
    double error[1000] = { desired_output - initial_output, desired_output - initial_output };
    double previous_control_signal[1000] = { control_signal, control_signal };

    int i = 1;

    while (abs(desired_output - output[i]) > 0.01 && i < 1000) {
        error[i + 1] = desired_output - output[i];
        control_signal = previous_control_signal[i] + reg0 * error[i + 1] + reg1 * error[i] + reg2 * error[i - 1];

        output[i + 1] = a * output[i] - b * output[i - 1] + c * control_signal + d * sin(previous_control_signal[i]);
        previous_control_signal[i + 1] = control_signal;
        i++;
    }

    cout << setw(5) << setfill(' ') << "Шаг" << setw(10) << setfill(' ') << "Выход" << setw(12) << setfill(' ') << "Ошибка" << setw(20) << setfill(' ') << "Контрольный сигнал" << endl;
    for (int j = 0; j <= i; j++) {
        cout << setw(5) << setfill(' ') << j + 1;
        cout << setw(12) << setfill(' ') << output[j];
        cout << setw(15) << setfill(' ') << error[j];
        cout << setw(20) << setfill(' ') << previous_control_signal[j] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "Введите коэффициенты системы: " << endl;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "c: ";
    cin >> c;
    cout << "d: ";
    cin >> d;

    cout << "Введите параметры системы:\n";
    cout << "Прирост: ";
    cin >> gain;
    cout << "Временная константа: ";
    cin >> time_const_0;
    cout << "Задержка времени: ";
    cin >> time_delay;
    cout << "Вторая временная константа: ";
    cin >> time_const;
    cout << "Желаемое значение выхода: ";
    cin >> desired_output;

    reg0 = gain * (1 + (time_delay / time_const_0));
    reg1 = -gain * (1 + 2 * (time_delay / time_const_0) - (time_const_0 / time_const));
    reg2 = gain * (time_delay / time_const_0);

    nonlinear_system();

    return 0;
}
