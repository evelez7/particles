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
double I_pg(int, double, double, double (*)(double), int, int, int, int);

void interpolate(double, int, double (*)(double), int, int, int);
void interpolate(double, int, double (*)(double), int);

double x(double, double);

void graph(std::vector<double> const &, std::vector<double> const &, double (*)(double), std::string, std::string);
// END forward declarations

// global vars
int N_array[2] = {32, 64};
double (*w_pointers[4])(double) = {w_2, w_4};
double t_array_one[3] = {0.0, 0.025, 0.05};
double t_array_two[2] = {1.0 / (4 * M_PI), 1.0 / (2 * M_PI)};
int dimensions = 1;
// END global vars

namespace plt = matplotlibcpp;

// windows: -I/usr/include/python2.7 -lpython2.7
// mac: -I/System/Library/Framework/Python.framework/Versions/2.7/include/python2.7 -lpython2.7
int main(int argc, char **argv) {
    char *p;
    int test_case = strtol(argv[1], &p, 10);
    if (argc > 2) { // we must configure custom N for each test

        char *l;
        char *z;
        int start = strtol(argv[2], &l, 10);
        int end = strtol(argv[3], &z, 10);

        for (auto w_script : w_pointers) {
            for (auto N : N_array) {
                double h = 1.0 / static_cast<double>(N);
                if (test_case == 1) {
                    for (auto time : t_array_one) {
                        interpolate(time, N, w_script, test_case, start, end);
                    }
                } else if (test_case == 2) {
                    for (auto time : t_array_two) {
                        interpolate(time, N, w_script, test_case, start, end);
                    }
                }
            }
        }
    } else {

        for (auto w_script : w_pointers) {
            for (auto N : N_array) {
                double h = 1.0 / static_cast<double>(N);
                if (test_case == 1) {
                    for (auto time : t_array_one) {
                        interpolate(time, N, w_script, test_case);
                    }
                } else if (test_case == 2) {
                    for (auto time : t_array_two) {
                        interpolate(time, N, w_script, test_case);
                    }
                }
            }
        }
    }

    return 0;
}

void interpolate(double t, int N, double (*w_script)(double), int test_case, int start_loop, int end_loop) {
    double h = 1.0 / static_cast<double>(N);
    std::vector<double> x_axis, y_axis;
    for (int k = 0; k < N; ++k) {
        double interpolated_value = I_pg(k, h, t, w_script, N, test_case, start_loop, end_loop);
        x_axis.push_back(k);
        y_axis.push_back(interpolated_value);
    }
    graph(x_axis, y_axis, w_script, std::to_string(N), std::to_string(t));
}

void interpolate(double t, int N, double (*w_script)(double), int test_case) {
    double h = 1.0/static_cast<double>(N);
    std::vector<double> x_axis, y_axis;
    for (int k = 0; k < N; ++k) {
        double interpolated_value = I_pg(k, h, t, w_script, N, test_case);
        x_axis.push_back(k);
        y_axis.push_back(interpolated_value);
    }
    graph(x_axis, y_axis, w_script, std::to_string(N), std::to_string(t));
}

double I_pg(int k, double h, double t, double (*w_script)(double), int N, int test_case) {
    auto r_double = get_r_double(w_script);
    double r_low = std::get<0>(r_double);
    double r_high = std::get<1>(r_double);

    double sum = 0;
    for (int k_i = k + r_low; k_i < k+r_high; ++k_i) {
        double alpha = static_cast<double>(k_i) * h;
        double x_bar = static_cast<double>(k_i) * h;
        double x_k = x(alpha, t);
        double w_value = w(x_bar - x_k, h, w_script);

        double f_value;
        if (test_case ==1) {
            f_value = f_one(k_i * h, alpha);
        } else {
            f_value = f_two(k_i * h, alpha);
        }
        sum += f_value * w_value;
    }
    return sum;
}

// the first problem where t is from 0-0.05
// reminder that x_bar, x_k_val should probably be vectors
double I_pg(int k, double h, double t, double (*w_script)(double), int N, int test_case, int start_loop, int end_loop) {
    auto r_double = get_r_double(w_script);
    double r_low = std::get<0>(r_double);
    double r_high = std::get<1>(r_double);

    double sum = 0;
    for (int k_i = k + r_low; k_i < k + r_high; ++k_i) {
        for (int i = start_loop; i < end_loop; ++i) {
            double alpha = static_cast<double>(k_i) * h; // given info, we know alpha a priori
            double x_bar = static_cast<double>(i) * h;
            double x_k = x(alpha, t);
            double w_value = w(x_bar - x_k, h, w_script);

            double f_value;
            if (test_case == 1) {
                f_value = f_one(k_i * h, alpha);
            } else {
                f_value = f_two(k_i * h, alpha);
            }
            sum += f_value * w_value;
        }
    }
    return sum;
}

// the Lagrangian mapping
// x(alpha, 0) = alpha
double x(double alpha, double t) {
    return alpha - (t * sin(2.0 * M_PI * alpha));
}

void graph(std::vector<double> const &x, std::vector<double> const &y, double (*w_script)(double), std::string N, std::string time) {
    plt::plot(x, y);
    plt::title(get_w_name(w_script) + " N=" + N + " t=" + time);
    plt::show();
}