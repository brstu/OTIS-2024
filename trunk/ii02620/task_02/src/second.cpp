#include <iostream>
#include <cmath>
#include <array>
#include <iomanip>
#include <vector> 

using namespace std;

void control() {
    const double kp = 0.097;     
    const double ti = 2.162;  
    const double td = 1.0;         
    const double dt = 0.0001;     

    const double k0 = kp * (1.0 + (dt != 0 ? td / dt : 0.0));
    const double k1 = -kp * (1.0 + 2.0 * td / dt - dt / ti);
    const double k2 = (kp * td) / dt;

    const int numIter = 10;       
    const double setpoint = 29.0;    

    cout << "Начало работы регулятора\n";
    cout << setw(8) << "Итерация" << setw(20) << "Обновленное значение" << setw(20) << "Управляющее воздействие" << endl;

    const double a_model = 0.7;
    const double b_model = 0.2;
    double output = 0.0;
    double control = 0.0;


    auto model = [&](double e, double a, double b, double x) {
        return a * e + b * x; 
        };

    // Вектор для хранения значений ошибки
    vector<double> error(3, 0.0);

    // Цикл регулирования
    for (int i = 1; i <= numIter; i++) {
        error[2] = error[1];
        error[1] = abs(setpoint - output);
        const double deltaControl = k0 * error[1] + k1 * error[2] + k2 * error[0]; // Изменение управляющего воздействия
        const double prevControl = control;
        control = prevControl + deltaControl;
        output = model(output, a_model, b_model, control); 

        // Вывод результатов в таблицу
        cout << setw(8) << i << setw(22) << output << setw(20) << control << endl;
        error[0] = error[1]; //Обновление массива ошибок
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    control();
    return 0;
}

