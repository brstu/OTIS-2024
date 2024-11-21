#include <iostream>
#include <cmath> 
using namespace std;
void simulateLine(double A, double B, double y0, double u0, int st) {
    double y = y0; 
    double u = u0; 

    cout << "Линейная модель:\n";
    for (int t = 0; t < st; ++t) {
        double y_n = A * y + B * u;
        cout << "Шаг времени " << t << ": Температура = " << y_n << endl;
        y = y_n; 
    }
}
void simulate(double A, double B, double C, double D, double y0, double u0, int step) {
    double y_p = y0; 
    double y = y0;
    double u = u0; 

    cout << "\nНелинейная модель:\n";
    for (int t = 0; t < step; ++t) {
        double y_n = A * y - B * y_p * y_p + C * u + D * sin(u);
        cout << "Шаг времени " << t << ": Температура = " << y_n << endl;
        y = y_n; 
        y_p = y;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    double A, B, C, D;
    double i_t, i_in;
    int s;

  
    cout << "Введите значение параметра a: ";
    cin >> A;

    cout << "Введите значение параметра b: ";
    cin >> B;

    cout << "Введите значение параметра c (для нелинейной модели): ";
    cin >> C;

    cout << "Введите значение параметра d (для нелинейной модели): ";
    cin >> D;

    cout << "Введите начальное значение температуры y0: ";
    cin >> i_t;

    cout << "Введите начальное значение управляющего сигнала u0: ";
    cin >> i_in;
    cout << "Введите количество шагов моделирования: ";
    cin >> s;
    simulateLine(A, B, i_t, i_in, s);
    simulate(A, B, C, D, i_t, i_in, s);

    return 0;
}