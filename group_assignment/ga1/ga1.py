#1 = 0
#2 = 1
#3 = 3
#4 = 6
#5 = 10
#6 = 15
#7 = 21
#f(x) = f(x-1) + x-1

import random

def algorithm(n,k):
	variables = []
	for i in range(n):
		variables.append(random.randint(1,k))
	inequalites = 0
	for i in range(n):
		for j in range(i,n):
			if i == j:
				continue
			if variables[i] != variables[j]:
				inequalites += 1
	return inequalites

# 1 2 1 2, 4