### Переменные нашей модели:
```
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
```

Вывод: В ходе лабораторной работе научился работать с нелинейными моделями.
