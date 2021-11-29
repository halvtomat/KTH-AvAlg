#include "helper.h"
#include "greedy.h"
#include "opt2.h"
#include <iostream>
#include <chrono>

#define TIME_LIMIT 1989999

chrono::time_point<chrono::high_resolution_clock> start_time;
int number_of_nodes;
double **distances;
double **nodes;
vector<int> path;

void exit() {
	for (size_t i = 0; i < number_of_nodes; i++) {
		delete[] nodes[i];
		delete[] distances[i];
	}
	delete[] nodes;
	delete[] distances;
}

int main(int argc, char const *argv[]) {
	ios::sync_with_stdio(false);
	start_time = chrono::high_resolution_clock::now();

	init_nodes(number_of_nodes, nodes, distances);

	calc_distances(number_of_nodes, nodes, distances);

	greedy(path, number_of_nodes, distances);

	auto now_time = chrono::high_resolution_clock::now();
	while(chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() < TIME_LIMIT) {
		double prev_distance = calc_total_distance(path, distances);
		opt2(path, distances, start_time, (double)TIME_LIMIT);
		double new_distance = calc_total_distance(path, distances);
		if(new_distance == prev_distance)
			break;
		now_time = chrono::high_resolution_clock::now();
	}

	print_path(path);
	
	now_time = chrono::high_resolution_clock::now();

	cerr << "Total distance = " << calc_total_distance(path, distances) << " , Total time = " << chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() << "\n";

	exit();
	return 0;
}
