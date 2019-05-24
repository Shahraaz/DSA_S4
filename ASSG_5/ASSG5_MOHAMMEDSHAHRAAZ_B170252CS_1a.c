#include<stdio.h>
#include<stdlib.h>

FILE *fin,*fout;
int size[1000],n;
typedef struct Edge
{
	int u,v,w;
} Edge;

Edge Adj[1000][1000];

int cmp(const void *a,const void *b)
{
	Edge l = *(Edge*)a;
	Edge r = *(Edge*)b;
	if(l.w==r.w)
	{
		if(l.u==r.u)
			return l.v < r.v;
		return l.u < r.u;
	}
	return  l.w > r.w;
}

int parent[1000],rank[1000];

void init()
{
	for(int i=0;i<1000;++i)
	{
		parent[i] = i;
		rank[i] = 1;
	}
}

int find(int u)
{
	if(u==parent[u])
		return u;
	return parent[u] = find(parent[u]);
}

int Union(int u,int v)
{
	u = find(u);
	v = find(v);
	//printf("u v %d %d\n",u,v);
	if(u==v) return 0;
	if(rank[u]>rank[v])	parent[v] = u;
	else
	{
		parent[u] = v;	
		if(rank[u]==rank[v]) rank[v]++;
	}
	return 1;
}

int main()
{
	fin = fopen("input.txt","r");
	fout = fopen("output.txt","w");
	fscanf(fin,"%d",&n);
	char ch = '\0';
	ch = getc(fin);
	for(int i=0;i<n;++i)
	{
		ch = getc(fin);
		if(ch=='\n') continue;
		int k = ch - '0';
		while(ch!='\n')
		{
			ch = getc(fin);
			if(ch == '\n' || ch == ' ')
			{
				//printf("%d\n",k);
				Adj[i][size[i]].v = k;
				Adj[i][size[i]].u = i;
				size[i]++;
				k = 0;
			}
			else k = k*10 + ch - '0';			
		}
	}
	int w,sizeedge = 0;
	Edge Edges[1000];
	for(int i=0;i<n;++i)
		for(int j=0;j<size[i];++j)
		{
			fscanf(fin,"%d",&w);
			Adj[i][j].w = w;
			Edges[sizeedge] = Adj[i][j];
			sizeedge++;
		}
	qsort(Edges,sizeedge,sizeof(Edges[0]),cmp);		
	long long mst = 0;
	init();
	for(int i=0;i<sizeedge;++i)
	{
		//printf("%d %d %d\n",Edges[i].u,Edges[i].v,Edges[i].w);
		if(Union(Edges[i].u,Edges[i].v))
			mst += Edges[i].w;	
	}
	fprintf(fout,"%d",mst);
	return 0;
}
