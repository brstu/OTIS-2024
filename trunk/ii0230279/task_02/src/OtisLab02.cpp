#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

// Глобальные переменные для коэффициентов и параметров
double coeffA, coeffB, coeffC, coeffD; // Коэффициенты системы
double gain, desiredOutput; // Параметры системы
double reg0, reg1, reg2; // Параметры регулятора

// Функция для симуляции системы
void runSimulation() {
    const double INITIAL_OUTPUT = 2.0;  // Начальное значение выхода
    double controlSignal = 0.0;          // Изначальный управляющий сигнал
    double integral = 0.0; // Переменная для интегральной части
    double previousError = 0.0; // Переменная для хранения предыдущей ошибки
    vector<double> outputs = { INITIAL_OUTPUT };  // Вектор выходных значений
    vector<double> errors = { desiredOutput - INITIAL_OUTPUT };  // Инициализация вектора ошибок

    // Цикл продолжается, пока ошибка больше 0.01
    while (fabs(errors.back()) > 0.01) {
        double currentError = desiredOutput - outputs.back(); // Текущая ошибка
        errors.push_back(currentError);

        // Обновление интегральной части
        integral += currentError;

        // Пропорциональная + интегральная + дифференциальная составляющая
        controlSignal = gain * (currentError + 0.1 * integral + 0.1 * (currentError - previousError));

        // Упрощенные формулы для нового выхода
        double newOutput = coeffA * outputs.back() + coeffB * sin(controlSignal) + coeffC * controlSignal;

        // Обновление выходных данных
        outputs.push_back(newOutput);
        previousError = currentError; // Обновление предыдущей ошибки
    }

    // Вывод результатов симуляции
    cout << fixed << setprecision(4);  // Форматируем вывод с 4 знаками после запятой
    cout << "Step\tOutput\tError\n";
    for (size_t i = 0; i < outputs.size(); ++i) { // Итерируем по всем шагам
        cout << i + 1 << "\t"
            << outputs[i] << "\t"
            << errors[i] << endl;
    }
}

int main() {
    // Ввод параметров системы от пользователя
    setlocale(LC_ALL, "RU");
    cout << "Введите коэффициенты системы:\n";
    cout << "coeffA: "; cin >> coeffA;
    cout << "coeffB: "; cin >> coeffB;
    cout << "coeffC: "; cin >> coeffC;
    cout << "coeffD: "; cin >> coeffD;

    cout << "\nВведите параметры системы:\n";
    cout << "gain: "; cin >> gain;
    cout << "desiredOutput (желаемое значение выхода): "; cin >> desiredOutput;

    // Расчет параметров регулятора
    reg0 = gain + 5; // Можно сделать их зависящими от gain
    reg1 = -gain / 2; // Изменяем коэффициент для большей сложности
    reg2 = gain * 0.5; // Можно использовать различные значения для упрощения и компоновки

    // Запуск симуляции
    runSimulation();

    return 0; // Выход из программы
}