#include <iostream>
#include <vector>

int main() {
    double YS = 0.0; // Инициализация YS
    double W = 10.0; // Инициализация W

    // Теперь можно инициализировать векторы
    std::vector<double> y;
    y.push_back(YS);
    double U = 1.0;
    std::vector<double> E;
    E.push_back(W - YS);
    std::vector<double> um;
    um.push_back(U);

    // Вывод для проверки
    std::cout << "y: ";
    for (const auto& val : y) {
        std::cout << val << " ";
    }
    std::cout << "nE: ";
    for (const auto& val : E) {
        std::cout << val << " ";
    }
    std::cout << "num: ";
    for (const auto& val : um) {
        std::cout << val << " ";
    }

    return 0;
}
