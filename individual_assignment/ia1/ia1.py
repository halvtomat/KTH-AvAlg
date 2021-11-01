# Sample input
# genes = [a, b, c, d, e, f]
# obs = [[d, b, c], [a, c, f], [a, f, e], [f, b, a]]
# order = []
# 
# 

# obs1 = [a, b, c], obs2 = [c, a, f]
# obs3 = [a, b, f]

import random

def isCompatible(order = [], obs = []):
	i0 = order.index(obs[0])
	i1 = order.index(obs[1])
	i2 = order.index(obs[2])
	if (i0 < i1 and i1 < i2) or (i0 > i1 and i1 > i2):
		return True
	return False

def algorithm(genes = [], observations = []):
	order = genes
	ratio = 0
	runs = 0
	bestOrder = order
	bestRatio = ratio
	while runs < len(genes)**4:
		numCompatible = 0
		random.shuffle(order)
		for obs in observations:
			if isCompatible(order, obs):
				numCompatible += 1
		ratio = numCompatible/len(observations)
		if ratio > bestRatio:
			bestOrder = order
			bestRatio = ratio
		runs += 1
	print("runs = ", runs)
	print("ratio = ", bestRatio)
	return bestOrder