### Лабораторная работа 2
### ПИД-регуляторы
### Учащийся группы ИИ-25
### Янушкевич Вячеслав Александрович
### function
```C++
void control_system(double desired_value, int iterations) {
    double current_output = 0.0;

    for (int i = 0; i < iterations; ++i) {
        double error = desired_value - current_output;
        current_output = nonlinear_response(error, current_output);
        cout << "Iteration " << i + 1 << ": Output = " << current_output << endl;
    }
}
```