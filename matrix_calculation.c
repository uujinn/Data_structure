#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){

	
	// 프로그램 실행 시 행렬 M(aXb)과 N(bXc)의 크기(a,b,c)를 int타입으로 입력받는다.
    int a = atoi(*(argv + 1));
    int b = atoi(*(argv + 2));
    int c = atoi(*(argv + 3));
    
    int i, j, k;
    
    int **M, **N, **L;

	// (aXb)의 크기로 int 타입의 메모리 할당
    M = (int **)malloc(sizeof(int *)*a);
    for (i = 0; i < a; i++){
        *(M + i) = (int*)malloc(sizeof(int)*b);
    }

	// (bXc)의 크기로 int 타입의 메모리 할당
    N = (int **)malloc(sizeof(int *)*b);
    for (i = 0; i < b; i++){
        *(N + i) = (int*)malloc(sizeof(int)*c);
    }

	// (aXc)의 크기로 int타입의 메모리 할당
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
