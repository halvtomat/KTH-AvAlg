#ifndef OPT2_H
#define OPT2_h

#include <vector>
#include <chrono>
#include "helper.h"

using namespace std;

void opt2(vector<int> &path, double **&distances, chrono::time_point<chrono::high_resolution_clock> start_time, double time_limit);

void opt2_annealing(vector<int> &path, double **&distances, chrono::time_point<chrono::high_resolution_clock> start_time, double time_limit, double &temp);

#endif
