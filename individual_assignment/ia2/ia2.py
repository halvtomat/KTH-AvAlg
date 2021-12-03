#!/usr/bin/env python3

from numpy import random, ones, zeros
import sys


class Dict:
	d = {}
	k = 0

	def __init__(self, k):
		self.k = k
		self.d = {}

	def add(self, x):
		self.d[x] = 1

	def remove(self, x):
		del self.d[x]

	def decr(self):
		for x in self.d:
			self.d[x] -= 1
		self.d = {key:val for key, val in self.d.items() if val != 0}

	def incr(self, x):
		self.d[x] += 1

	def next(self, x):
		if self.d.__contains__(x):
			self.incr(x)
		elif len(self.d) < self.k - 1:
			self.add(x)
		else:
			self.decr()
	
	def get_value(self, x):
		return self.d[x]
	
def misra_gries(stream):
	dict = Dict(100)
	for x in stream:
		dict.next(x)
	for x in dict.d:
		if dict.get_value(x) > len(stream)/2:
			print("Majority element = ", x)
			return
	print("No majority")

def controll(stream):
	id = -1
	count = 0
	for x in stream:
		if id == -1:
			id = x
			count = 1
		elif id == x:
			count += 1
		elif count == 1:
			count = 0
			id = -1
		else:
			count -= 1
	count = 0
	for x in stream:
		if x == id:
			count += 1
	if count > len(stream)/2:
		print("Majority element = ", id, " , with count = ", count)
	else:
		print("No majority element!")


def main():
	n = int(sys.argv[1])
	m = int(sys.argv[2])
	ratio = 506/1000
	inv_ratio = 1 - ratio
	stream = [*zeros(int(m * ratio), dtype=int), *random.randint(1, n, int(m * inv_ratio))]
	random.shuffle(stream)	
	misra_gries(stream)
	#controll(stream)

if __name__ == "__main__":
	main()