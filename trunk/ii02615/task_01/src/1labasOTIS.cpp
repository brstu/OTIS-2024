#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

float alpha = 0.6, beta = 0.8, c = 0.2, delta = 1.0, epsilon = 0.2;

vector<float> Linear(int steps, float initialTemperature) {
    vector<float> result(steps);
    result[0] = initialTemperature;

    for (int i = 1; i < steps; ++i) {
        result[i] = alpha * result[i - 1] + beta * epsilon;
    }
    return result;
}

vector<float> NonLinear(int steps, float initialTemperature) {
    vector<float> result(steps);
    result[0] = initialTemperature;

    if (steps > 1) {
        result[1] = alpha * result[0] + c * epsilon + delta * sin(epsilon);
    }

    for (int i = 2; i < steps; ++i) {
        result[i] = alpha * result[i - 1] - beta * pow(result[i - 2], 2) + c * epsilon + delta * sin(epsilon);
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    float initialTemperature;
    int steps;
    vector<vector<float>> results;

    cout << "Введите начальное значение T: ";
    cin >> initialTemperature;

    cout << "Введите количество шагов: ";
    cin >> steps;
    steps++;

    results.push_back(Linear(steps, initialTemperature));
    results.push_back(NonLinear(steps, initialTemperature));

    cout << right << setw(10) << "Ит:" << setw(10) << right << "Линейный" << setw(13) << right << "Нелинейный" << endl;

    for (int i = 0; i < steps; ++i) {
        cout << right << setw(10) << i << setw(10) << results[0][i] << setw(13) << results[1][i] << endl;
    }

    return 0;
}