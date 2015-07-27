#include"Sort.h"

long long QuickSort(int A[],long long low, long long high)
{
	long long no_of_comparisons = 0;
	long long pivot;
	long long n;
	n = high-low+1;

	if(n == 1)
	{
		return no_of_comparisons;
	}
	else
	{
		no_of_comparisons+=(high-low);
		pivot = partition_median(A,low,high);
		if(low < pivot-1)
		no_of_comparisons+= QuickSort(A,low,pivot-1);
		if(pivot+1 < high)
		no_of_comparisons+= QuickSort(A,pivot+1,high);	
	}

	return no_of_comparisons;
}

long long partition_first(int A[],long long low,long long high)
{
	int p = A[low];
	long long i = low+1;
	long long j;
	int temp;

	
	for(j=low+1; j <= high; j++)
	{
		if(A[j]<p)
		{
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
			i++;
			prtition_comp++;
		}
		else
		{
			prtition_comp++;
		}
	}
	temp = A[low];
	A[low] = A[i-1];
	A[i-1] = temp;
	return i-1;
}

long long partition_last(int A[],long long low,long long high)
{
	int p = A[high];
	long long i = low+1;
	long long j;
	int temp;

	A[high] = A[low];
    A[low] = p;

	for(j=low+1; j <= high; j++)
	{
		if(A[j]<p)
		{
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
			i++;
			prtition_comp++;
		}
		else
		{
			prtition_comp++;
		}
	}
	temp = A[low];
	A[low] = A[i-1];
	A[i-1] = temp;
	return i-1;
}

long long partition_median(int A[],long long low,long long high)
{
	int p,median_index;
	long long i = low+1;
	long long j;
	int temp;

	median_index = find_median(A,low,high);
	p = A[median_index];
	A[median_index] = A[low];
	A[low] = p;

	for(j=low+1; j <= high; j++)
	{
		if(A[j]<p)
		{
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
			i++;
			prtition_comp++;
		}
		else
		{
			prtition_comp++;
		}
	}
	temp = A[low];
	A[low] = A[i-1];
	A[i-1] = temp;
	return i-1;
}

int find_median(int A[],int low, int high)
{
	int mid;
	mid = (low+high)/2;

    if(((A[low] - A[mid])*(A[high]-A[low]))>= 0)
        return low;
    else if(((A[mid] - A[low])*(A[high]-A[mid]))>= 0)
        return mid;
    else
        return high;
}
int main() {
	FILE *myFile;
    myFile = fopen("input\QuickSort.txt", "r");
	int Arr[MAX];
	long long i;
	long long no_of_comparisons;
	for (i = 0; i < MAX; i++)
    {
        fscanf(myFile, "%d", &Arr[i]);
    }
	no_of_comparisons = QuickSort(Arr,0,MAX-1);
	printf("no of comparisons = %l\n ",no_of_comparisons);
	printf("no of comparisons = %l\n ",prtition_comp);
	getchar();
	// your code goes here
	return 0;
}