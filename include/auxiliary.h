#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

#include "State.h"
#include "3DTlib/math/point.h"

using namespace _3dtlib;
using namespace std;

static bool flag_init_record = true;

void save_csv(double t, Point ground_truth, Point measurement, State filter, std::string filename);
void save_csv(double t, vector<double> ground_truth, Point measurement, State filter, std::string filename);

template <typename T>
vector<T> linspace(T a, T b, size_t N)
{
    T h = (b - a) / static_cast<T>(N-1);
    std::vector<T> xs(N);
    typename std::vector<T>::iterator x;
    T val;
    for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h)
        *x = val;
    return xs;
}
