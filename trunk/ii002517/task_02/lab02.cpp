#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

double regulator1, regulator2, regulator3;

double paramA, paramB, paramC, paramD;

double backG, Time, delTime, time_const, target;

void simulation() {
    const short int start = 2;
    vector<double> outputs = { start, start };
    double controlInput = 1.0;
    vector<double> deviation = { target - start, target - start };
    vector<double> lastControlInputs = { controlInput, controlInput };

    while (abs(target - outputs.back()) > 0.01) {
        deviation.push_back(target - outputs.back());
        controlInput = lastControlInputs.back() + regulator1 * deviation.back() + regulator2 * deviation[deviation.size() - 2] + regulator3 * deviation[deviation.size() - 3];
        outputs.push_back(paramA * outputs.back() - paramB * outputs[outputs.size() - 2] + paramC * controlInput + paramD * sin(lastControlInputs.back()));
        lastControlInputs.push_back(controlInput);
    }

    cout << "SteptOutputtErrortControl Inputn";
    for (int i = 0; i < outputs.size(); i++)
        cout << i + 1 << ";" << outputs[i] << ";" << deviation[i] << ";" << lastControlInputs[i] << endl;
}



int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите коэффициенты системы: (paramA, paramB, paramC, paramD)" << endl;
    cin >> paramA >> paramB >> paramC >> paramD;

    cout << "Введите параметры системы:\n";
    cout << "feedbackGain: "; cin >> backG;
    cout << "initialTimeConst: "; cin >> Time;
    cout << "delayTime: "; cin >> delTime;
    cout << "timeConstant: "; cin >> time_const;
    cout << "targetOutput (желаемое значение выхода): "; cin >> target;

    regulator1 = backG * (1 + (delTime / Time));
    regulator2 = -backG * (1 + 2 * (delTime / Time) - (Time / time_const));
    regulator3 = backG * (delTime / Time);

    simulation();
}