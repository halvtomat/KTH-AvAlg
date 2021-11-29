#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

double calc_total_distance(vector<int> &path, double **&distances);

void calc_distances(int number_of_nodes, double **&nodes, double **&distances);

void init_nodes(int &number_of_nodes, double **&nodes, double **&distances);

void print_path(vector<int> &path);

#endif
