#include<stdio.h>
#include<stdlib.h>

FILE *fin,*fout;
int size[1000],n,Vis[1000];
typedef struct Edge
{
	int u,v,w;
} Edge;

typedef struct pair
{
	int f,s;
} pii;

Edge Adj[1000][1000];

int Heapsize ;
pii Heap[1000];

int parent(int u)
{
	return (u-1)/2;
}

int left(int u)
{
	return 2*u+1;
}

int right(int u)
{
	return 2*u + 2;
}

pii min_val()
{
	return Heap[0];
}

int index[1000];

void swap(pii *a,pii *b)
{
	pii temp = *a;
	*a = *b;
	*b = temp;
	int tt = index[a->s];
	index[a->s] = index[b->s];
	index[b->s] = tt;
}

void insert(pii x)
{
	Heap[Heapsize] = x;
	index[x.s] = Heapsize;	
	int  i = Heapsize;
	Heapsize++;
	while(i!=0 && Heap[parent(i)].f > Heap[i].f)
	{
		swap(&Heap[parent(i)],&Heap[i]);
		i = parent(i);
	}
}

void Decrease(int x,int w)
{
	int i = index[x];
	if(Heap[i].f > w)
	{
		Heap[i].f = w;
		while(i!=0 && Heap[parent(i)].f > Heap[i].f)
		{
			swap(&Heap[parent(i)],&Heap[i]);
			i = parent(i);
		}
	}
}

void MinHeapify(int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < Heapsize && Heap[l].f < Heap[i].f) 
        smallest = l; 
    if (r < Heapsize && Heap[r].f < Heap[smallest].f) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&Heap[i], &Heap[smallest]); 
        MinHeapify(smallest); 
    } 
} 

pii extractMin() 
{ 
    pii root = Heap[0]; 
    if (Heapsize <= 0) 
        return root; 
    if (Heapsize == 1) 
    { 
        Heapsize--; 
        return Heap[0]; 
    } 
  
    Heap[0] = Heap[Heapsize-1]; 
    Heapsize--; 
    MinHeapify(0);   
    return root; 
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
	for(int i=0;i<n;++i)
		for(int j=0;j<size[i];++j)
		{
			int w;
			fscanf(fin,"%d",&w);
			Adj[i][j].w = w;;
		}	
	pii temp ;
	long long mst = 0;
	temp.f = 0;
	temp.s = 0;	
	insert(temp);
	for(int i=1;i<n;++i)
	{
		temp.s = i;
		temp.f = 1e9;
		insert(temp);
	}
	while(Heapsize)
	{
		temp = min_val();
		extractMin();
		//printf("Top %d %d\n",temp.f,temp.s);
		if(Vis[temp.s]) continue;
		Vis[temp.s] = 1;
		mst += temp.f;
		for(int i=0;i<size[temp.s];++i)
		{
			Edge x = Adj[temp.s][i]; 
			//printf("%d %d\n",x.v,x.w);
			if(!Vis[x.v]) Decrease(x.v,x.w);
		}
	}
	fprintf(fout,"%d",mst);
	return 0;
}
