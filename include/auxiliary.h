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



q_s^{2}+ q_x^2− q_y^2 − q_z^2
2 · (qx · qy − qz · qs) 2 · (qx · qz + qy · qs)
2 · (qx · qy + qz · qs) q
2
s − q
2
x + q
2
y − q
2
z
2 · (qy · qz − qx · qs)
2 · (qx · qz − qy · qs) 2 · (qy · qz + qx · qs) q
2
s − q
2
x − q
2
y + q
2
