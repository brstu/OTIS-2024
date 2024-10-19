#include <iostream>
#include <vector>
#include <cmath>

class TemperatureControl {
public:
    TemperatureControl(double a, double b, double c, double d, double initialY0, double roomTemp)
        : a(a), b(b), c(c), d(d), Y0(roomTemp) {
        y.push_back(initialY0); 
        y_previous.push_back(initialY0); 
    }

    void simulate(int steps, double inputWarm) {
        for (int τ = 1; τ < steps; ++τ) {
            double y_current = a * y[τ - 1] + b * inputWarm; 
            double y_nonlinear = a * y[τ - 1] - b * std::pow(y_previous[τ - 1], 2) + c * inputWarm + d * std::sin(inputWarm);

            y.push_back(y_current); 
            y_previous.push_back(y[τ - 1]); 

            std::cout << "Шаг " << τ << ":\n";
            std::cout << "Линейная модель температуры: " << y_current << "\n";
            std::cout << "Нелинейная модель температуры: " << y_nonlinear << "\n\n";
        }
    }

private:
    double a, b, c, d; 
    double Y0; 
    std::vector<double> y; 
    std::vector<double> y_previous; 
};

int main() {
    setlocale(LC_ALL, "RU");
    
    double a = 0.9;
    double b = 0.5; 
    double c = 0.1;
    double d = 0.05; 
    double initialY0 = 20.0; 
    double roomTemp = 22.0; 
    double inputWarm = 5.0; 
    int steps = 10;

    TemperatureControl simulator(a, b, c, d, initialY0, roomTemp);
    simulator.simulate(steps, inputWarm);

    return 0;
}