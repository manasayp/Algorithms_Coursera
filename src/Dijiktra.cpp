#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define MAX 200
#define V 200

int graph_d[MAX][MAX];

int isCompleted(int *);
int find_minimum(int *,int *);
void print_solution(int *);

void dijiktra(int graph[V][V],int src)
{
	int *dist = NULL;
	int *visited = NULL;
	int *prev = NULL;
	int u , v;

	dist = (int *)malloc(sizeof(int)*V);
	visited = (int *)malloc(sizeof(int)*V);
	prev = (int *)malloc(sizeof(int)*V);

	if(dist == NULL || visited == NULL || prev == NULL)
		return;

	for(int i = 0; i < V; i++)
	{
		dist[i] = INT_MAX;
		visited[i] = 0;
		prev[i] = NULL;
	}
	dist[src] = 0;

	while(!isCompleted(visited))
	{
		int min = INT_MAX;
		u = find_minimum(dist,visited); // for finding shortest path from src to a particular dst, compare u with dst and break
		visited[u] = 1;

		for(int v = 0; v < V; v++)
		{
			if((visited[u] == 1) && 
			   (dist[u] != INT_MAX) &&
			   (graph[u][v] !=0) && 
			   (graph[u][v]+dist[u] < dist[v]))
			{
				dist[v] = dist[u]+graph[u][v];
				prev[v] = u;
			}
		}
	}
	print_solution(dist);
}

int isCompleted(int *visited)
{
	for(int i = 0; i < V; i++)
	{
		if(visited[i] == 0)
			return 0;
	}
	return 1;
}

int find_minimum(int *dist,int *visited)
{
	int min_index = 0, min = INT_MAX;

	for(int i = 0; i < V; i++)
	{
		if(dist[i] <= min && visited[i] == 0)
		{
			min = dist[i];
			min_index = i;
		}
	}
	return min_index;
}

void print_solution(int dist[])
{
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < V; i++)
   {
	if((i == 6) || (i == 36) || (i ==58) || (i == 81) || (i == 98) || (i ==114) || (i == 132) ||(i ==164) || (i == 187) || (i == 196))
      printf("%d \t\t %d\n", i, dist[i]);
   }
}
int main()
{
	FILE *myFile;
	int u,v,w,i=0,j=0;
	char ch[50];

	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			graph_d[i][j] = 0;
		}
	}

	myFile = fopen("input/dijkstraData.txt", "r");

	if (myFile != NULL) {
        char line[1000];
        
        while (fgets(line, sizeof line, myFile) != NULL) 
		{
            char *start = line;
            int n,i = 0;
            sscanf(start, "%d%n", &u, &n);
			start += n;
            while(sscanf(start, "%d%n", &v,&n) == 1)
			{
				start += n;
				start += 1;
				sscanf(start, "%d%n", &w,&n);
				start += n;
				graph_d[u-1][v-1] = graph_d[v-1][u-1] = w;
			}
                
            puts("");
        }
 }

    dijiktra(graph_d,0);
	getchar();
}
#endif