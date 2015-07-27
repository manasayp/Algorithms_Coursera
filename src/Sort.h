#ifndef __SORT_
#define __SORT__
#include <stdio.h>
#include <stdlib.h>
#define MAX 10000


long long QuickSort(int A[],long long low,long long high);
long long partition_first(int A[],long long low,long long high);
long long partition_last(int A[],long long low,long long high);
long long partition_median(int A[],long long low,long long high);
int find_median(int A[],int low, int high);

long long prtition_comp = 0;
#endif