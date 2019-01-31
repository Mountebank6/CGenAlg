#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

#define True 1
#define False 0

int CHESSBOARD_SIZE = 8;

/* 
 * Take in two queens and return True if they threaten each other
 * and False otherwise
 */
int Threaten(int x_1, int y_1, int x_2, int y_2){
        //Detect queens being in the same spot
        if (x_1 == x_2 && y_1 == y_2){
                return -1; 
        }
        //If on the same horiz or vert axis
        if (x_1 == x_2 || y_1 == y_2){
                return True;
        }
        //Check if abs val of differences are equal (diagonal check)
        x_1 = abs(x_1 - x_2);
        y_1 = abs(y_1 - y_2);
        if (x_1 == y_1){
                return True;
        } else {
                return False;
        }            
}


int Min(int A, int B){
        if (A <= B){
                return A;
        } else {
                return B;
        }
}


void print_pop(int** population, int pop_size){
	int gene_size = 2*CHESSBOARD_SIZE;

        for (int i=0; i<pop_size; i++){
                printf("Gene Number %d: ",i+1);
                int every_other = 0;
                
		for (int j=0; j<gene_size; j++){
                        if (every_other){
                                printf("%d ", population[i][j]);
                        } else {
                                printf("%d,", population[i][j]);
                        }
                        every_other ^= 1;
                }
                printf("\n");
        }
}


/*
 * Takes a population and a list of scores and returns a sorte
 */
int** Sort(int** pop, int pop_size, int** scores){
        int** temp = (int**) malloc(sizeof(int*)*pop_size);
        for (int i=0; i<pop_size; i++){
                int* tuple = (int*) malloc(sizeof(int)*2);
                temp[i] = tuple;
                tuple[0] = INT_MAX;
                tuple[1] = i;
        }

        void CopyArray(int** B, int** A, int n){
                for (int i=0; i<n; i++){
                        A[i] = B[i];
                }
        }
        
        void BottomUpMerge(int** A, int iL, int iR, int iEnd, int** B){
                int i = iL, j = iR;
                for (int k=iL; k<iEnd; k++){
                        if (i < iR && (j >= iEnd || A[i][0] <= A[j][0])){
                                B[k] = A[i];
                                i += 1;
                        } else {
                                B[k] = A[j];
                                j += 1;
                        }
                }
        }

        for (int w=1; w<pop_size; w=2*w){
                for (int i=0; i<pop_size; i=i+2*w){
                        BottomUpMerge(scores, i, Min(i+w, pop_size),
                                      Min(i+2*w, pop_size), temp);
                }
                CopyArray(temp, scores, pop_size);
        }
       
        int k;
        for (int i=0; i<pop_size; i++){
                int* remove = temp[i];
                k = scores[i][1];
                temp[i] = pop[k];
                free(remove);
        }
             
        return temp;
}



/*
 * Take in a population of chessboards and sort them based on the sum 
 * of queens threatened by each queen
 */
int** ViolateScore(int** pop, int pop_size){
        int** score_list = (int**) malloc(sizeof(int*)*pop_size);
        int score;
        for (int i=0; i<pop_size; i++){
                int* temp = (int*) malloc(sizeof(int)*2);
                score_list[i] = temp;
                score_list[i][0] = INT_MAX;
                score_list[i][1] = i;
        }

        for (int i=0; i<pop_size; i++){
                score = 0;
                for (int j=0; j<CHESSBOARD_SIZE; j++){
                        //Create a flag to catch impossible boards
                        int threaten_flag; 
                        for (int k=j+1; k<CHESSBOARD_SIZE; k++){
                                threaten_flag = Threaten(pop[i][j*2], pop[i][j*2+1],
                                            pop[i][k*2], pop[i][k*2+1]); 
                                if (threaten_flag == -1){
                                       score = INT_MAX;
                                       break;
                                } else if (threaten_flag){
                                       score += 1;
                                }
                        }
                        //Make the default true value the likely case
                        if (threaten_flag != -1){
                                continue;
                        } else {
                                break;
                        }
                }	
                score_list[i][0] = score;
        }
        pop = Sort(pop, pop_size, score_list);
        free(score_list);
        return pop;
}     


void rand_gene(int* gene, int length){
        for (int i=0; i<length; i++){
                gene[i] = rand() % 7;
        }
}


int main(){
        int** test_pop = (int**) malloc(sizeof(int*)*4);
        for (int i=0; i<4; i++){
                int* sub = (int*) malloc(sizeof(int*)*16);
                sub[0] = i;
                test_pop[i] = sub;
        }
        srand(time(NULL));        
        for(int i=0; i<4; i++){
                rand_gene(test_pop[i], 16);
        }
        print_pop(test_pop, 4);
        printf("######################\n");
        test_pop = ViolateScore(test_pop, 4);
        print_pop(test_pop, 4);
}
