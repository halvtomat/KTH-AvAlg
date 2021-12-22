#!/usr/bin/env python3
import random
import numpy as np
import sys

def find_path(graph, k, final_path):
	colors = k
	graph_color = []
	queue = []
	path = []
	for i in range(7):
		path.append(-1)
		graph_color.append(random.randint(0,colors - 1))
		if graph_color[i] == 0:
			queue.append(i)
	
	visited = []
	while len(queue) > 0:
		a = queue.pop()
		visited.append(a)
		for x in graph[a]:
			if graph_color[x] == graph_color[a] + 1 and not visited.__contains__(x):
				queue.append(x)
				path[x] = a
				if graph_color[x] == colors - 1:
					final_path.append(x)
					for _ in range(0,colors - 1):
						x = path[x]
						final_path.append(x)
					final_path.reverse()
					return True
	return False

def main():
	x = int(sys.argv[1])
	k = 6
	graph = []
	graph.append([3])
	graph.append([4])
	graph.append([0])
	graph.append([1, 5, 6])
	graph.append([])
	graph.append([2])
	graph.append([4, 5])
	counter = 0
	paths = []
	for _ in range(0, x):
		path = []
		if find_path(graph, k, path):
			counter += 1
			if len(paths) == 0:
				paths.append(np.array(path))
			else:
				contains = False
				for p in paths:
					if np.array_equiv(p, np.array(path)):
						contains = True
				if not contains:
					paths.append(np.array(path))
	expected = 3 * ((1/k)**k) - ((1/k)**(k+1))
	print("counter = ", counter)
	print("probability = ", counter/x)
	print("expected counter = ", round(x * expected))
	print("expected probability = ", expected)
	print("\nUNIQUE PATHS\n")
	for p in paths:
		print(p)

if __name__ == "__main__":
	main()