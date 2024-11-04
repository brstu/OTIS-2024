#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class SimulationModel
{
private:
    double paramA;
    double paramB;
    double paramC;
    double paramD;

    double coeff0;
    double coeff1;
    double coeff2;

    vector<double> coefficients;
    vector<double> residuals = { 0, 0, 0 };
    vector<double> history = { 0, 0, 0 };
    vector<double> velocities = { 1, 1 };

public:
    SimulationModel(double a, double b, double c, double d)
        : paramA(a), paramB(b), paramC(c), paramD(d),
        coeff0(paramA* (1 + paramC / paramD)),
        coeff1(-paramA * (1 + 2 * paramC / paramD - paramD / paramB)),
        coeff2(paramA* paramC / paramD),
        coefficients({ coeff0, coeff1, coeff2 }) {}

    double computeTotal()
    {
        double sum = 0;
        for (int i = 0; i < 3; i++)
        {
            sum += coefficients[i] * residuals[i];
        }
        return sum;
    }

    void executeNonlinearProcess(int iterations, double targetValue, double xFactor = 0.5,
        double yFactor = 0.3, double wFactor = 0.9,
        double sFactor = 0.7)
    {
        for (int i = 0; i < iterations; i++)
        {
            residuals[0] = targetValue - history[history.size() - 1];
            residuals[1] = targetValue - history[history.size() - 2];
            residuals[2] = targetValue - history[history.size() - 3];
            velocities[0] = velocities[1] + computeTotal();
            history.push_back(xFactor * history[history.size() - 1] -
                yFactor * history[history.size() - 2] * history[history.size() - 2] +
                wFactor * velocities[0] + sFactor * sin(velocities[1]));
            velocities[1] = velocities[0];
        }
    }

    vector<double> getHistory() const
    {
        return history;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    double targetValue;
    SimulationModel simModel(0.0001, 100, 100, 1);

    cout << "¬ведите целевое значение: ";
    cin >> targetValue;
    simModel.executeNonlinearProcess(100, targetValue);
    vector<double> results = simModel.getHistory();

    for (size_t i = 0; i < results.size(); i++)
    {
        double adjustedValue = results[i] * targetValue / results.back();
        cout << i << " " << adjustedValue << endl;
    }

    return 0;
}
