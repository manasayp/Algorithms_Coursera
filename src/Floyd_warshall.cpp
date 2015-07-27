#include<stdio.h>
#include<stdlib.h>
const int INF = 100000;

void floyd_warshall(int **graph,int nVertices);
int check_negative_cycle(int **graph,int nVertices);

int main()
{
	FILE *fp;
	int nVertices , nEdges, u, v , minDist = INF;
	int **graph;

	fp = fopen("g3.txt","r");

	if(fp == NULL)
	{
		printf("Error Opening File\n");
		return 0;
	}

	fscanf(fp,"%d",&nVertices);
	fscanf(fp,"%d",&nEdges);

	graph = (int **)malloc(nVertices*sizeof(int *));

	for(int i = 0 ; i < nVertices; i++)
	{
		graph[i] = (int *)malloc(nVertices*sizeof(int));
	}

	for(int i = 0 ; i < nVertices ; i++){
            for(int j = 0 ; j < nVertices ; j++)
                    graph[i][j] = INF;
    }

	while(!feof(fp))
	{
		fscanf(fp,"%d",&u);
		fscanf(fp,"%d",&v);
		fscanf(fp,"%d",&graph[u-1][v-1]);
	}

	/*for(int i = 0 ; i < nVertices ; i++){
            for(int j = 0 ; j < nVertices ; j++)
                    printf("%d\t",graph[i][j]);
			printf("\n");
    }
*/
	floyd_warshall(graph,nVertices);

	//for(int i = 0 ; i < nVertices ; i++){
 //           for(int j = 0 ; j < nVertices ; j++)
 //                   printf("%d\t",graph[i][j]);
	//		printf("\n");
 //   }

	if(check_negative_cycle(graph,nVertices))
	{
		 for(int i = 0 ; i < nVertices; i++)
		 {
                 for(int j = 0; j < nVertices ; j++)
				 {
				      if(i != j)
					  {
                          if(minDist > graph[i][j])
                              minDist = graph[i][j];
                      }
                 }
         }
		 printf("Shortest Distance = %d\n",minDist);
	}
	else
	{
		printf("Negative Cycle found\n");
	}
	getchar();

	free(graph);
	graph = NULL;
	return 0;
}

void floyd_warshall(int **graph,int nVertices)
{
     for(int k = 0; k <  nVertices; k++)
	 {
		 for(int i = 0; i < nVertices; i++)
		 {
			 for(int j = 0; j < nVertices; j++)
			 {
				 if(graph[i][k]+graph[k][j] < graph[i][j])
				 {
					 graph[i][j] = graph[i][k]+graph[k][j];
				 }
			 }
		 }
	 }
}

int check_negative_cycle(int **graph,int nVertices)
{
	for(int i = 0 ; i < nVertices; i++)
	{
		for(int j = 0; j <nVertices; j++)
		{
			if(graph[i][i] < 0)
				return 0;
		}
	}
	return 1;
}