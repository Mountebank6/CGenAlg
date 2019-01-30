#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

#define True 1
#define False 0

int CHESSBOARD_SIZE = 8;

/* 
 * Take in two queens and return True if they threaten each other
 * and False otherwise
 */
int Threaten(int x_1, int y_1, int x_2, int y_2){
        if(x_1 == x_2 || y_1 == y_2){
                return True;
        }
        //Figure out how to look for diagonals                
}


int Min(int A, int B){
        if (A <= B){
                return A;
        } else {
                return B;
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
        
        pop = temp;
        
        return pop;
}



/*
 * Take in a population of chessboards and sort them based on the sum 
 * of queens threatened by each queen
 */
void ViolateScore(int** pop, int pop_size){
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
                        for (int k=j+1; k<CHESSBOARD_SIZE; k++){
                                if (Threaten(pop[i][j*2], pop[i][j*2+1],
                                            pop[i][k*2], pop[i][k*2+1])){
                                 
                                       score += 1;
                                }
                        }
                }
                score_list[i][0] = score;
        }
        
        pop = Sort(pop, pop_size, score_list);
        free(score_list);
        return;
}     


int main(){
        int** test_pop = (int**) malloc(sizeof(int*)*4);
        for (int i=0; i<4; i++){
                int* sub = (int*) malloc(sizeof(int*));
                sub[0] = i;
                test_pop[i] = sub;
        }
        
        int** sco = (int**) malloc(sizeof(int*)*4);
        for (int i=0; i<4; i++){
                int* sub = (int*) malloc(sizeof(int*));
                sub[0] = 0;
                sub[1] = i;
                sco[i] = sub;
        }
        sco[0][0] = 3;
        sco[1][0] = 1;
        sco[2][0] = 2;
        sco[3][0] = 4;

        printf("Values of test_pop at initialization\n");
        for (int i=0; i<3; i++){
                printf("%d, ", test_pop[i][0]);
        }
        printf("%d \n", test_pop[3][0]);
        test_pop = Sort(test_pop, 4, sco);
        
        printf("Values of test_pop after ordering\n");
        for (int i=0; i<3; i++){
                printf("%d, ", test_pop[i][0]);
        }
        printf("%d \n", test_pop[3][0]);
        return 0;
}
