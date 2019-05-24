#include<stdio.h>
#include<stdlib.h>

FILE *fin,*fout;
int size[1000],n,m;
typedef struct Edge
{
	int u,v,w;
}Edge;

Edge Adj[1000][1000];

void Addedge(int u,int v,int w)
{
	//printf("%d %d %d\n",u,v,w);
	Adj[u][size[u]].u = u;
	Adj[u][size[u]].v = v;
	Adj[u][size[u]].w = w;
	size[u]++;
}
int mod = 1e9 + 7; 
int Dist[1000];

typedef struct pii
{
	int f,s;
} pii;

typedef struct node
{
	pii data;
	int degree;
	struct node *sibling,*child,*parent; 
}Node;

Node *Directory[1000];

void init()
{
	for(int i=0;i<1000;++i)
	{	
		Directory[i] = NULL;		
		Dist[i] = mod;
	}
}

Node* createnode(pii data)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	Directory[data.s] = temp;
	temp->degree = 0;
	temp->sibling = temp->child = temp->parent = NULL;
	return temp; 
}

Node *Heap = NULL;

Node *Merge(Node* Head1,Node *Head2)
{
	if(Head1==NULL) return Head2;
	if(Head2==NULL) return Head1;
	Node *Buffer = NULL,*Tail = NULL;
	while(Head1!=NULL && Head2!=NULL)
	{		
		if(Head1->degree <= Head2->degree)
		{
			if(Buffer==NULL)
				Tail = Buffer = Head1;			
			else
			{
				Tail->sibling = Head1;
				Tail = Head1;
			}			
			Head1 = Head1->sibling;
		}
		else
		{
			if(Buffer==NULL)
				Tail = Buffer = Head2;	
			else
			{
				Tail->sibling = Head2;
				Tail = Head2;
			}
			Head2 = Head2->sibling;
		}
	}
	if(Head1!=NULL)
		Tail->sibling = Head1;
	if(Head2!=NULL)
		Tail->sibling = Head2;
	return Buffer;
}

int cmp(pii a,pii b)
{
	if(a.f==b.f) return a.s < b.s;
	return a.f < b.f;
}

Node *Link(Node *One,Node *two)
{
	if(One==NULL)	return two;
	if(two==NULL)	return One;
	if(cmp(One->data,two->data))
	{
		two->sibling = One->child;
		two->parent = One;
		One->child = two;
		One->degree = 1 + One->degree;
		return One;	
	}
	else
	{
		One->sibling = two->child;
		One->parent = two;
		two->child = One;
		two->degree = 1 + two->degree;
		return two;	
	}
}

Node *Union(Node *Head1,Node *Head2)
{
	Node *Head = Merge(Head1,Head2);
	if(Head==NULL)
		return Head;
	Node *prev = NULL,*curr = Head,*next = Head->sibling;;
	while(next!=NULL)
	{
		if(curr->degree == next->degree)
		{
			Node *Nnext = next->sibling;
			if(Nnext!=NULL && Nnext->degree==curr->degree)
			{
				prev = curr;
				curr = next;
				next = Nnext;
			}
			else
			{
				Node *temp = Link(curr,next);
				temp->sibling = Nnext;
				if(prev==NULL) Head = temp;
				else prev->sibling = temp;
			}
		}
		else
		{
			prev = curr;
			curr = next;
			next = next->sibling;
		}
	}
	return Head;
}

void insert(pii x)
{
	printf("%d %d\n",x.f,x.s);
	if(Heap==NULL)
		Heap = createnode(x);
	else
		Heap = Union(Heap,createnode(x));
}

Node *min(Node *Head)
{
	if(Head==NULL) return Head;
	Node *temp = Head,*curr = Head;
	while(curr!=NULL)
	{
		if(cmp(curr->data,temp->data))
			temp = curr;
		curr = curr->sibling;
	}	
	return temp;
}

Node *Reverse(Node *H)
{
	if(H==NULL) return H;
	Node *curr = H,*prev = NULL, *next = H->sibling;
	while(curr!=NULL)
	{
		curr->sibling = prev;
		prev = curr;
		curr = next;
		if(next!=NULL)
			next = next->sibling;
	}
	return prev;
}

pii extract(Node *Head1)
{
	//printf("Extract\n");
	pii temmmm ;
	if(Head1==NULL) return temmmm;
	Node* mini = min(Head1);
	if(Head1==mini)
		Head1 = mini->sibling;
	else
	{
		Node *curr = Head1;
		while(curr->sibling != mini)
			curr = curr->sibling;
		curr->sibling = mini->sibling; 
	}
	Node *Head2 = mini->child;
	Head2 = Reverse(Head2);
	Heap = Union(Head1,Head2);
	return mini->data;
}


void swap(pii *a,pii *b)
{
	printf("Swap %d %d || %d %d\n",a->f,a->s,b->f,b->s);
	pii temp = *a;
	*a = *b;
	*b = temp;
	Node *tt = Directory[a->s];
	Directory[a->s] = Directory[b->s] ;
	Directory[b->s] = tt;
}

void Decrease(int idx,int w)
{
	printf("Decrease %d %d\n",idx,w);	
	Node *temp = Directory[idx];
	if(temp!=NULL)
		if(temp->data.f > w)
		{
			temp->data.f = w;
			Node *Parent = temp->parent;
			while(Parent!=NULL && cmp(temp->data,Parent->data))
			{
				swap(&(temp->data),&(Parent->data));
				temp = Parent;			
			}
		}
}

int Vis[1000];

void Dijktara(int s)
{
	init();
	Dist[s] = 0;
	pii top;
	top.f = 0;
	top.s = s;
	printf("Source\n");
	insert(top);
	for(int i=0;i<n;++i)
	{
		if(i==s) continue;
		printf("Sedate\n");
		top.f = mod;
		top.s = i;
		insert(top);
	}
	while(Heap!=NULL)
	{
		top = extract(Heap);
		printf("Top %d %d\n",top.f,top.s);
		Vis[top.s] = 1;
		Dist[top.s] = top.f;
		for(int i=0;i<size[top.s];++i)
		{
			Edge x = Adj[top.s][i];
			printf("Edge %d %d %d\n",x.u,x.v,x.w);
			if(!Vis[x.v]) Decrease(x.v,top.f+x.w);
		}
	}
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
		Addedge(y,x,z);
	}
	fscanf(fin,"%d",&s);
	Dijktara(s);
	for(int i=0;i<n;++i)
	{
		fprintf(fout,"%d ",i);
		if(Dist[i] == mod)
			fprintf(fout,"INF\n");
		else fprintf(fout,"%d\n",Dist[i]);
	}
	return 0;
}
