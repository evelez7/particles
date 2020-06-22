#include <string>
#include "w.h"
#include "util.h"
#include <map>
#include <cmath>

std::map<double (*)(double), std::tuple<int, int>> r_map = {
    {w_2, std::make_tuple(0, 1)},
    {w_3, std::make_tuple(-1, 2)},
    {w_4, std::make_tuple(-1, 2)},
    {w_6, std::make_tuple(-2, 3)}
};

double first_order_moment(std::vector<double> z_vector) {
    double sum = 0.0;
    for (auto z : z_vector) {
        sum += z;
    }
    return sum;
}

std::tuple<int, int> get_r_double(double (*w_script)(double)) {
    return r_map[w_script];
}

double f(double x) {
    return sin(2.0 * M_PI * x);
}

void verify_vector_length(std::shared_ptr<std::vector<std::vector<int>>> i, int size) {
    for (auto i_n : *i) {
        if (i_n.size() != size) {
            throw std::exception();
        }
    }
}