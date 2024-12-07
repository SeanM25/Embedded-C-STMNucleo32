# -*- coding: utf-8 -*-
"""
Created on Thu Aug  2 15:48:46 2018

@author: AutonomousSystemsLab

This explores various hashes that might be used to do the coin-flip commitment scheme.
The current system uses an XOR and then a shift-XOR, which is
a) really easy to manipulate (not necessarily a bad thing!)
b) confusing, since that means there are 3 XOR checksums in the lab
Lets look for a slightly better one.
"""

import matplotlib.pyplot as plt
import numpy as np

plt.close("all")

#%% How long does it take to iterate over all 16-bit numbers?
#for i in range(0,2**16):
#	k = i*i;

#%% Helpers:
def parity(x):
    parity = False
    while x:
        parity = not parity
        x = x & (x - 1)    
    return int(parity)

#%% SO DUMB, but can I get a list of primes in hex please:

if False:
	for i in range(0xAAAAA,0xBBBBB):
		prime = True
		for j in range (2,i):
			if i%j == 0:
				prime = False
				break
		if prime:
			print(hex(i))
#%% Not so long!  So we can do this crazy thing:
	
	


def check_quality(candidateHash):
	#okay, to analyze the quality of the result, first let's check the
		#distribution of the results:
	all_args = range(0,2**16)
	all_results = np.zeros([2**16],dtype=int);

	parities = [0,0]
	collision_dict = {arg:[] for arg in all_args}

	for i in all_args:
		result = candidateHash(i)
		all_results[i] = result
		parities[int(parity(result))]+=1
		collision_dict[result] += [i]
	
	biggest_collision = max(
			collision_dict.items(), 
			key = lambda x: len(x[1]))
	collision_distribution = [len(x[1])-1 for x in collision_dict.items()]
	max_collisions = len(biggest_collision[1])-1

	
	#let's look at each resulting bit:
	ones_per_bit = []
	bit_correlations = []
	for i in range(0,16):
		ones_count = sum([1 for r in all_results 
				if (r & (1<<i))])
		ones_per_bit.append(ones_count)
		#also check correlation between input bit and output bit
		bit_corrs_for_bit = np.zeros([2,2**16],dtype=int)
		for j in range(0,2**16):
			a_bit = 1 & (all_args[j] >> i)
			r_bit = 1 & (all_results[j] >> i)
			bit_corrs_for_bit[:,j] = [a_bit,r_bit]
		corr_mat = np.corrcoef(bit_corrs_for_bit)
		bit_correlations.append(corr_mat[0][1])
	


	#print out some info:
	print(candidateHash.__name__,":")
	print("   size of image:",str(len(list(set(all_results)))))
	print("   largest collision output was %d with %d collisions" % 
	  (biggest_collision[0], max_collisions))
	if max_collisions < 20:
		print("   ", biggest_collision[1])
	
	fig, axarr = plt.subplots(2,3)
	
	fig.tight_layout()	
	fig.subplots_adjust(top=0.9)
	
	fig.suptitle(candidateHash.__name__)
	
	axarr[0,0].set_title("distribution of image", fontsize=10)
	axarr[0,0].hist(all_results, bins=2**8)
	
	axarr[0,1].set_title("average ones per bit over image", fontsize=10)
	axarr[0,1].bar(np.arange(0,16),ones_per_bit)
	
	axarr[0,2].set_title("average parity of image", fontsize=10)
	axarr[0,2].bar([0,1],[p/sum(parities) for p in parities])
	
	axarr[1,0].set_title("collision distribution", fontsize=10)
	axarr[1,0].hist(collision_distribution)
	
	axarr[1,1].set_title("bit-wise correlations",fontsize=10)
	axarr[1,1].scatter(np.arange(0,16),bit_correlations,marker=".")
	
	axarr[1,2].set_title("biggest collision domain",fontsize=10)
	axarr[1,2].scatter([0 for x in biggest_collision[1]],
		 biggest_collision[1],marker=".")
	axarr[1,2].plot([0, 0],[0,0xFFFF]);
	
	plt.show()
	
	
#%%
def mult_hash(a):
	hash_a = (a * a) ;
	return hash_a & 0xFFFF;

def mod_hash_beef(a):
	hash_a = (a * a) % 0xBEEF;
	return hash_a & 0xFFFF;

def mod_hash_dead(a):
	hash_a = (a*a)  % 0xDEAD;
	return hash_a & 0xFFFF;

def missy_elliott_hash(a):
	take_it_down = (a>>1) | ((a & 1) << 15)
	flip_it = 0xFFFF ^ take_it_down
	reverse_it = 0
	while flip_it:
		reverse_it = (reverse_it << 1) + (flip_it & 1)
		flip_it >>= 1
	return a ^ reverse_it
	
def c_rand(a):
	a = (a * 1103515245) + 12345;
	return a & 0xFFFF;

def worst_hash(a):
	return a

for candidate in [
		mult_hash, 
		mod_hash_dead, 
		mod_hash_beef,
		missy_elliott_hash,
#		c_rand,
#		worst_hash,
		]:
	check_quality(candidate)
	
#%% find hash collisions:

def find_collision(hash):
	all_args = range(0,2**16)
	collision_dict = {arg:[] for arg in all_args}
	
	for i in all_args:
		result = hash(i)
		collision_dict[result] += [i]
	
	#now find biggest collision:
	biggest_collision = max(
			collision_dict.items(), 
			key = lambda x: len(x[1]))
	return biggest_collision
	
#coll = find_collision(mod_hash_beef)
#print( coll	)
#print([hex(x) for x in coll[1]])
	