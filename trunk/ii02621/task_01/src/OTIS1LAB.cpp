#include <iostream>
#include <cmath> 
using namespace std;

// Линейная модель: y(t+1) = a * y(t) + b * u(t)
void simulateLinearModel(double A, double B, double y0, double u0, int steps) {
    double y = y0; 
    double u = u0; 

    cout << "Линейная модель:\n";
    for (int t = 0; t < steps; ++t) {
        double y_next = A * y + B * u;
        cout << "Шаг времени " << t << ": Температура = " << y_next << endl;
        y = y_next; 
    }
}

// Нелинейная модель: y(t+1) = A * y(t) - B * y^2(t-1) + C * u(t) + D * sin(u(t))
void simulateNonlinearModel(double A, double B, double C, double D, double y0, double u0, int steps) {
    double y_prev = y0; 
    double y = y0;
    double u = u0; 

    cout << "\nНелинейная модель:\n";
    for (int t = 0; t < steps; ++t) {
        double y_next = A * y - B * y_prev * y_prev + C * u + D * sin(u);
        cout << "Шаг времени " << t << ": Температура = " << y_next << endl;
        y_prev = y; 
        y = y_next; 
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    double A, B, C, D;
    double i_temperature, i_input;
    int steps;

  
    cout << "Введите значение параметра a: ";
    cin >> A;

    cout << "Введите значение параметра b: ";
    cin >> B;

    cout << "Введите значение параметра c (для нелинейной модели): ";
    cin >> C;

    cout << "Введите значение параметра d (для нелинейной модели): ";
    cin >> D;

    cout << "Введите начальное значение температуры y0: ";
    cin >> i_temperature;

    cout << "Введите начальное значение управляющего сигнала u0: ";
    cin >> i_input;
    cout << "Введите количество шагов моделирования: ";
    cin >> steps;
    simulateLinearModel(A, B, i_temperature, i_input, steps);
    simulateNonlinearModel(A, B, C, D, i_temperature, i_input, steps);

    return 0;
}