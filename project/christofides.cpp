#include "christofides.h"

int closest_node(int number_of_nodes,int key[], bool mst[]) {
	int min = numeric_limits<int>::max();
	int closest;
	for(size_t i = 0; i < number_of_nodes; i++)
		if(!mst[i] && key[i] < min) {
			min = key[i];
			closest = i;
		}
	return closest;
}

void find_odd_degree(int number_of_nodes, vector<int> &odd_degree, vector<int> *&adjacency_list) {
	for (size_t i = 0; i < number_of_nodes; i++)
		if((adjacency_list[i].size() % 2) != 0)
			odd_degree.push_back(i);
}

void perfect_matching(int number_of_nodes, double **&distances, vector<int> &odd_degree, vector<int> *&adjacency_list) {
	int closest;
	int length;
	vector<int>::iterator tempi, first, iterator, last;

	find_odd_degree(number_of_nodes, odd_degree, adjacency_list);

	while(!odd_degree.empty()) {
		first = odd_degree.begin();
		iterator = first + 1;
		last = odd_degree.end();
		length = numeric_limits<int>::max();
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

void init_mst(int number_of_nodes, double **&distances, vector<int> *&adjacency_list) {
    int *key = new int[number_of_nodes];
    int *parent = new int[number_of_nodes];
    bool *nodes_in_tree = new bool[number_of_nodes];

    for (size_t i = 0; i < number_of_nodes; i++) {
        key[i] = numeric_limits<int>::max();
        nodes_in_tree[i] = false;
    }
    key[0] = 0;
    parent[0] = -1;

    for (size_t i = 0; i < number_of_nodes - 1; i++) {
        int a = closest_node(number_of_nodes, key, nodes_in_tree);
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

void euler_tour(vector<int> &path, int number_of_nodes, int start, vector<int> *&adjacency_list) {
	vector<int> *tempv = new vector<int>[number_of_nodes];
	for (size_t i = 0; i < number_of_nodes; i++) {
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

void hamilton(vector<int> &path, int number_of_nodes) {
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

void christofides(vector<int> &path, int number_of_nodes, double **&distances) {
	vector<int> *adjacency_list = new vector<int>[number_of_nodes];
	vector<int> odd_degree;
	init_mst(number_of_nodes, distances, adjacency_list);
	perfect_matching(number_of_nodes, distances, odd_degree, adjacency_list);
	int best_start = 0;
	double best_dist = numeric_limits<int>::max();
	for (size_t i = 0; i < number_of_nodes; i++) {
		euler_tour(path, number_of_nodes, i, adjacency_list);
		hamilton(path, number_of_nodes);
		double dist = calc_total_distance(path, distances);
		if(dist < best_dist)
			best_start = i;
	}
	euler_tour(path, number_of_nodes, best_start, adjacency_list);
	hamilton(path, number_of_nodes);

	delete[] adjacency_list;
}