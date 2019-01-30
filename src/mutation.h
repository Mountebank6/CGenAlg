#ifndef MUTATION_H_
#define MUTATION_H_

/*
 * Control population-level breeding
 */

int** BreedPop(int** pop, int genome_len, int inverse_mut_prob, 
	       int crossover_num, int** gene_ranges, int pop_size);

void BreedPair(int* par_a, int* par_b, int** pop, int genome_len,
	       int inverse_mut_prob, int crossover_num, int** gene_ranges,
	       int pop_size, int pair_num);

int** GenPop(int genome_len, int inverse_mut_prob, 
	     int crossover_num, int** gene_ranges, int pop_size);

#endif
