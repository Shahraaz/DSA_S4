#include<stdio.h>
#include<stdlib.h>

FILE *fin,*fout;
int Adj[1000][1000],size[1000],n;


int main()
{
	fin = fopen("input.txt","r");
	fout = fopen("output.txt","w");
	fscanf(fin,"%d",&n);
	char ch = '\0';
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
				Adj[i][size[i]] = k;
				size[i]++;
				k = 0;
			}
			else k = k*10 + ch - '0';			
		}
	}
	return 0;
}
