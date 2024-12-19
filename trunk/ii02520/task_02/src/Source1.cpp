#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class ModelSimulation {
private:
    double alpha;
    double beta;
    double gamma;
    double delta;

    double coeffA;
    double coeffB;
    double coeffC;

    vector<double> coeffArray;
    vector<double> errorTerms;
    vector<double> valueHistory;
    vector<double> speedArray;

    void initialize() {
        coeffA = alpha * (1 + gamma / delta);
        coeffB = -alpha * (1 + 2 * gamma / delta - delta / beta);
        coeffC = alpha * gamma / delta;
        coeffArray = { coeffA, coeffB, coeffC };
        errorTerms = { 0, 0, 0 };
        valueHistory = { 0, 0, 0 };
        speedArray = { 1, 1 };
    }

public:
    ModelSimulation(double a, double b, double c, double d) 
        : alpha(a), beta(b), gamma(c), delta(d) {
        initialize();
    }

    double calculateTotal() {
        double totalSum = 0;
        for (size_t i = 0; i < coeffArray.size(); i++) {
            totalSum += coeffArray[i] * errorTerms[i];
        }
        return totalSum;
    }

    void performNonlinearIteration(int steps, double targetValue,
                                   double xRate = 0.5, double yRate = 0.3,
                                   double wRate = 0.9, double sRate = 0.7) {
        for (int i = 0; i < steps; i++) {
            errorTerms[0] = targetValue - valueHistory.back();
            errorTerms[1] = targetValue - valueHistory[valueHistory.size() - 2];
            errorTerms[2] = targetValue - valueHistory[valueHistory.size() - 3];
            
            speedArray[0] = speedArray[1] + calculateTotal();
            double newValue = xRate * valueHistory.back() 
                            - yRate * pow(valueHistory[valueHistory.size() - 2], 2) 
                            + wRate * speedArray[0] 
                            + sRate * sin(speedArray[1]);
            
            valueHistory.push_back(newValue);
            speedArray[1] = speedArray[0];
        }
    }

    vector<double> getValueHistory() const {
        return valueHistory;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    double desiredValue;
    ModelSimulation simulationModel(0.0001, 100, 100, 1);

    cout << "Введите желаемое значение: ";
    cin >> desiredValue;

    simulationModel.performNonlinearIteration(100, desiredValue);
    vector<double> results = simulationModel.getValueHistory();

    for (size_t i = 0; i < results.size(); i++) {
        double adjustedResult = results[i] * desiredValue / results.back();
        cout << i << " " << adjustedResult << endl;
    }

    return 0;
}
