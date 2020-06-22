#ifndef UTIL_H
#define UTIL_H

#include <memory>
#include <tuple>
#include <list>
#include <vector>

double first_order_moment(std::vector<double> z_vector);

std::tuple<int, int> get_r_double(double (*)(double));

double f(double);

void test_w();

void verify_vector_length(std::shared_ptr<std::vector<std::vector<int>>>, int);
#endif