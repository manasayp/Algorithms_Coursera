#include <stdio.h>
#include <stdlib.h>
#define MAX 100000

long long MergeSort(int A[],long long low,long long high);
long long Merge(int A[],long long low,long long high,long long mid);

long long MergeSort(int A[],long long low,long long high)
{
	long long no_of_inversion = 0;
	long long mid;
	if(low < high)
	{
	mid = (low+high)/2;
	no_of_inversion = MergeSort(A,low,mid);
	no_of_inversion+= MergeSort(A,mid+1,high);
	no_of_inversion+= Merge(A,low,high,mid);
	}
	return no_of_inversion;
}

long long Merge(int A[],long long low,long long high,long long mid)
{
	int c[MAX];
	long long no_of_inversion = 0;
	long long k=low,i=low,j=mid+1;
	while (i <= mid && j <= high)
	{
		if(A[i] <= A[j] )
		{
			c[k++] = A[i];
			i++;
		}
		else if(A[j] <= A[i])
		{
			c[k++] = A[j];
			j++;
			no_of_inversion+=(mid-i+1);
		}
	}
	while(i<=mid)
	{
		c[k++] = A[i++];
	}
	while(j<=high)
	{
		c[k++] = A[j++];
	}
	for(i = low;i <=high; i++) 
        A[i] = c[i];
	return no_of_inversion;
}
int main(int argc,char *argv[]) {
	FILE *myFile;
	if(argc < 2)
	{
		printf("Usage : ./a.out <filename> \n");
		exit(0);
	}
    myFile = fopen(argv[1], "r");
	if(myFile == NULL)
	{
		printf("Error opening file\n");
		exit(0);
	}
	int Arr[MAX];
	long long i;
	long long no_of_inversion;
	for (i = 0; i < MAX; i++)
    {
        fscanf(myFile, "%d", &Arr[i]);
    }
	no_of_inversion = MergeSort(Arr,0,MAX-1);
	printf("no of inversions = %ul\n",no_of_inversion);
	getchar();
	// your code goes here
	return 0;
}