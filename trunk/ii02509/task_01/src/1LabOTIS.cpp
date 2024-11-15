#include <iostream>
#include <cmath> // Для использования функции sin()
using namespace std;

// Линейная модель: y(t+1) = p * y(t) + q * v(t)
void executeLinearModel(double p, double q, double startValue, double inputValue, int iterations) {
    double currentState = startValue; // Начальное состояние
    double controlInput = inputValue; // Начальный управляющий вход

    cout << "Результаты линейной модели:n";
    for (int i = 0; i < iterations; ++i) {
        double nextState = p * currentState + q * controlInput;
        cout << "Шаг " << i << ": Состояние = " << nextState << endl;
        currentState = nextState; // Обновляем текущее состояние
    }
}

// Нелинейная модель: y(t+1) = p * y(t) - q * y^2(t-1) + r * v(t) + s * sin(v(t))
void executeNonlinearModel(double p, double q, double r, double s, double startValue, double inputValue, int iterations) {
    double previousState = startValue; // Состояние на предыдущем шаге
    double currentState = startValue; // Начальное состояние
    double controlInput = inputValue; // Начальный управляющий вход

    cout << "nРезультаты нелинейной модели:n";
    for (int i = 0; i < iterations; ++i) {
        double nextState = p * currentState - q * previousState * previousState + r * controlInput + s * sin(controlInput);
        cout << "Шаг " << i << ": Состояние = " << nextState << endl;
        previousState = currentState; // Обновляем состояние на предыдущем шаге
        currentState = nextState; // Обновляем текущее состояние
    }
}

int main() {
    // Переменные для параметров модели
    double paramP, paramQ, paramR, paramS;
    double initialTemp, initialControl;
    int stepCount;

    // Сбор данных от пользователя
    cout << "Введите параметр p: ";
    cin >> paramP;

    cout << "Введите параметр q: ";
    cin >> paramQ;

    cout << "Введите параметр r (для нелинейной модели): ";
    cin >> paramR;

    cout << "Введите параметр s (для нелинейной модели): ";
    cin >> paramS;

    cout << "Введите начальное значение состояния: ";
    cin >> initialTemp;

    cout << "Введите начальное значение управляющего входа: ";
    cin >> initialControl;

    cout << "Введите количество итераций моделирования: ";
    cin >> stepCount;

    // Запуск симуляций
    executeLinearModel(paramP, paramQ, initialTemp, initialControl, stepCount);
    executeNonlinearModel(paramP, paramQ, paramR, paramS, initialTemp, initialControl, stepCount);

    return 0;
}
