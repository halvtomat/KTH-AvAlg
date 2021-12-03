#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "helper.h"
#include "greedy.h"
#include "opt2.h"

#define VERY_BIG numeric_limits<int>::max()
#define TIME_LIMIT 1989999
#define INITIAL_TEMP 100.0

using namespace std;

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
	auto start_time = chrono::high_resolution_clock::now();
	double time_limit = TIME_LIMIT;
	int number_of_nodes;
	double **nodes;
	double **distances;
	double temp = INITIAL_TEMP;
	vector<int> path;
	init_nodes(number_of_nodes, nodes, distances);
	
	if(number_of_nodes == 1) {
		cout << 0 << "\n";
		return 0;
	}

	calc_distances(number_of_nodes, nodes, distances);

	greedy(path, number_of_nodes, distances);

	auto now_time = chrono::high_resolution_clock::now();
	while(chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() < TIME_LIMIT) {
		double prev_distance = calc_total_distance(path, distances);
		opt2_annealing(path, distances, start_time, time_limit, temp);
		double new_distance = calc_total_distance(path, distances);
		if(abs(new_distance - prev_distance) < 0.01)
			break;
		now_time = chrono::high_resolution_clock::now();
	}

	print_path(path);

	cerr << "Total distance = " << calc_total_distance(path, distances) << " , Total time = " << chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() << "\n";
	
	for (size_t i = 0; i < number_of_nodes; i++) {
		delete[] nodes[i];
		delete[] distances[i];
	}
	delete[] nodes;
	delete[] distances;
	
	return 0;
}
