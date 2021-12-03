#include "opt2.h"

void opt2_swap(int a, int b, vector<int> &path, double **&distances) {
	int afterB = b == path.size() - 1 ? 0 : b + 1;
	int afterA = a == path.size() - 1 ? 0 : a + 1;
	double c = (distances[path[a]][path[b]] + distances[path[afterA]][path[afterB]]) - 
		(distances[path[a]][path[afterA]] + distances[path[b]][path[afterB]]);
	if(c < 0) {
		vector<int> opt_path;
		for (size_t i = 0; i < a + 1; i++)
			opt_path.push_back(path[i]);
		for (size_t i = a + 1; i < b + 1; i++)
			opt_path.push_back(path[a + 1 + b - i]);
		for (size_t i = b + 1; i < path.size(); i++)
			opt_path.push_back(path[i]);
		for (size_t i = 0; i < path.size(); i++)
			path[i] = opt_path[i];
	}
}

void opt2(vector<int> &path, double **&distances, chrono::time_point<chrono::high_resolution_clock> start_time, double time_limit) {
	for (size_t i = 0; i < path.size() - 2; i++) {
		for (size_t j = i + 1; j < path.size(); j++) {
			opt2_swap(i, j, path, distances);
			auto now_time = chrono::high_resolution_clock::now();
			if(chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() >= time_limit)
				return;
		}
	}
}

void opt2_swap_annealing(int a, int b, vector<int> &path, double **&distances, double temp) {
	int afterB = b == path.size() - 1 ? 0 : b + 1;
	int afterA = a == path.size() - 1 ? 0 : a + 1;
	double c = (distances[path[a]][path[b]] + distances[path[afterA]][path[afterB]]) - 
		(distances[path[a]][path[afterA]] + distances[path[b]][path[afterB]]);
	if(c < 0 || ((double) rand() / (RAND_MAX)) < exp(-(abs(c)/temp))) {
		vector<int> opt_path;
		for (size_t i = 0; i < a + 1; i++)
			opt_path.push_back(path[i]);
		for (size_t i = a + 1; i < b + 1; i++)
			opt_path.push_back(path[a + 1 + b - i]);
		for (size_t i = b + 1; i < path.size(); i++)
			opt_path.push_back(path[i]);
		for (size_t i = 0; i < path.size(); i++)
			path[i] = opt_path[i];
	}
}

void opt2_annealing(vector<int> &path, double **&distances, chrono::time_point<chrono::high_resolution_clock> start_time, double time_limit, double &temp) {
	for (size_t i = 0; i < path.size() - 2; i++) {
		for (size_t j = i + 1; j < path.size(); j++) {
			opt2_swap_annealing(i, j, path, distances, temp);
			auto now_time = chrono::high_resolution_clock::now();
			if(chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() >= time_limit)
				return;
		}
	}
	if(temp > 0)
		temp /= 1.1;
	if(temp < 0)
		temp = 0;
}