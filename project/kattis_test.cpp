#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <chrono>

using namespace std;

#define TIME_LIMIT 1989999

chrono::time_point<chrono::high_resolution_clock> start_time;
int number_of_nodes;
double **distances;
double **nodes;
vector<int> path;

double calc_total_distance(vector<int> &path, double **&distances) {
	double total_distance = 0;
	for (size_t i = 0; i < path.size() - 1; i++)
		total_distance += distances[path[i]][path[i + 1]];
	total_distance += distances[path[0]][path[path.size() - 1]];
	return total_distance;
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void calc_distances(int number_of_nodes, double **&nodes, double **&distances) {
	for (size_t i = 0; i < number_of_nodes; i++) {
        for (size_t j = i + 1; j < number_of_nodes; j++) {
            double curr_dist = distance(nodes[i][0], nodes[i][1], nodes[j][0], nodes[j][1]);
            distances[i][j] = curr_dist;
			distances[j][i] = curr_dist;
        }
    }
}

void init_nodes(int &number_of_nodes, double **&nodes, double**&distances) {
	cin >> number_of_nodes;
	nodes = new double*[number_of_nodes];
	distances = new double*[number_of_nodes];
	for (size_t i = 0; i < number_of_nodes; i++) {
		nodes[i] = new double[2];
		distances[i] = new double[number_of_nodes];
		cin >> nodes[i][0];
		cin >> nodes[i][1];
	}
}

void print_path(vector<int> &path) {
	for (size_t i = 0; i < path.size(); i++)
		cout << path[i] << "\n";
}

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

void opt2(vector<int> &path, double **& distances, chrono::time_point<chrono::high_resolution_clock> start_time) {
	for (size_t i = 0; i < path.size() - 2; i++) {
		for (size_t j = i + 1; j < path.size(); j++) {
			opt2_swap(i, j, path, distances);
			auto now_time = chrono::high_resolution_clock::now();
			if(chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() >= TIME_LIMIT)
				return;
		}
	}
}

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
		opt2(path, distances, start_time);
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