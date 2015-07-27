/*run the greedy algorithm that schedules jobs in decreasing order of the difference (weight - length). 
IMPORTANT: if two jobs have equal difference (weight - length), you should schedule the job with higher weight first*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct jobs
{
	int weight;
	int length;
	int wt_lngth_diff;
	int job_id;
}Jobs;

/*Compute weight-length difference for Jobs*/
void Compute_diff(Jobs *diff_arr,int count)
{
	for(int i = 0; i < count ; i++)
	{
		diff_arr[i].wt_lngth_diff = diff_arr[i].weight-diff_arr[i].length;
		diff_arr[i].job_id = i;
	}
}

/*Quicksort - partition around pivot*/
int partition(Jobs A[],int low,int high,int k)
{
	int p;
	int i = low+1;
	int j;
	Jobs temp;

	if(k == 1) //Sorting jobs based on weight-length difference
	{
		p = A[low].wt_lngth_diff;
		for(j=low+1; j <= high; j++)
		{
			if(A[j].wt_lngth_diff<=p)
			{
				temp = A[j];
				A[j] = A[i];
				A[i] = temp;
				i++;
			}
		}
		temp = A[low];
		A[low] = A[i-1];
		A[i-1] = temp;
		return i-1;
	}
	else //Sorting jobs based on weight difference
	{
		p = A[low].weight;

		for(j=low+1; j <= high; j++)
		{
			if(A[j].weight<p)
			{
				temp = A[j];
				A[j] = A[i];
				A[i] = temp;
				i++;
			}
		}
		temp = A[low];
		A[low] = A[i-1];
		A[i-1] = temp;
		return i-1;
	}

}

/*Quicksort - to sort jobs */
int QuickSort(Jobs A[],int low, int high,int k)
{
	int pivot;
	int n;
	n = high-low+1;

	if(n > 1)
	{
		pivot = partition(A,low,high,k);
		if(low < pivot-1)
		QuickSort(A,low,pivot-1,k);
		if(pivot+1 < high)
		QuickSort(A,pivot+1,high,k);	
	}

	return 0;
}

/*sort jobs based on weights*/
void Sort_weights(Jobs *diff_arr,int count)
{
	int temp;
	int k = 0,n = 0;
	
	for(int i = 0; i < count; i++)
	{
		temp = diff_arr[i].wt_lngth_diff;
		k = i;
		n = i+1;
		while(diff_arr[n].wt_lngth_diff == temp)
		{
			n++;
		}
		if((n -k -1) > 0)
		{
            QuickSort(diff_arr,k,n-1,2);
			i = n-1;
		}
		
	}
	
	
}

/*Compute completion time*/
void Compute_Completion_time(Jobs *diff_arr,int count)
{
	long long sum = 0;
	long long w_sum = 0;
	FILE *fp;
	fp = fopen("weight.txt","w");

	if(fp != NULL)
	{
		for(int i = count-1; i >= 0 ; i--)
		{
			sum +=  diff_arr[i].length;
			fprintf(fp,"Job Id : %d Weight Difference : %d Weight: %d\t length = %d \t Completion Time = %d \n",diff_arr[i].job_id,diff_arr[i].wt_lngth_diff,diff_arr[i].weight,diff_arr[i].length,sum);
			w_sum += diff_arr[i].weight*sum;
		}
	}
	fclose(fp);
	printf("Sum = %ld\n",sum);
	printf("weighted sum = %lld\n",w_sum);
}

//Main function
int main()
{
	FILE *fp;
	fp = fopen("jobs.txt","r");
	int count = 0;

	Jobs *diff_array;

	if(fp == NULL)
	{
       printf("error in opening file\n");
	   return 0;
	}

	fscanf(fp,"%d",&count);

	diff_array = (Jobs *)malloc((count+1)*sizeof(struct jobs));

	memset(diff_array,0,(count+1)*sizeof(struct jobs));

	for(int i = 0 ; i < count; i++)
	{
		fscanf(fp,"%d",&diff_array[i].weight);
		fscanf(fp,"%d",&diff_array[i].length);
	}

	fclose(fp);

	Compute_diff(diff_array,count);
	QuickSort(diff_array,0,count-1,1);
	Sort_weights(diff_array,count);

	Compute_Completion_time(diff_array,count);

	free(diff_array);
	diff_array = NULL;
	return 0;
}