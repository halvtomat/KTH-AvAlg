#include "greedy.h"

void greedy(vector<int> &path, int number_of_nodes, double **&distances) {
	bool in_path[number_of_nodes] = { false };
	int next, prev;
	double best_distance;
	in_path[0] = true;
	prev = 0;
	path.push_back(0);
	for (size_t i = 1; i < number_of_nodes; i++) {
		next = -1;
		best_distance = numeric_limits<double>::max();
		for (size_t j = 1; j < number_of_nodes; j++) {
			if(!in_path[j] && (next == -1 || distances[prev][j] < best_distance)) {
				best_distance = distances[prev][j];
				next = j;
			}
		}
		prev = next;
		path.push_back(next);
		in_path[next] = true;
	}
}