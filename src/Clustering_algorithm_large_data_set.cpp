#include<stdio.h>
#include<stdlib.h>

int *clusters;
int *size;
int nClusters;


typedef struct vertice
{
	int *bits;
	int node;
}Vertex;


int isConnected(int,int);
void mergeClusters(int,int);
int findRoot(int);

int main()
{
	FILE *fp;
	int nVertices = 0,nBits = 0, nEdges = 0,count = 0,maxSpace = 0;
	Vertex *vertices;

	int c,sum=0;

	fp = fopen("clustering_big.txt","r");

	if(fp == NULL)
	{
		printf("%d\n"," Error opening file");
		return 0;
	}

	
	fscanf(fp,"%d",&nVertices);
	fscanf(fp,"%d",&nBits);

	vertices = (Vertex *)malloc((nVertices+1)*sizeof(struct vertice));
	

	for(int i = 1; i <= nVertices; i++)
	{
		vertices[i].node = i;
		vertices[i].bits = (int *)malloc(nBits*sizeof(int));
	}

	

	for(int i = 1; i <= nVertices; i++)
	{
		for(int j = 0; j < nBits;j ++)
		{
		    fscanf(fp,"%d",&c);
			vertices[i].bits[j] = c;
		}
	}

	fclose(fp);

	nClusters = nVertices;

	clusters = (int *)malloc(sizeof(int)*(nVertices+1));
	size = (int *)malloc(sizeof(int)*(nVertices+1));

	for(int i = 1;i <= nVertices; i++)
	{
		clusters[i] = i;
		size[i] = 1;
	}

	
	for(int i = 1;i <= nVertices; i++)
	{
		for(int j = i+1; j <=nVertices; j++)
		{
			for(int k = 0;k < nBits;k++)
			{
				if(vertices[i].bits[k] != vertices[j].bits[k])
                       sum++;
			}
			if(sum <= 2)
			{
				if(!isConnected(i,j))
				{
					mergeClusters(i,j);
				}
			}
			sum = 0;
		}
	}

	printf("%d\n",nClusters);

	
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