#include <cmath>
#include <iostream>
#include <map>
#include "w.h"
#include "util.h"

double w_2(double x)
{
  auto abs_x = abs(x);
  if (abs_x >= 0 && abs_x <= 1)
    return 1 - abs_x;

  return 0;
}

double w_3(double x)
{
  auto abs_x = abs(x);

  if (abs_x >= 0 && abs_x <= 1)
  {
    return 1.0 - ((5.0 / 2.0) * pow(abs_x, 2.0)) + ((3.0 / 2.0) * pow(abs_x, 3.0));
  }
  else if (abs_x >= 1 && abs_x <= 2)
  {
    return ((1.0 / 2.0) * pow(2.0 - abs_x, 2.0)) * (1.0 - abs_x);
  }

  return 0;
}

double w_4(double x)
{
  auto abs_x = abs(x);

  if (abs_x >= 0.0 && abs_x <= 1.0)
  {
    return 1.0 - (abs_x / 2.0) - pow(abs_x, 2.0) + (pow(abs_x, 3.0) / 2.0);
  }
  else if (abs_x >= 1.0 && abs_x <= 2.0)
  {
    return 1.0 - ((11.0 * abs_x) / 6.0) + pow(abs_x, 2.0) - (pow(abs_x, 3.0) / 6.0);
  }

  return 0.0;
}

double w_6(double x)
{
  auto abs_x = abs(x);

  if (abs_x >= 0.0 && abs_x <= 1.0)
  {
    return 1.0 - (abs_x / 3.0) - ((5.0 * pow(abs_x, 2.0)) / 4.0) + ((5.0 * pow(abs_x, 3.0)) / 12.0) + (pow(abs_x, 4.0) / 4.0) - (pow(abs_x, 5.0) / 12.0);
  }
  else if (abs_x >= 1.0 && abs_x <= 2.0)
  {
    return 1.0 - ((13.0 * abs_x) / 12.0) - ((5.0 * pow(abs_x, 2.0)) / 8.0) + ((25.0 * pow(abs_x, 3.0)) / 24.0) - ((3.0 * pow(abs_x, 4.0)) / 8.0) + (pow(abs_x, 5.0) / 24.0);
  }
  else if (abs_x >= 2.0 && abs_x <= 3.0)
  {
    return 1.0 - ((137.0 * abs_x) / 60.0) + ((15.0 * pow(abs_x, 2.0)) / 8.0) - ((17.0 * pow(abs_x, 3.0)) / 24.0) + (pow(abs_x, 4.0) / 8.0) - (pow(abs_x, 5.0) / 120.0);
  }

  return 0;
}

double w(std::shared_ptr<std::vector<double>> z, double h, double (*w_script)(double))
{
  double product = 1.0;
  for (int i = 0; i < z->size(); i++)
  {
    product *= w_script((z->at(i)) / h);
  }
  return product;
}

double w(double z, double h, double (*w_script)(double))
{
  return w_script(z / h);
}

std::string get_w_name(double (*w_script)(double))
{
  if (w_script == w_2)
  {
    return "W_2";
  }
  else if (w_script == w_3)
  {
    return "W_3";
  }
  else if (w_script == w_4)
  {
    return "W_4";
  }
  else if (w_script == w_6)
  {
    return "W_6";
  }
  return NULL;
}

double L2_1(double x)
{
  double abs_x = abs(x);
  double temp = 0;
  if (abs_x <= 1)
    temp += 1. - ((5. / 2.) * pow(abs_x, 2.)) + ((3 / 2) * pow(abs_x, 3.));
  else if (1 < abs(x) && abs(x) <= 2)
    temp += 2 - (4 * (abs(x))) + ((5 / 2) * pow(abs_x, 2.)) - (pow(abs_x, 3.) / 2);
  return temp;
}

double L2_2(double x)
{
  double abs_x = abs(x);
  double temp = 0;
  if (abs_x <= 1)
    temp += 1 - pow(abs_x, 2.) - ((9 / 2) * pow(abs_x, 3.)) + ((15 / 2) * pow(abs_x, 4.)) - (3 * pow(abs_x, 5.));
  else if (1 < abs_x && abs_x <= 2)
    temp += -4 + (18 * abs(x)) - (29 * pow(abs_x, 2.)) + ((43 / 2) * pow(abs_x, 3.)) - ((15 / 2) * pow(abs_x, 4.)) + pow(abs_x, 5.);
  return temp;
}

double L4_2(double x)
{
  double abs_x = abs(x);
  double temp = 0;
  if (abs_x <= 1)
    temp += 1 - ((5 / 4) * pow(abs_x, 2.)) - ((35 / 12) * pow(abs_x, 3.)) + ((21 / 4) * pow(abs_x, 4.)) - ((25 / 12) * pow(abs_x, 5.));
  else if (1 < abs_x && abs_x <= 2)
    temp += -4 + ((75 / 4) * (abs(x))) - ((245 / 8) * pow(abs_x, 2.)) + ((545 / 24) * pow(abs_x, 3.)) - ((63 / 8) * pow(abs_x, 4.)) + ((25 / 24) * pow(abs_x, 5.));
  else if (2 < abs_x && abs_x <= 3)
    temp += (18 - ((153 / 4) * (abs(x))) + ((255 / 8) * pow(abs_x, 2.)) - ((313 / 24) * pow(abs_x, 3.)) + ((21 / 8) * pow(abs_x, 4.)) - ((5 / 24) * pow(abs_x, 5.)));
  return temp;
}

double L4_4(double x)
{
  double abs_x = abs(x);
  double temp = 0;
  if (abs_x <= 1)
    temp += (1 - ((5 / 4) * pow(abs_x, 2.)) + ((1 / 4) * pow(abs_x, 4.)) - ((100 / 3) * pow(abs_x, 5.)) + ((455 / 4) * pow(abs_x, 6.)) - ((295 / 2) * pow(abs_x, 7.)) + ((345 / 4) * pow(abs_x, 8.)) - ((115 / 6) * pow(abs_x, 9.)));
  else if (1 < abs_x && abs_x <= 2)
    temp += (-199 + ((5485 / 4) * (abs(x))) - ((32975 / 8) * pow(abs_x, 2.)) + ((28425 / 4) * pow(abs_x, 3.)) - ((61953 / 8) * pow(abs_x, 4.)) + ((33175 / 6) * pow(abs_x, 5.)) - ((20685 / 8) * pow(abs_x, 6.)) + ((3055 / 4) * pow(abs_x, 7.)) - ((1035 / 8) * pow(abs_x, 8.)) + ((115 / 12) * pow(abs_x, 9.)));
  else if (2 < abs_x && abs_x <= 3)
    temp += (5913 - ((89235 / 4) * (abs(x))) + ((297585 / 8) * pow(abs_x, 2.)) - ((143895 / 4) * pow(abs_x, 3.)) + ((177871 / 8) * pow(abs_x, 4.)) - ((54641 / 6) * pow(abs_x, 5.)) + ((19775 / 8) * pow(abs_x, 6.)) - ((1715 / 4) * pow(abs_x, 7.)) + ((345 / 8) * pow(abs_x, 8.)) - ((23 / 12) * pow(abs_x, 9.)));
  return temp;
}