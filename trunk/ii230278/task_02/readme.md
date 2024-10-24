# Лабораторная работа 2

в ходе лабораторной работы научился работать с нелинейными моделями

```C++
void nonLinear() {
    const double init_output = 2;
    vector<double> output;
    output.push_back(init_output);
    double controlSign = 1.0; 
    vector<double> err;
    err.push_back(des - init_output); 
    vector<double> prevSign;
    prevSign.push_back(controlSign); 
    
    while (abs(des - output.back()) > 0.01) {
        double current_err = des - output.back();  
        err.push_back(current_err);  
```