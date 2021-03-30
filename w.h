#ifndef W_H
#define W_H

#include <string>
#include <memory>
#include <vector>

double w_2(double);

double w_3(double);

double w_4(double);

double w_6(double);

double L4_4(double);

double L4_2(double);

double L2_2(double);

double L2_1(double);

double w(std::shared_ptr<std::vector<double>>, double, double (*)(double));

double w(double, double, double (*)(double));

std::string get_w_name(double (*)(double));
#endif