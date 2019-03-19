#include<stdio.h>
#include<stdlib.h>

FILE *fin,*fout;

int n;
int Adj[10000][10000];
int VIS[10000];
int Printer ;

void clearVIS()
{
	Printer = 1;
	for(int i=0;i<n;++i)
		VIS[i] = 0;
}

void BFS(int start,int end)
{
	int Q[10000],qstart,qend,qsize;
	qstart = qend = qsize = 0;
	Q[qend++] = start;
	qsize++;
	while(qsize)
	{
		int top = Q[qstart];
		qstart++;
		qsize--;
		if(VIS[top]) continue;
		VIS[top] = 1;
		fprintf(fout,"%d ",top);
		if(top==end)
			break;
		for(int i=0;i<n;++i)
			if(Adj[top][i] && !VIS[i])
			{
				Q[qend++] = i;
				qsize++;		
			}
	}
	fprintf(fout,"\n");	
}

void DFS(int start,int end)
{
		VIS[start] = 1;
		if(Printer)
			fprintf(fout,"%d ",start);
		if(start==end)
			Printer = 0;
		if(Printer==0)
			return;
		for(int i=0;i<n;++i)
			if(Adj[start][i] && !VIS[i])
				DFS(i,end);
}

int main()
{
	fin = fopen("input.txt","r");
	fout = fopen("output.txt","w");
	int i ;
	fscanf(fin,"%d",&n);
	char ch = '\0';
	ch = getc(fin);
	for(i=0;i<n;++i)
	{
		ch = getc(fin);
		if(ch=='\n' || ch==' ')
			continue;
		int k = ch - '0';
		while(ch!='\n')
		{
			ch = getc(fin);
			if(ch=='\n')
			{
				Adj[i][k] = 1;			
				k = 0;			
				break;		
			}
			if(ch==' ')
			{
				Adj[i][k] = 1;			
				k = 0;			
			}
			else k = k*10 + ch - '0';
		}
	}
	char str[5];
	int start,end;
	//printf("INPUT\n");
	while(1)
	{
		fscanf(fin,"%s %d %d\n",str,&start,&end);
		//printf("%s %d %d\n",str,start,end);
		clearVIS();
		switch(str[0])
		{
		case 's' :
			fclose(fout);
			return 0;
		case 'b' : 		
			BFS(start,end);
			break;
		case 'd' : 
			DFS(start,end);
			fprintf(fout,"\n");
			break;
		}
	}
	return 0;
}
