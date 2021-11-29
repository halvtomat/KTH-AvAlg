#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <stack>
#include "helper.h"
#include "opt2.h"

#define VERY_BIG numeric_limits<int>::max()
#define TIME_LIMIT 1989999

using namespace std;

chrono::time_point<chrono::high_resolution_clock> start_time;
int number_of_nodes;
double **nodes;
double **distances;
vector<int> *adjacency_list;
vector<int> odd_degree;

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
	vector<int>::iterator tempi, first, iterator, last;

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
				tempi = iterator;
			}	
	adjacency_list[*first].push_back(closest);
	adjacency_list[closest].push_back(*first);
	odd_degree.erase(tempi);
	odd_degree.erase(first);
	}
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
	vector<int> *tempv = new vector<int>[number_of_nodes];
	for (size_t i = 0; i < number_of_nodes; i++){
		tempv[i].resize(adjacency_list[i].size());
		tempv[i] = adjacency_list[i];
	}
	
	stack<int> stack;
	int index = start;
	path.push_back(start);
	while(!stack.empty() || tempv[index].size() > 0) {
		if(tempv[index].empty()) {
			path.push_back(index);
			index = stack.top();
			stack.pop();
		} else {
			stack.push(index);
			int neighbor = tempv[index].back();
			tempv[index].pop_back();
			for (size_t i = 0; i < tempv[neighbor].size(); i++)
				if(tempv[neighbor][i] == index)
					tempv[neighbor].erase(tempv[neighbor].begin() + i);
			index = neighbor;
		}
	}
	path.push_back(index);
}

void hamilton(vector<int> &path) {
	bool *visited = new bool[number_of_nodes];
	for (size_t i = 0; i < number_of_nodes; i++)
		visited[i] = 0;

	int root = path.front();
	visited[root] = 1;

	vector<int>::iterator current = path.begin();
	vector<int>::iterator iterator = current + 1;

	bool addMore = true;
	while(iterator != path.end()) {
		if(!visited[*iterator]) {
			current = iterator;
			visited[*current] = 1;
			iterator = current + 1;
		} else 
			iterator = path.erase(iterator);
	}
}



int main(int argc, char const *argv[]) {
	ios::sync_with_stdio(false);
	start_time = chrono::high_resolution_clock::now();
	init_nodes(number_of_nodes, nodes, distances);
	adjacency_list = new vector<int>[number_of_nodes];
	
	if(number_of_nodes == 1) {
		cout << 0 << "\n";
		return 0;
	}

	calc_distances(number_of_nodes, nodes, distances);

	init_mst();

	perfect_matching();

	int best_start = 0;
	double best_dist = VERY_BIG;
	for (size_t i = 0; i < number_of_nodes; i++) {
		vector<int> path;
		euler_tour(i, path);
		hamilton(path);
		double dist = calc_total_distance(path, distances);
		if(dist < best_dist)
			best_start = i;
	}
	
	vector<int> path;
	euler_tour(best_start, path);

	hamilton(path);

	auto now_time = chrono::high_resolution_clock::now();
	while(chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() < TIME_LIMIT) {
		opt2(path, distances);
		now_time = chrono::high_resolution_clock::now();
	}

	cerr << "Total distance = " << calc_total_distance(path, distances) << " , Total time = " << chrono::duration_cast<chrono::microseconds>(now_time - start_time).count() << "\n";

	//print_path(path);

	exit();
	return 0;
}