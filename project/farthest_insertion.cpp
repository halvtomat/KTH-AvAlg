#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>

#define VERY_BIG 999999999999999999

using namespace std;

int number_of_nodes;
double **nodes;
double **distances;
vector<int> path;
vector<int> not_path;

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int farthest_node() {
	double prev_dist = 0;
	int max = -1;
	double sum_of_distances = 0;
	for (size_t i = 0; i < not_path.size(); i++) {
		sum_of_distances = 0;
		for (size_t j = 0; j < path.size(); j++)
			sum_of_distances += pow(distances[not_path[i]][path[j]], 2);
		double curr_dist = sqrt(sum_of_distances);
		if (curr_dist > prev_dist) {
			prev_dist = curr_dist;
			max = not_path[i];
		}
	}
	return max;
}

int farthest_node2() {
    double shortest_dist = VERY_BIG;
    double curr_dist = 0;
    double furthest_dist = -1;
    int furthest_node = -1;
    for (size_t i = 0; i < not_path.size(); i++) {
        for (size_t j = 0; j < path.size(); j++) {
            curr_dist = distances[not_path[i]][path[j]];
            if (curr_dist < shortest_dist)
                shortest_dist = curr_dist;
        }
        if(shortest_dist > furthest_dist) {
            furthest_dist = shortest_dist;
            furthest_node = not_path[i];
        }
    }
    return furthest_node;
}

int shortest_distance_node_in_path(int node) {
	double short_dist = VERY_BIG;
	double curr_dist = 0;
	int index = -1;
	for (size_t i = 0; i < path.size() - 1; i++) {
		curr_dist = distances[node][path[i]] + distances[node][path[i + 1]] - distances[path[i]][path[i + 1]];
		if (curr_dist < short_dist) {
			short_dist = curr_dist;
			index = i + 1;
		}
	}
	return index;
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
	for (size_t i = 0; i < number_of_nodes; i++) {
		not_path.push_back(i);
		nodes[i] = new double[2];
		distances[i] = new double[number_of_nodes];
		cin >> nodes[i][0];
		cin >> nodes[i][1];
	}
}

double calc_total_distance() {
	double total_distance = 0;
	for (size_t i = 0; i < path.size() - 1; i++)
		total_distance += distances[path[i]][path[i + 1]];
	return total_distance;
}

int main(int argc, char const *argv[]) {
	auto start_time = chrono::high_resolution_clock::now();
	init_nodes();
	
	if(number_of_nodes == 1) {
		cout << 0 << "\n";
		return 0;
	}
		

	double prev_dist = -1;
	int max_nodes[2] = {-1, -1};

    for (size_t i = 0; i < number_of_nodes; i++) {
        for (size_t j = i + 1; j < number_of_nodes; j++) {
			if(i == j) {
				distances[i][j] = 0;
				continue;
			}
            double curr_dist = distance(nodes[i][0], nodes[i][1], nodes[j][0], nodes[j][1]);
            distances[i][j] = curr_dist;
			distances[j][i] = curr_dist;
            if (curr_dist > prev_dist) {
                prev_dist = curr_dist;
                max_nodes[0] = i;
                max_nodes[1] = j;
            }
        }
    }
	path.push_back(max_nodes[0]);
	path.push_back(max_nodes[1]);
	not_path.erase(remove(not_path.begin(), not_path.end(), max_nodes[0]), not_path.end());
	not_path.erase(remove(not_path.begin(), not_path.end(), max_nodes[1]), not_path.end());
	int farthest = farthest_node2();
	path.push_back(farthest);
	not_path.erase(remove(not_path.begin(), not_path.end(), farthest), not_path.end());

	while(not_path.size() > 0) {
		farthest = farthest_node2();
		int index = shortest_distance_node_in_path(farthest);
		path.insert(path.begin() + index, farthest);
		not_path.erase(remove(not_path.begin(), not_path.end(), farthest), not_path.end());
	}

	//cout << "Total distance = " << calc_total_distance() << "\n";
	auto now_time = chrono::high_resolution_clock::now();
	while(chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() < 1989999) {
		now_time = chrono::high_resolution_clock::now();
	}
	for (size_t i = 0; i < path.size(); i++)
		cout << path[i] << "\n";

	exit();
	return 0;
}
