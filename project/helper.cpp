#include "helper.h"

double calc_total_distance(vector<int> &path, double **&distances) {
	double total_distance = 0;
	for (size_t i = 0; i < path.size() - 1; i++)
		total_distance += distances[path[i]][path[i + 1]];
	total_distance += distances[path[path.size() - 1]][path[0]];
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