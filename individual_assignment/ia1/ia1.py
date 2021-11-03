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
	while ratio < 0.2:
		numCompatible = 0
		random.shuffle(order)
		for obs in observations:
			if isCompatible(order, obs):
				numCompatible += 1
		ratio = numCompatible/len(observations)
	return order