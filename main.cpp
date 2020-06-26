#define WITHOUT_NUMPY
#include "matplotlibcpp.h"
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

void interpolate(double, int, double (*)(double), int);

double solution(double (*)(double), double, double);
double x(double, double);
double x_k(double, int, double);

void graph(std::vector<double> const &, std::vector<double> const &, double (*)(double), std::string, std::string);
// END forward declarations

// global vars
int N_array[3] = {32, 64, 128};
double (*f_pointers[2])(double) = {f_one, f_two};
double (*w_pointers[2])(double) = {w_2, w_4};
double t_array_one[3] = {0.0, 0.0025, 0.005};
double t_array_two[2] = {1.0 / (4 * M_PI), 1.0 / (2 * M_PI)};
int dimensions = 1;
// END global vars

namespace plt = matplotlibcpp;

// windows: -I/usr/include/python2.7 -lpython2.7
// mac: -I/System/Library/Framework/Python.framework/Versions/2.7/include/python2.7 -lpython2.7
int main(int argc, char **argv) {
    char *p;
    int test_case = strtol(argv[1], &p, 10);
    for (auto w_script : w_pointers) {
        for (auto N : N_array) {
            if (test_case == 0) {
                for (auto time : t_array_one) {
                    interpolate(time, N, w_script, test_case);
                }
            } else if (test_case == 1) {
                for (auto time : t_array_two) {
                    interpolate(time, N, w_script, test_case);
                }
            }
        }
    }

    return 0;
}

void interpolate(double t, int N, double (*w_script)(double), int test_case) {
    double h = 1.0 / static_cast<double>(N);
    std::vector<double> x_axis, y_axis, real;
    for (int k = 0; k < N; ++k) {
        double interpolated_value = I_pg(k, h, t, w_script, N, test_case);
        x_axis.push_back(k);
        y_axis.push_back(interpolated_value);
        real.push_back(solution(f_pointers[test_case], static_cast<double>(k) * h, t));
    }
    plt::named_plot("interpolation", x_axis, y_axis);
    plt::named_plot("solution", x_axis, real);
    plt::title(get_w_name(w_script) + " N=" + std::to_string(N) + " t=" + std::to_string(t));
    plt::legend();
    plt::show();
}

// n = 128
// scale back time by a factor of 10, up to 0.00025
double I_pg(int k, double h, double t, double (*w_script)(double), int N, int test_case) {
    auto r_double = get_r_double(w_script);
    double r_low = std::get<0>(r_double);
    double r_high = std::get<1>(r_double);

    double sum = 0;
    for (int k_i = k + r_low; k_i < k + r_high; ++k_i) {
        for (int j = 0; j < N; ++j) {
            double alpha = static_cast<double>(j) * h;
            double x_bar = static_cast<double>(k_i) * h;

            double x_k_val = x(alpha, t);
            double w_value = w(x_bar - x_k_val, h, w_script);

            double f_value;
            if (test_case == 0) {
                f_value = f_one(k_i * h);
            } else {
                // f_value = f_two(x_bar, alpha);
                // f_value = f_two(alpha, alpha); 
                f_value = f_two(x_k_val);
            }
            sum += f_value * w_value;
        }
    }
    return sum;
}

double solution(double (*f)(double), double alpha_x, double t) {
    return (f(alpha_x) / (1 - (2 * M_PI * t * cos(2 * M_PI * alpha_x))));
}
// the Lagrangian mapping
// x(alpha, 0) = alpha
double x_k(double t, int k, double h) {
    return x(static_cast<double>(k) * h, t);
}
double x(double alpha, double t) {
    return alpha - (t * sin(2.0 * M_PI * alpha));
}

void graph(std::vector<double> const &x, std::vector<double> const &y, double (*w_script)(double), std::string N, std::string time) {
   plt::plot(x, y);
   plt::title(get_w_name(w_script) + " N=" + N + " t=" + time);
   plt::show();
}
