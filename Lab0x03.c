#define _CRT_SECURE_NO_WARNINGS 1 //for visual studio, remove if giving errors
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long long int busyCount;
long long int countNumber = 20000000;

void doBusyWork()
{
    for (long long int a = 0; a < countNumber; a++)
    {
        busyCount++;
    }
}

enum
{
    Algo_A = true,
    Algo_B = true,
    Algo_C = true,
    Algo_D = true
};


void algorithm_A(int N, double list[])
{
    int a = 0;
    int b = N;

    while (a < b) {
        if (list[a] < list[b]) {
            a = a + 1;
            doBusyWork();
        }
        else {
            b = b - 1;
            doBusyWork();
        }
    }

}

int algorithm_B(int N, double list[])
{
    for (int q = 1; q < N; q = 2 * q) {
        for (int i = 0; i < N - q; i = i + 2 * q) {
            if (list[i] < list[i + q]) {
                int tmp = list[i];
                list[i] = list[i + q];
                list[i + q] = tmp;
                doBusyWork();
            }
        }
    }


    return list[0];
}



void algorithm_C(double list[], int startIndex, int endIndex) {
    if (endIndex > startIndex) {
        //phase 1   
        for (int i = startIndex; i <= (startIndex + endIndex) / 2; i++) {
            int x = list[i];
            list[i] = 2.0 * list[endIndex + startIndex - i];
            list[endIndex + startIndex - i] = x;
        }

        //phase 2: recursion 
        algorithm_C(list, startIndex, startIndex + floor(.5 * (endIndex - startIndex)));

        algorithm_C(list, startIndex + ceil(.25 * (endIndex - startIndex)), startIndex + floor(.75 * (endIndex - startIndex)));

        algorithm_C(list, startIndex + ceil(.5 * (endIndex - startIndex)), endIndex);

        //phase 3 
        for (int i = startIndex; i <= (startIndex + endIndex) / 2; i++) {
            int x = list[i];
            list[i] = list[endIndex + startIndex - i] / 2.0;
            list[endIndex + startIndex - i] = x;
        }
    }
}

int algorithm_D(int N)
{
    if (N <= 1)
    {
        doBusyWork();
        return 1;
    }
    else
    {
        return (algorithm_D(N - 1) + algorithm_D(N - 2));
    }
}

int main()
{
    int N;
    clock_t start, end;
    double total;

    if (Algo_A)
    {
        N = 512;
        double* mList = (double*)malloc(N * sizeof(double));
        for (int i = 0; i < N; i++)
            mList[i] = i;

        for (int i = 1; i <= N; i = i * 2)
        {

            printf("\n----------------------------------------------");
            start = clock();
            algorithm_A(i, mList);
            end = clock();

            total = (double)(end - start) / CLOCKS_PER_SEC;

            if (total > 0.0001)
            {
                printf("\n\nAlgorithm A: N=%d", i);
                printf("\n\nExperimental Time: %f", total);
                printf("\n----------------------------------------------");
            }
        }
        free(mList);
    }
       

    printf("\n\n****************************Algorithm Stoped******************************");

    if (Algo_B)
    {
        N = 512;
        double* mList = (double*)malloc(N * sizeof(double));
        for (int i = 0; i < N; i++)
            mList[i] = i;

        for (int i = 1; i <= N; i = i * 2)
        {

            printf("\n----------------------------------------------");

            start = clock();
            algorithm_B(i, mList);
            end = clock();
            total = (double)(end - start) / CLOCKS_PER_SEC;

            if (total > 0.0001)
            {
                printf("\n\nAlgorithm B: N=%d", i);
                printf("\n\nExperimental Time: %f", total);
                printf("\n----------------------------------------------");
            }
        }
        free(mList);
    }
        

    printf("\n\n****************************Algorithm Stoped******************************");

    if (Algo_C)
    {
        N = 32;
        double* mList = (double*)malloc(N * sizeof(double));
        for (int i = 0; i < N; i++)
            mList[i] = i;
        for (int i = 1; i <= N; i = i * 2)
        {
            start = clock();
            algorithm_C(mList, 0, i - 1);
            end = clock();
            printf("\n\nAlgorithm C: N=%d", i);
            total = (double)(end - start) / CLOCKS_PER_SEC;
            printf("\n\nExperimental Time: %f", total);
            printf("\n----------------------------------------------");
        }
        free(mList);
    }

    printf("\n\n****************************Algorithm Stoped******************************");

    if (Algo_D)
    {
        N = 32;
        double* mList = (double*)malloc(N * sizeof(double));
        for (int i = 0; i < N; i++)
            mList[i] = i;

        for (int i= 1; i <= N; i = i * 2)
        {
            start = clock();
            algorithm_D(i);
            end = clock();
            printf("\n\nAlgorithm D: N=%d", i);
            total = (double)(end - start) / CLOCKS_PER_SEC;
            printf("\n\nExperimental Time: %f", total);
            printf("\n----------------------------------------------");
        }
        printf("\n");
        free(mList);
    }    
    printf("\n\n****************************Algorithm Stoped******************************");

    return 0;
}