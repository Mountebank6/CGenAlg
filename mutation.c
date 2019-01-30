#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


int** GenPop(int genome_len, int** gene_ranges, int pop_size){
	assert(pop_size % 4 == 0);

	int** pop = (int**) malloc(sizeof(int*)*pop_size);
	for (int i=0;i<pop_size;i++) {
		pop[i] = (int*) malloc(sizeof(int)*genome_len);
		for (int j=0;j<genome_len;j++) {
			pop[i][j] = (rand() % (gene_ranges[j][1]-gene_ranges[j][0]))
				    + gene_ranges[j][0];
		}
	}

	return pop;
}


void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int compare (const void * a, const void * b){
	//Return positive if a>b, 0 if a ==b, negative otherwise
	return ( *(int*)a - *(int*)b );
	}

void BreedPair(int* par_a, int* par_b, int** pop, int genome_len,
	       int inverse_mut_prob, int crossover_num, int** gene_ranges,
	       int pop_size, int child_a_destination, int child_b_destination){
// Take Parents, cross them over, mutate a bit and plop the children 
	
	//setup
	int n = genome_len - 1;
	assert(crossover_num < n);
	assert(child_a_destination<pop_size);
	assert(child_b_destination<pop_size);
	
	//Generate a shuffled list of possible crossover locations
	//Later we take the first N (N is randomly selected) elements of this list
	//sort them and crossover there
	int* shuffle_locs = (int*) malloc(sizeof(int)*(n));
	for(int i=1;i<n;i++){
		shuffle_locs[i]=i+1;
			    }
	//the +1 is because it makes no sense to crossover at the zeroth index
	//Since n is the highest index of genome the legal crossover are indexes:
	//1, 2, ..., n 
	shuffle(shuffle_locs, n);
	
	int* cross_locs = (int*) malloc(sizeof(int)*crossover_num);
	for (int i=0;i<crossover_num;i++){
		cross_locs[i] = shuffle_locs[i];
					 }
	qsort(cross_locs,crossover_num,sizeof(int),compare);
	//Now cross_locs is a sorted list of crossover locations	
	
	//Gen the kids.
	int* child_a = (int*) malloc(sizeof(int)*genome_len);
	int* child_b = (int*) malloc(sizeof(int)*genome_len);
	

	//fill in the kids and perform crossover
	int toggle = 1;
	int rolling_index = 0;
	for (int i=0;i<genome_len;i++){
		if (i < cross_locs[rolling_index]){
			if(toggle>0){
				child_a[i] = par_a[i];
				child_b[i] = par_b[i];
				}
			else{
                                child_a[i] = par_b[i];
                                child_b[i] = par_a[i];

				}
			}
		else if (i==cross_locs[rolling_index]){
			toggle = toggle*(-1);
			if(toggle>0){
                                child_a[i] = par_a[i];
                                child_b[i] = par_b[i];
                                }
                        else{
                                child_a[i] = par_b[i];
                                child_b[i] = par_a[i];
                                }
			}
		else{printf("invalid crossover location %d", cross_locs[rolling_index]);}
	}
	
	//Write the childen to their designated locations
	
	free(pop[child_a_destination]);
	pop[child_a_destination] = child_a;
	free(pop[child_b_destination]);
	pop[child_b_destination] = child_b;

	free(cross_locs);
	free(shuffle_locs);
}
	

int main(){
	return 4;
}

