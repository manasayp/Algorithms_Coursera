#if 0
// I/O Includes

#include<new>
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<strstream>

// Data Structure Includes

#include<map>
#include<set>
#include<list>
#include<stack>
#include<stdio.h>
#include<stdlib.h>

int knapsack(int ,int ,int *,int *);
int return_max(int , int );

int main()
{
	FILE *fp;
	int Capacity , nItems;
	int *value,*weight,i = 1;

	fp = fopen("input/knapsack1.txt","r");

	if(fp == NULL)
	{
		printf("Error Opening File\n");
		return 0;
	}

	fscanf(fp,"%d",&Capacity);
	fscanf(fp,"%d",&nItems);

	value = (int *)malloc(nItems*sizeof(int));
	weight = (int *)malloc(nItems*sizeof(int));

	while(!feof(fp))
	{
		fscanf(fp,"%d",&value[i]);
		fscanf(fp,"%d",&weight[i]);
		i++;
	}

	int maxValue = knapsack(Capacity,nItems,value,weight);
	printf("The optimal solution for the knapsack problem is  %d\n",maxValue);
	getchar();
	return 0;
}


int knapsack(int Capacity,int nItems,int *value,int *weight)
{
	int **K;
    K = (int **)malloc((nItems+1)*sizeof(int *));

	for(int i  = 0 ; i <= nItems; i++)
	{
		K[i] = (int *)malloc((Capacity+1)*sizeof(int));
	}

	for(int i  = 0 ; i < Capacity+1; i++)
	{
		K[0][i] = 0;
	}

	for(int i = 1; i < nItems+1; ++i)
	{
		for(int j = 0 ; j <= Capacity ; ++j)
		{
			
			if((j - weight[i]) > 0)
			{
				K[i][j] = return_max(K[i-1][j],K[i-1][j-weight[i]]+value[i]);
			}
			else
			{
				K[i][j] = K[i-1][j];
			}
		}
	}
	return K[nItems][Capacity];
}

int return_max(int a, int b)
{
	return (a > b)? a : b;
}
#endif