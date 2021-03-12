#include "util.h"
#include "w.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// forward declarations
std::shared_ptr<std::vector<double>> evaluate_z(double, double);

double I_pg(int, double, double, double (*)(double), int, int);

double eval(double, int, double, double (*)(double), int);

double exact(double (*)(double), double, double);
double x(double, double);
double x_k(double, int, double);

void graph(std::vector<double> const &, std::vector<double> const &, double (*)(double), std::string, std::string);
// END forward declarations

// global vars
int N_array[6] = {16, 32, 64, 128, 256, 512};
double (*f_pointers[2])(double) = {f_one, f_two};
double (*w_pointers[2])(double) = {w_2, w_4};
int dimensions = 1;
// END global vars

// windows: -I/usr/include/python2.7 -lpython2.7
// mac: -I/System/Library/Framework/Python.framework/Versions/2.7/include/python2.7 -lpython2.7
int main(int argc, char **argv)
{
  char *p;
  for (auto N : N_array)
  {
    double h = 1./static_cast<double>(N);
    std::vector<double> h_vals, errors;
    for (int i = -16; i<0; ++i)
    {
      double c = pow(10., i);
      errors.push_back(eval(c, N, h, w_pointers[0], 0));
      h_vals.push_back(h);
    }
  }

  return 0;
}

double eval(double c, int N, double h, double (*w_script)(double), int test_case)
{
  std::vector<double> x_axis, y_axis, real;
  double max = 0;
  for (int k = (-N/2) + 4; k < (N/2) - 4; ++k)
  {
    double interpolated_value = I_pg(k, h, c, w_script, N, test_case);
    double exact_value = exact(f_pointers[test_case], static_cast<double>(k) * h, c);
    double difference = interpolated_value - exact_value;
    if (difference > max)
      max = difference;
  }
  return max;
  // plt::named_plot("interpolation", x_axis, y_axis);
  // plt::named_plot("solution", x_axis, real);
  // plt::title(get_w_name(w_script) + " N=" + std::to_string(N) + " t=" + std::to_string(t));
  // plt::legend();
  // plt::show();
}

// n = 128
// scale back time by a factor of 10, up to 0.00025
double I_pg(int k, double h, double t, double (*w_script)(double), int N, int test_case)
{
  auto r_double = get_r_double(w_script);
  double r_low = std::get<0>(r_double);
  double r_high = std::get<1>(r_double);

  double sum = 0;
  for (int k_i = k + r_low; k_i < k + r_high; ++k_i)
  {
    for (int j = 0; j < N; ++j)
    {
      double alpha = static_cast<double>(j) * h;
      double x_bar = static_cast<double>(k_i) * h;

      double x_k_val = x(alpha, t);
      double w_value = w(x_bar - x_k_val, h, w_script);

      double f_value;
      if (test_case == 0)
      {
        f_value = f_one(k_i * h);
      }
      else
      {
        f_value = f_two(k_i * h);
      }
      sum += f_value * w_value;
    }
  }
  return sum;
}

double exact(double (*f)(double), double x_alpha, double c)
{
  // return (f(alpha_x) / (1 - (2 * M_PI * c * cos(2 * M_PI * alpha_x))));
  return f(x_alpha/(1+c))/(1+c);
}

// the Lagrangian mapping
// x(alpha, 0) = alpha
double x_k(double t, int k, double h)
{
  return x(static_cast<double>(k) * h, t);
}

double x(double alpha, double t)
{
  return alpha - (t * sin(2.0 * M_PI * alpha));
}
