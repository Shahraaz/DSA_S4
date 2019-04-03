#include<stdio.h>
#include<stdlib.h>

FILE *fin,*fout;
int size[1000],n,m;
typedef struct Edge
{
	int u,v,w;
}Edge;

Edge Edges[1000];
int edgecnt ;

void Addedge(int u,int v,int w)
{
	//printf("%d %d %d\n",u,v,w);
	Edges[edgecnt].u = u;	
	Edges[edgecnt].v = v;	
	Edges[edgecnt].w = w;	
	edgecnt++;
}

int mod = 1e9+7;

int BellmanFordA()
{
	int Dist[n];
	for(int i=0;i<n;++i)	
		Dist[i] = mod;
	Dist[0] = 0;
	for(int i=0;i<n;++i)
		for(int j=0;j<edgecnt;++j)
		{
			int  u = Edges[j].u;
			int  v = Edges[j].v;
			int  w = Edges[j].w;
			if(Dist[u] != mod && (Dist[u] + w < Dist[v]))
				Dist[v] = Dist[u] + w;
		}
	for(int j=0;j<edgecnt;++j)
	{
		int  u = Edges[j].u;
		int  v = Edges[j].v;
		int  w = Edges[j].w;
		printf("%d %d %d\n",Dist[u], w, Dist[v]);		
		if(Dist[u] != mod && (Dist[u] + w < Dist[v]))
			return 1;
	}
	return 0;
}

int main()
{
	fin = fopen("input.txt","r");
	fout = fopen("output.txt","w");
	fscanf(fin,"%d",&n);
	fscanf(fin,"%d",&m);
	int x,y,z,s;
	for(int i=0;i<m;++i)
	{
		fscanf(fin,"%d %d %d",&x,&y,&z);
		Addedge(x,y,z);
	}
	if(BellmanFordA())
		fprintf(fout,"1");
	else fprintf(fout,"-1");
	return 0;
}
