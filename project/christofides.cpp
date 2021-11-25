#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#define VERY_BIG 999999999999999999

using namespace std;

int number_of_nodes;
double **nodes;
double **distances;
vector<int> path;
vector<int> *adjacency_list;
vector<int> odd_degree;

double calc_total_distance() {
	double total_distance = 0;
	for (size_t i = 0; i < path.size() - 1; i++)
		total_distance += distances[path[i]][path[i + 1]];
	total_distance += distances[path[0]][path[path.size() - 1]];
	return total_distance;
}

void print_path() {
	for (size_t i = 0; i < path.size(); i++)
		cout << path[i] << "\n";
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
	delete[] adjacency_list;
}

int closest_node(int key[], bool mst[]) { //getMinIndex
	int min = VERY_BIG;
	int closest;
	for(size_t i = 0; i < number_of_nodes; i++)
		if(!mst[i] && key[i] < min) {
			min = key[i];
			closest = i;
		}
	return closest;
}

void find_odd_degree() { //findOdds
	for (size_t i = 0; i < number_of_nodes; i++)
		if((adjacency_list[i].size() % 2) != 0)
			odd_degree.push_back(i);
}

void perfect_matching() {
	int closest;
	int length;
	vector<int>::iterator temp, first, iterator, last;

	find_odd_degree();

	while(!odd_degree.empty()) {
		first = odd_degree.begin();
		iterator = first + 1;
		last = odd_degree.end();
		length = VERY_BIG;
		for(; iterator != last; iterator++)
			if(distances[*first][*iterator] < length) {
				length = distances[*first][*iterator];
				closest = *iterator;
				temp = iterator;
			}
	}
	adjacency_list[*first].push_back(closest);
	adjacency_list[closest].push_back(*first);
	odd_degree.erase(temp);
	odd_degree.erase(first);
}

void init_mst() { //findMST
    int *key = new int[number_of_nodes];
    int *parent = new int[number_of_nodes];
    bool *nodes_in_tree = new bool[number_of_nodes];

    for (size_t i = 0; i < number_of_nodes; i++) {
        key[i] = VERY_BIG;
        nodes_in_tree[i] = false;
    }
    key[0] = 0;
    parent[0] = -1;

    for (size_t i = 0; i < number_of_nodes - 1; i++) {
        int a = closest_node(key, nodes_in_tree);
        nodes_in_tree[a] = true;
        
        for (size_t j = 0; j < number_of_nodes; j++) {
            if(distances[a][j] && nodes_in_tree[j] == false && distances[a][j] < key[j])
            parent[j] = a;
            key[j] = distances[a][j];
        }
    }
      for (int i = 0; i < number_of_nodes; i++) {
        int b = parent[i];
        
        if (b != -1) {
        adjacency_list[i].push_back(b);
        adjacency_list[b].push_back(i);
        }
    }
}

void euler_tour(int start, vector<int> &path) {
	
}

void init_nodes() {
	cin >> number_of_nodes;
	nodes = new double*[number_of_nodes];
	distances = new double*[number_of_nodes];
	adjacency_list = new vector<int>[number_of_nodes];
	for (size_t i = 0; i < number_of_nodes; i++) {
		path.push_back(i);
		nodes[i] = new double[2];
		distances[i] = new double[number_of_nodes];
		cin >> nodes[i][0];
		cin >> nodes[i][1];
	}
}

void init_distances() {
	for (size_t i = 0; i < number_of_nodes; i++) {
        for (size_t j = i + 1; j < number_of_nodes; j++) {
            double curr_dist = distance(nodes[i][0], nodes[i][1], nodes[j][0], nodes[j][1]);
            distances[i][j] = curr_dist;
			distances[j][i] = curr_dist;
        }
    }
}

int main(int argc, char const *argv[]) {
	init_nodes();
	
	if(number_of_nodes == 1) {
		cout << 0 << "\n";
		return 0;
	}

	init_distances();

	cout << "Total distance = " << calc_total_distance() << "\n";

	//print_path();

	exit();
	return 0;
}
