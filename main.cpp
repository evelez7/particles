#include "w.h"
#include "util.h"
#include <cmath>
#include <vector>
#include <memory>

// forward declarations
double I_PG(int, double);
std::shared_ptr<std::vector<double>> evaluate_z(double, double);
double I_pg_one(int, double, double(*)(double));
void interpolate(int);
std::shared_ptr<std::vector<double>> evaluate_z();
double x_k(double, double, int);
double x(double, double);

// global vars
int N_array[2] = {32, 64};
double (*w_pointers[4])(double) = {w_2, w_4};
int dimensions = 1;

int main(int argc, char** argv) {
    for (int i = 0; i < 2; ++i) {
        interpolate(i);
    }
    return 0;
}

void interpolate(int option) {
    if (option == 1) {
        for (auto w_script : w_pointers) {
            for (auto N : N_array) {
                double h = 1.0 / N;
                
                for (int k = 0; k < N; ++k) {
                    // double alpha = 
                    // double x_value = x()

                    I_pg_one(k, h, w_script);
                }
            }
        }
    } else if (option == 2) {

    }
}

// the first problem where t is from 0-0.05
// reminder that x_bar, x_k_val should probably be vectors
double I_pg_one(int k, double h, double (*w_script)(double)) {
    double sum = 0;
    //for (int) // summation
    for (double t = 0.0; t < 0.05; t+= 0.025) {
        double f_value = f(k*h);

        // double x_k_val = x()
        double x_bar = k*h;
        double x_k_val = x_k(t, h, k);
        auto z = x_bar - x_k_val;
        double w_value = w(z, h, w_script);
        sum += f_value * w_value;
    }
    return sum;
}


// the Lagrangian mapping
// x(alpha, 0) = alpha
double x(double alpha, double t) {
    return alpha - (t * sin(2 * M_PI * alpha));
}

double x_k(double t, double h, int k) {
    double alpha_k = static_cast<int>(k) * h;
    return (alpha_k, t);
}

std::shared_ptr<std::vector<double>> evaluate_z() {
    auto z = std::make_shared<std::vector<double>>();
    for (int i = 0; i < dimensions; ++i) {
        // z->push_back()
    }
    return z;
}