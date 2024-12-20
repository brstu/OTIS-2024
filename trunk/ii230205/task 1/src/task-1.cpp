#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

double const a = 0.9;
double const b = 0.4;
double const c = 0.1;
double const d = 1.2;
double const u = 1.6;

std::vector<double> LinearMod(int t, double yt) {
    std::vector<double> linearResult(t);
    linearResult[0] = yt;
    for (int i = 1; i < t; i++) {
        linearResult[i] = a * linearResult[i - 1] + b * u;
    }
    return linearResult;
}

std::vector<double> NonlinearMod(int t, double yt) {
    std::vector<double> nonlinearResult(t);
    nonlinearResult[0] = yt; 
    if (t > 1) {
        nonlinearResult[1] = a * nonlinearResult[0] + c * u + d * sin(u); 
    }

    for (int i = 2; i < t; i++) {
        nonlinearResult[i] = a * nonlinearResult[i - 1] - b * pow(nonlinearResult[i - 2], 2) + c * u + d * sin(u);
    }

    return nonlinearResult;
}

int main() {
    setlocale(LC_ALL, "rus");

    double startTemperature;
    int times;
    std::vector<std::vector<double>> results;

    std::cout << "Введите стартовую температуру: ";
    std::cin >> startTemperature;
    std::cout << "Введите время: ";
    std::cin >> times;

    times += 1;

    results.push_back(LinearMod(times, startTemperature));
    results.push_back(NonlinearMod(times, startTemperature));

    std::cout << std::right << std::setw(10) << "Итерация"
        << std::setw(10) << std::right << "Линейная"
        << std::setw(13) << std::right << "Нелинейная" << std::endl;

    for (int i = 0; i < times; i++) {
        std::cout << std::right << std::setw(10) << i
            << std::setw(10) << results[0][i]
            << std::setw(13) << results[1][i] << std::endl;
    }

    return 0;
}