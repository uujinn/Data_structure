#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int degree[50]; // 차수
    int coef[50];   // 계수
    int n;
    char poly[50];

} polynomial;

void initPoly(polynomial *);
void Setpolynomial(polynomial *);
polynomial multPoly(polynomial, polynomial);
void printPoly(polynomial);
int poly_count(const char *src, const char *str);

void initPoly(polynomial *P)
{ // 다항식을 초기화시켜주는 함수
    int i;
    for (i = 0; i < 50; i++)
    {
        P->degree[i] = 0;
        P->coef[i] = 0;
    }
    
    P->n = 0;
}

void Setpolynomial(polynomial *P)
{
    initPoly(P);

    char *poly = P->poly;
    char *ptr = poly;
    int index = 0;

    while (ptr != NULL)
    {
        // 계수 구하기
        int tmp = 0;
        int sign = 1;

        if (*poly == '+')
        {
            sign = 1;
            poly++;
        }
        else if (*poly == '-')
        {
            sign = -1;
            poly++;
        }

        while (*ptr != 'x' && *ptr != 0)
            ptr++;

        while (poly != ptr)
        {
            tmp = tmp * 10 + (*poly - '0');
            poly++;
        }
        
        P->coef[index] = sign * tmp;
        P->n++;

        if (*poly == 0)
            break;

        tmp = 0;
        sign = 1;
        poly += 3;

        if (*poly == '+')
        {
            sign = 1;
            poly++;
        }
        else if (*poly == '-')
        {
            sign = -1;
            poly++;
        }

        ptr = poly;

        while (*ptr != '+' && *ptr != '-' && *ptr != 0)
            ptr++;

        while (poly != ptr)
        {
            tmp = tmp * 10 + (*poly - '0');
            poly++;
        }
        
        P->degree[index++] = sign * tmp;
        
        if (*poly == 0)
            break;
    }
}

polynomial multPoly(polynomial A, polynomial B)
{
    polynomial tmp;
    initPoly(&tmp);

    int i, j, k, l;
    int coef = 0, degree = 0;
    for (i = 0; i < A.n; i++){             
        for (j = 0; j < B.n; j++)
        {
            coef = A.coef[i] * B.coef[j];
            degree = A.degree[i] + B.degree[j];
            int flag = 1; // 이 항을 처리해야 하는지 알려주는 플래그. 
            // 0이면 이미 처리함. 1이면 처리해야함.
            
            // 차수가 같은 항이 있을 때 
            for (k = 0; k < tmp.n; k++)
            {
                if (tmp.degree[k] == degree)
                {
                    flag = 0;
                    tmp.coef[k] += coef;

                    // 계수가 0이 된다면 그 항은 제거
                    if (tmp.coef[k] == 0)
                    {
                        for (l = k; l < tmp.n - 1; l++)
                        {
                            tmp.coef[l] = tmp.coef[l + 1];
                            tmp.degree[l] = tmp.degree[l + 1];
                        }
                        
                        tmp.n--;
                    }
                    
                    break;
                }
            }

            // 차수가 같은 항이 없을 때 
            if (flag) // flag = true
            {
                for (k = 0; k < tmp.n && tmp.degree[k] > degree; k++)
                    ;
                
                for (l = tmp.n; l > k + 1; l--)
                {
                    tmp.coef[l] = tmp.coef[l - 1];
                    tmp.degree[l] = tmp.degree[l - 1];
                }
                
                tmp.coef[k] = coef;
                tmp.degree[k] = degree;
                tmp.n++;
            }
        }
    }
    return tmp;
}

void printPoly(polynomial P)
{
    int i;

    for (i = 0; i < P.n - 1; i++)
    {
        printf("%dx**%d", P.coef[i], P.degree[i]);
        if (P.coef[i + 1] > 0)
            printf("+");
    }

    printf("%d", P.coef[i]);

    if (P.degree[i] != 0)
        printf("x**%d", P.degree[i]);
    
    printf("\n");
}

int poly_count(const char *src, const char *str)
{
    int count = 0;
    const char *tmp = src;
    const char *ptr = strstr(tmp, str);

    while (ptr != NULL)
    {
        count++;
        tmp = ptr + 1;
        ptr = strstr(tmp, str);
    }

    return count + 1;
}

int main()
{
    char str[1000];
    printf("?");
    scanf("(%s", str); // 첫번째 ( 제외하고 받아줌
    str[strlen(str) - 1] = 0; // 마지막 ) 제거

    int n = poly_count(str, ")*(");
    polynomial *polys = (polynomial *)malloc(sizeof(polynomial));
    
    // polynomial 끊어서 배열에 넣어주기
    char *str_ptr = str;
    char *ptr = strstr(str, ")*(");
    int i = 0;

    while (ptr != NULL)
    {
        *ptr = 0;
        strcpy(polys[i++].poly, str_ptr);
        str_ptr = ptr + 3;
        ptr = strstr(ptr + 1, ")*(");
    }
    strcpy(polys[i].poly, str_ptr);

    // 넣어줬던 str 파싱
    for (i = 0; i < n; i++)
    {
        Setpolynomial(&polys[i]);
    }

    polynomial tmp = polys[0];

    for (i = 1; i < n; i++)
    {
        tmp = multPoly(tmp, polys[i]);
    }

    printPoly(tmp);
    return 0;
}