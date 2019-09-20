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
