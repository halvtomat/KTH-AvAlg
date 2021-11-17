#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#define VERY_BIG 999999999999999999
#define TIME_LIMIT 30000000//1989999

using namespace std;

chrono::time_point<chrono::high_resolution_clock> start_time;
int number_of_nodes;
double **nodes;
double **distances;
double temp;
vector<int> path;
vector<int> opt_path;

double calc_total_distance() {
	double total_distance = 0;
	for (size_t i = 0; i < path.size() - 1; i++)
		total_distance += distances[path[i]][path[i + 1]];
	total_distance += distances[path[0]][path[path.size() - 1]];
	return total_distance;
}

double calc_total_distance_opt() {
	double total_distance = 0;
	for (size_t i = 0; i < opt_path.size() - 1; i++)
		total_distance += distances[opt_path[i]][opt_path[i + 1]];
	total_distance += distances[opt_path[0]][opt_path[opt_path.size() - 1]];
	return total_distance;
}

void opt2_swap(int a, int b) {
	for (size_t i = 0; i < a; i++)
		opt_path[i] = path[i];
	for (size_t i = a; i < b + 1; i++)
		opt_path[i] = path[a + b - i];
	for (size_t i = b + 1; i < path.size(); i++)
		opt_path[i] = path[i];
	double c = calc_total_distance() - calc_total_distance_opt();
	if(c <= 0 || (rand() / (RAND_MAX)) > exp(-c/temp)) {
		for (size_t i = 0; i < path.size(); i++)
			path[i] = opt_path[i];
	}
	cout << calc_total_distance() << " , temp = " << temp << " , c =" << c << "\n";
}



void print_path() {
	for (size_t i = 0; i < path.size(); i++)
		cout << path[i] << "\n";
}

void opt2() {
	for (size_t i = 0; i < path.size() - 2; i++) {
		for (size_t j = i + 1; j < path.size(); j++) {
			opt2_swap(i, j);
			auto now_time = chrono::high_resolution_clock::now();
			if(chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() >= TIME_LIMIT)
				return;
		}
	}
	if(temp > 0.01)
		temp -= 0.0001;
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void exit() {
	for (size_t i = 0; i < number_of_nodes; i++) {
		delete[] nodes[i];
		delete[] distances[i];
	}
	delete[] nodes;
	delete[] distances;
}

void init_nodes() {
	cin >> number_of_nodes;
	nodes = new double*[number_of_nodes];
	distances = new double*[number_of_nodes];
	temp = 1.0;
	for (size_t i = 0; i < number_of_nodes; i++) {
		path.push_back(i);
		opt_path.push_back(i);
		nodes[i] = new double[2];
		distances[i] = new double[number_of_nodes];
		cin >> nodes[i][0];
		cin >> nodes[i][1];
	}
}



int main(int argc, char const *argv[]) {
	start_time = chrono::high_resolution_clock::now();
	init_nodes();
	
	if(number_of_nodes == 1) {
		cout << 0 << "\n";
		return 0;
	}

    for (size_t i = 0; i < number_of_nodes; i++) {
        for (size_t j = i + 1; j < number_of_nodes; j++) {
            double curr_dist = distance(nodes[i][0], nodes[i][1], nodes[j][0], nodes[j][1]);
            distances[i][j] = curr_dist;
			distances[j][i] = curr_dist;
        }
    }

	default_random_engine rng(start_time.time_since_epoch().count());
	shuffle(begin(path), end(path), rng);

	auto now_time = chrono::high_resolution_clock::now();
	while(chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() < TIME_LIMIT) {
		opt2();
		now_time = chrono::high_resolution_clock::now();
	}

	cout << "Total distance = " << calc_total_distance() << "\n";

	//print_path();

	exit();
	return 0;
}
