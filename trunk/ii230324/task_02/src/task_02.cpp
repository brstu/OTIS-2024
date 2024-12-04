#include <iostream>
#include <vector>
#include <iomanip> 
#include <cmath>

using namespace std;

// Определяем структуру для хранения результатов
struct SimulationResult {
    double step;   // Номер шага
    double output; // Выход y
    double error;  // Ошибка e
    double control; // Управление u

    SimulationResult(double s, double out, double err, double ctrl)
        : step(s), output(out), error(err), control(ctrl) {}
};

// Функция для инициализации констант и переменных
void initializeVariables(double& alpha, double& b, double& c, double& d,
                         double& K, double& T0, double& TD, double& T,
                         double& w, double& q0, double& q1, double& q2,
                         short int& yStart, double& u) {
    alpha = 0.95;
    b = 0.2;
    c = 1.2;
    d = 1;
    K = 0.73;
    T0 = 1.4;
    TD = 1.0;
    T = 1.25;
    w = 34.1;

    q0 = K * (1 + TD / T0);
    q1 = -K * (1 + 2 * TD / T0 - T0 / T);
    q2 = K * (TD / T0);

    yStart = 3;
    u = 1.0;
}

// Функция для отображения результатов в виде таблицы
void displayResults(const vector<SimulationResult>& results) {
    cout << "Результаты симуляции контроллера:\n";
    cout << left << setw(15) << "Шаг"
         << setw(25) << "Выход y"
         << setw(25) << "Ошибка e"
         << setw(25) << "Управление u" << endl;

    cout << string(75, '-') << endl; // Разделитель

    // Используем традиционный цикл for
    for (size_t i = 0; i < results.size(); ++i) {
        const SimulationResult& result = results[i];
        cout << setw(10) << result.step
             << setw(20) << fixed << setprecision(4) << result.output
             << setw(20) << fixed << setprecision(4) << result.error
             << setw(25) << fixed << setprecision(4) << result.control << endl;
    }
}

void nonlinearModel() {
    double alpha, b, c, d, K, T0, TD, T, w, q0, q1, q2;
    short int yStart;
    double u;

    // Инициализация переменных
    initializeVariables(alpha, b, c, d, K, T0, TD, T, w, q0, q1, q2, yStart, u);

    vector<SimulationResult> results; // Вектор для хранения результатов
    vector<double> y;
    vector<double> u_pred(2, u);
    y.push_back(alpha * yStart + c * u + d * sin(u));

    vector<double> e; // Объявляем вектор e
    e.push_back(w - yStart); // Добавляем первый элемент
    e.push_back(w - y.back()); // Добавляем второй элемент

    // Итеративный контрольный цикл
    int step = 0;
    while (abs(e.back()) > 0.001) {
        e.push_back(w - y.back());
        u = u_pred.back() + q0 * e.back() + q1 * e[e.size() - 2] + q2 * e[e.size() - 3];
        y.push_back(alpha * y.back() - b * y[y.size() - 2] + c * u + d * sin(u_pred.back()));
        u_pred.push_back(u);

        // Сохраняем результаты
        results.emplace_back(step++, y.back(), e.back(), u);
    }

    // Отображение результатов
    displayResults(results);
}

int main() {
    nonlinearModel();
    return 0;
}
