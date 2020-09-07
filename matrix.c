#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){

// 문자형 a,b,c 받아서 int형으로 변환
    int a = atoi(*(argv + 1));
    int b = atoi(*(argv + 2));
    int c = atoi(*(argv + 3));
    
    int i, j, k;
    
    int **M, **N, **L;
	
    M = (int **)malloc(sizeof(int *)*a);
    for (i = 0; i < a; i++){
        *(M + i) = (int*)malloc(sizeof(int)*b);
    }


    N = (int **)malloc(sizeof(int *)*b);
    for (i = 0; i < b; i++){
        *(N + i) = (int*)malloc(sizeof(int)*c);
    }


    L = (int **)malloc(sizeof(int *)*a);
    for (i = 0; i < a; i++){
        *(L + i) = (int*)malloc(sizeof(int)*c);
    }


    srand(time(NULL));


    printf("Pointer address value of matrix M: %p\n",M);

    for (i = 0; i < a; i++){
        for (j = 0; j < b; j++){
            *(*(M+i)+j) = rand()%10000 + 1;
            printf("%5d", *(*(M+i)+j));
        }

        printf("\n");
        
    }
    
    printf("\n");


    printf("Pointer address value of matrix N: %p\n",N);

    for (i = 0; i < b; i++){
        for (j = 0; j < c; j++){
            *(*(N+i)+j) = rand()%10000 + 1;
            printf("%5d", *(*(N+i)+j));
        }

        printf("\n");
        
    }
    
    printf("\n");


    printf("Pointer address value of matrix L: %p\n",L);

    for (i = 0; i < a; i++){
        for (j = 0; j < c; j++){
            int sum = 0;
            for (k= 0; k < b; k++){
                sum += (*(*(M+i)+k)) * (*(*(N+k)+j));
            }

            *(*(L+i)+j) = sum;
            printf("%10d", *(*(L+i)+j));
        }

        printf("\n");
        
    }
    
    printf("\n");    

    return 0;
}
