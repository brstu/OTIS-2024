#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void unlinear_model()
{
  const double alpha= 0.95, b = 0.2, c = 1.0, d = 1.5;
  const double K = 0.73, T0 = 1.4, TD = 1.0, T = 1.25, w = 34.1;

  double q0 = K * (1 + TD / T0);
  double q1 = -K * (1 + 2 * TD / T0 - T0 / T);
  double q2 = K * (TD / T0);

  const short int y_start = 3;
  double u = 1.0;

  vector<double> y;
  vector<double> u_pred(2, u);

  y.push_back(alpha* y_start + c * u + d * sin(u));

  vector<double> e = { w - y_start, w - y.back() };

  while (abs(e.back()) > 0.001)
  {
    e.push_back(w - y.back());
    u = u_pred.back() + q0 * e.back() + q1 * e[e.size() - 2] + q2 * e[e.size() - 3];
    y.push_back(alpha* y.back() - b * y[y.size() - 2] + c * u + d * sin(u_pred.back()));
    u_pred.push_back(u);
  }

  cout << "Controller simulation result:\n\n";
  for (size_t i = 0; i < y.size(); i++)
  {
    cout << "y[" << i << "]=" << y[i] << "; ";
    cout << "e[" << i << "]=" << e[i] << "; ";
    cout << "u[" << i << "]=" << u_pred[i] << "; " << endl;
  }
}

int main()
{
  unlinear_model();
  return 0;
}
