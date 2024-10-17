#include <iostream>
#include <cmath> 

using namespace std;

// Функция для моделирования линейной системы
void linearModelSimulation(double a, double b, double y0, double u0, int n) {
    double yt = y0;  
    double ut = u0;  

    cout << "\n--- Моделирование линейной системы ---\n";
    for (int t = 0; t < n; ++t) {
        double yt_next = a * yt + b * ut;  // Уравнение линейной модели
        cout << "Шаг " << t + 1 << ": y[" << t + 1 << "] = " << yt_next << endl;
        yt = yt_next;
    }
}

// Функция для моделирования нелинейной системы
void nonlinearModelSimulation(double a, double b, double c, double d, double y0, double y_prev, double u0, int n) {
    double yt = y0;           
    double yt_minus1 = y_prev; 
    double ut = u0;           

    cout << "\n--- Моделирование нелинейной системы ---\n";
    for (int t = 0; t < n; ++t) {
        double yt_next = a * yt - b * yt_minus1 * yt_minus1 + c * ut + d * sin(ut - 1);  // Уравнение нелинейной модели
        cout << "Шаг " << t + 1 << ": y[" << t + 1 << "] = " << yt_next << endl;

        yt_minus1 = yt;  
        yt = yt_next;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a, b, c, d;  
    double y0, u0, y_prev;  
    int n;  

    cout << "Введите константу a: ";
    cin >> a;
    cout << "Введите константу b: ";
    cin >> b;
    cout << "Введите константу c (для нелинейной модели): ";
    cin >> c;
    cout << "Введите константу d (для нелинейной модели): ";
    cin >> d;
    cout << "Введите начальное значение температуры y0: ";
    cin >> y0;                                                      
    //Константы можно было задать вначале
    cout << "Введите начальное значение предыдущей температуры (для нелинейной модели): ";
    cin >> y_prev;
    cout << "Введите начальное значение температуры: ";
    cin >> u0;
    cout << "Введите количество временных шагов n: ";
    cin >> n;

    linearModelSimulation(a, b, y0, u0, n);
    nonlinearModelSimulation(a, b, c, d, y0, y_prev, u0, n);

    return 0;
}
