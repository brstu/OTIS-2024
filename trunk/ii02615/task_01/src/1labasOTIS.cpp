#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>


float alpha = 0.6;
float beta = 0.8;
float c = 0.2;
float delta = 1.0;
float epsilon = 0.2;

std::vector<float> Linear(int steps, float initialTemperature) {
    std::vector<float> result(steps);
    result[0] = initialTemperature;

    for (int i = 1; i < steps; ++i) {
        result[i] = alpha * result[i - 1] + beta * epsilon;
    }
    return result;
}

std::vector<float> NonLinear(int steps, float initialTemperature) {
    std::vector<float> result(steps);
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
    std::vector<std::vector<float> > results;

    std::cout << "Введите начальное значение T: ";
    std::cin >> initialTemperature;

    std::cout << "Введите количество шагов: ";
    std::cin >> steps;
    steps++;

    results.push_back(Linear(steps, initialTemperature));
    results.push_back(NonLinear(steps, initialTemperature));

    std::cout << std::right << std::setw(10) << "Ит:" << std::setw(10) << std::right << "Линейный" << std::setw(13) << std::right << "Нелинейный" << std::endl;

    for (int i = 0; i < steps; ++i) {
        std::cout << std::right << std::setw(10) << i << std::setw(10) << results[0][i] << std::setw(13) << results[1][i] << std::endl;
    }

    return 0;
}