### Переменные нашей модели:
```
class SimulationModel
{
private:
    double A;
    double B;
    double C;
    double D;

    double coeff0;
    double coeff1;
    double coeff2;

    vector<double> coeff;
    vector<double> resid = { 0, 0, 0 };
    vector<double> hist = { 0, 0, 0 };
    vector<double> vel = { 1, 1 };
```

Bывод: В ходе лабораторной работе нayчился paботать c нелинейными моделями.
