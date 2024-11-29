#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

double const a = 0.9;
double const b = 0.1;
double const c = 0.05;
double const d = 0.01;
double const u = 10.0;

std::vector<double> LinearMod(int t, double yt, double ut) {
    std::vector<double> linearResult(t);
    linearResult[0] = yt;
    for (int i = 1; i < t; i++) {
        linearResult[i] = a * linearResult[i - 1] + b * ut;
    }
    return linearResult;
}

std::vector<double> NonlinearMod(int t, double yt, double yt_1, double ut_1) {
    std::vector<double> nonlinearResult(t);
    nonlinearResult[0] = yt;
    if (t > 1) {
        nonlinearResult[1] = a * nonlinearResult[0] + c * ut_1 + d * sin(ut_1);
    }

    for (int i = 2; i < t; i++) {
        nonlinearResult[i] = a * nonlinearResult[i - 1] - b * pow(nonlinearResult[i - 2], 2) + c * ut_1 + d * sin(ut_1);
    }

    return nonlinearResult;
}

std::vector<double> PIDRegulator(int t, const std::vector<double>& setpoint, const std::vector<double>& state) {
    std::vector<double> output(t);
    double error, integralError = 0.0, previousError = 0.0;
    double Kp = 1.0, Ki = 0.1, Kd = 0.5;

    for (int i = 0; i < t; i++) {
        error = setpoint[i] - state[i];
        integralError += error;
        output[i] = Kp * error + Ki * integralError + Kd * (error - previousError);
        previousError = error;
    }

    return output;
}

int main() {
    setlocale(LC_ALL, "rus");

    double startTemperature;
    int times;
    std::vector<std::vector<double>> results;
    std::vector<double> setpoints;

    std::cout << "Введите стартовую температуру: ";
    std::cin >> startTemperature;
    std::cout << "Введите количество итераций: ";
    std::cin >> times;

    times += 1;

    for (int i = 0; i < times; i++) {
        setpoints.push_back(20.0 + 10.0 * sin(0.1 * i));
    }

    results.push_back(LinearMod(times, startTemperature, u));
    results.push_back(NonlinearMod(times, startTemperature, startTemperature, u));

    std::vector<double> pidOutput = PIDRegulator(times, setpoints, results[1]);

    std::cout << std::right << std::setw(10) << "Итерация   "
        << std::setw(15) << "Зад.температура"
        << std::setw(10) << "Линейная"
        << std::setw(13) << "Нелинейная"
        << std::setw(15) << "ПИД-регулятор" << std::endl;

    for (int i = 0; i < times; i++) {
        std::cout << std::right << std::setw(10) << i
            << std::setw(15) << setpoints[i]
            << std::setw(10) << results[0][i]
            << std::setw(13) << results[1][i]
            << std::setw(15) << pidOutput[i] << std::endl;
    }

    return 0;
}