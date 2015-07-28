#include<stdio.h>
#include<stdlib.h>

int *clusters;
int *size;
int nClusters;


typedef struct edges
{
	int e1;
	int e2;
	int weight;
}Edges;

int isConnected(int,int);
void mergeClusters(int,int);
int findRoot(int);
int partition(Edges A[],int low,int high);
int QuickSort(Edges A[],int low, int high);

int main()
{
	FILE *fp;
	int nVertices = 0, nEdges = 0,count = 0,maxSpace = 0;
	Edges *edge;

	fp = fopen("clustering1.txt","r");

	if(fp == NULL)
	{
		printf("%d\n"," Error opening file");
		return 0;
	}

	while(!feof(fp))
	{
        if (fgetc(fp) == '\n') 
            count = count++;
	}

	fclose(fp);

	fp = fopen("clustering1.txt","r");

	if(fp == NULL)
	{
		printf("%d\n"," Error opening file");
		return 0;
	}

	fscanf(fp,"%d",&nVertices);

	edge = (Edges *)malloc((count+1)*sizeof(struct edges));

	for(int i = 1; i < count; i++)
	{
		fscanf(fp,"%d",&edge[i].e1);
		fscanf(fp,"%d",&edge[i].e2);
		fscanf(fp,"%d",&edge[i].weight);

	}

	fclose(fp);

	nClusters = nVertices;
	nEdges = count-1;

	QuickSort(edge,1,nEdges);

	clusters = (int *)malloc(sizeof(int)*(nVertices+1));
	size = (int *)malloc(sizeof(int)*(nVertices+1));

	for(int i = 1;i <= nVertices; i++)
	{
		clusters[i] = i;
		size[i] = 1;
	}

	for(int i = 1; i <= nEdges;i++)
	{
		if(nClusters == 4)
			break;

		if(!isConnected(edge[i].e1,edge[i].e2))
		{
			mergeClusters(edge[i].e1,edge[i].e2);
		}
	}

	for(int i = 1; i <= nEdges;i++)
	{
		if(!isConnected(edge[i].e1,edge[i].e2))
		{
			maxSpace = edge[i].weight;
			break;
		}
	}

	printf("Maximum spacing of 4 clustering = %d \n", maxSpace);
	getchar();
	return 0;

}

int isConnected(int e1,int e2)
{
	if(findRoot(e1) == findRoot(e2))
		return 1;
	else
		return 0;
}

int findRoot(int i)
{
	while(clusters[i] != i)
	{
		i = clusters[i];
	}
	return i;
}

void mergeClusters(int e1,int e2)
{
	int root1 = findRoot(e1);
	int root2 = findRoot(e2);

	if(root1 > root2)
	{
		clusters[root2] = root1;
		size[root1]+=size[root2];
	}
	else
	{
		clusters[root1] = root2;
		size[root2]+=size[root1];
	}
	nClusters--;
}


/* Quicksort - Partition around pivot element */
int partition(Edges A[],int low,int high)
{
	double p = A[low].weight;
	int i = low+1;
	int j;
	Edges temp;

	for(j=low+1; j <= high; j++)
	{
		if(A[j].weight<=p)
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

/*Quicksort - to sort jobs based on weight*/
int QuickSort(Edges A[],int low, int high)
{
	int pivot;
	int n;
	n = high-low+1;

	if(n > 1)
	{
		pivot = partition(A,low,high);
		if(low < pivot-1)
		QuickSort(A,low,pivot-1);
		if(pivot+1 < high)
		QuickSort(A,pivot+1,high);	
	}

	return 0;
}