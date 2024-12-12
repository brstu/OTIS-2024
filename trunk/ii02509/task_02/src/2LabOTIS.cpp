#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Коэффициенты системы
double paramA, paramB, paramC, paramD;
// Параметры системы
double feedbackGain, initialTimeConst, delayTime, timeConstant, targetOutput;
// Параметры регулятора
double regulator1, regulator2, regulator3;

void simulateNonlinearSystem() {
    // Начальные параметры
    const short int startOutput = 2;
    vector<double> outputs = { startOutput, startOutput };  // Выходные значения
    double controlInput = 1.0;  // Управляющий сигнал
    vector<double> deviation = { targetOutput - startOutput, targetOutput - startOutput };  // Ошибка
    vector<double> lastControlInputs = { controlInput, controlInput };  // Предыдущие значения управляющего сигнала

    // Цикл, пока ошибка не станет меньше заданного порога
    while (abs(targetOutput - outputs.back()) > 0.01) {
        deviation.push_back(targetOutput - outputs.back());  // Обновление ошибки
        controlInput = lastControlInputs.back() + regulator1 * deviation.back() + regulator2 * deviation[deviation.size() - 2] + regulator3 * deviation[deviation.size() - 3];
        // Рассчитываем новое значение выхода системы
        outputs.push_back(paramA * outputs.back() - paramB * outputs[outputs.size() - 2] + paramC * controlInput + paramD * sin(lastControlInputs.back()));
        lastControlInputs.push_back(controlInput);  // Сохраняем управляющий сигнал
    }

    // Вывод результатов
    cout << "SteptOutputtErrortControl Inputn";
    for (int i = 0; i < outputs.size(); i++)
        cout << i + 1 << ";" << outputs[i] << ";" << deviation[i] << ";" << lastControlInputs[i] << endl;
}

int main() {
    setlocale(LC_ALL, "Rus");
    // Ввод параметров системы
    cout << "Введите коэффициенты системы:n";
    cout << "paramA: "; cin >> paramA;
    cout << "paramB: "; cin >> paramB;
    cout << "paramC: "; cin >> paramC;
    cout << "paramD: "; cin >> paramD;

    // Ввод параметров системы
    cout << "Введите параметры системы:n";
    cout << "feedbackGain: "; cin >> feedbackGain;
    cout << "initialTimeConst: "; cin >> initialTimeConst;
    cout << "delayTime: "; cin >> delayTime;
    cout << "timeConstant: "; cin >> timeConstant;
    cout << "targetOutput (желаемое значение выхода): "; cin >> targetOutput;

    // Расчет параметров регулятора
    regulator1 = feedbackGain * (1 + (delayTime / initialTimeConst));
    regulator2 = -feedbackGain * (1 + 2 * (delayTime / initialTimeConst) - (initialTimeConst / timeConstant));
    regulator3 = feedbackGain * (delayTime / initialTimeConst);

    // Запуск моделирования
    simulateNonlinearSystem();

    return 0;
}
