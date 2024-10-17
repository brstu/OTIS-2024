#include <iostream>
#include <cmath>
using namespace std;

double a = 0.5;  
double b = 0.01;   
double c = 0.2;  
double d = 0.4;  

double linearModel(double y, double u) {
    return a * y + b * u;
}

double nonlinearModel(double y, double u, double y_pred, double u_pred) {
    return a * y - b * pow(y_pred, 2) + c * u + d * sin(u_pred);
}
  
int main() {
    setlocale(LC_ALL, "ru");
    double y;
    cout << "Введите начальную температуру:" << endl;
    cin >> y;
    double y_next = y;
    double y_pred;
    double u = 8;
    double u_pred;
    u_pred = u;
    int steps = 10;

    cout << "Линейная модель" << endl;
    cout << "Время:\tТемпература:" << endl;
    for (int i = 0; i < steps; i++) {
        y_pred = y_next;
        y_next = linearModel(y_next, u);
        cout << i + 1 << "\t" << y_next << endl;
    }
    cout << endl;
    y_next = y;
    cout << "Нелинейная модель:" << endl;
    cout << "Время:\tТемпература:" << endl;
    for (int i = 0; i < steps; i++) {
        y_pred = y_next;
        y_next = nonlinearModel(y_next, u, y, u_pred);
        cout << i + 1 << "\t" << y_next << endl; 
    }
    return 0;
}