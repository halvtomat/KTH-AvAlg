#include "opt2.h"

void opt2_swap(int a, int b, vector<int> &path, double **& distances) {
	vector<int> opt_path;
	for (size_t i = 0; i < a; i++)
		opt_path.push_back(path[i]);
	for (size_t i = a; i < b + 1; i++)
		opt_path.push_back(path[a + b - i]);
	for (size_t i = b + 1; i < path.size(); i++)
		opt_path.push_back(path[i]);
	double c = calc_total_distance(opt_path, distances) - calc_total_distance(path, distances);
	if(c < 0) {
		for (size_t i = 0; i < path.size(); i++)
			path[i] = opt_path[i];
	}
}

void opt2(vector<int> &path, double **& distances, chrono::time_point<chrono::high_resolution_clock> start_time, double TIME_LIMIT) {
	for (size_t i = 0; i < path.size() - 2; i++) {
		for (size_t j = i + 1; j < path.size(); j++) {
			opt2_swap(i, j, path, distances);
			auto now_time = chrono::high_resolution_clock::now();
			if(chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() >= TIME_LIMIT)
				return;
		}
	}
}