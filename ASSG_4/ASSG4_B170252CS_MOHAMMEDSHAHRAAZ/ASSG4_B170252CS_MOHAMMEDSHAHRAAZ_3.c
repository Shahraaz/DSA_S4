#include<stdio.h>
#include<stdlib.h>

int red = 0,black = 1; 
FILE *fin,*fout;
typedef struct node
{
	int data,clr;
	struct node *left,*right;
} Node;
Node* Tree;

Node* create(int data)
{
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->clr = red;
	temp->left = temp->right = NULL;
	return temp;
}

int check_clr(Node *X)
{
	if(X==NULL)
		return black;
	return X->clr;
}

Node *RR(Node *X)
{
	if(X==NULL || X->left==NULL)
		return X;
	Node *ll = X->left;
	X->left = ll->right;
	ll->right = X;
	return ll;
}

Node *LL(Node *X)
{
	if(X==NULL || X->right==NULL)
		return X;
	Node *ll = X->right;
	X->right = ll->left;
	ll->left = X;
	return ll;
}

void Print(Node* X)
{
	if(X==NULL)
		return ;
	fprintf(fout,"(");
	Print(X->left);
	if(X->clr==red)
		fprintf(fout,"%dR",X->data);
	else
		fprintf(fout,"%dB",X->data);
	Print(X->right);
	fprintf(fout,")");	
}

int altered = 0,printinit = 0;
Node* rb_insert(Node *Root,int n)
{
	if(Root==NULL)
	{
		printinit = 1;
		return create(n);
	}
	if(Root->data==n)
	{
		printinit = 1;
		return Root;
	}
	if(Root->data < n)
		Root->right = rb_insert(Root->right,n);
	else Root->left = rb_insert(Root->left,n);
	if(printinit)
	{
		Print(Tree);
		fprintf(fout,"\n");
		printinit = 0;
	}
	if(check_clr(Root->left)==red)
	{
		if(check_clr(Root->left->left)==red)
		{
			if(check_clr(Root->right)==red)
			{
				altered = 1;
				Root->clr = red;
				Root->right->clr = Root->left->clr = black;	
			}
			else
			{
				altered = 1;
				Root = RR(Root);
				Root->clr = black;
				Root->right->clr = Root->left->clr = red;					
			}
		}		
	  if(check_clr(Root->left->right)==red)
		{
			if(check_clr(Root->right)==red)
			{
				altered = 1;
				Root->clr = red;
				Root->right->clr = Root->left->clr = black;	
			}
			else
			{
				altered = 1;
				Root->left = LL(Root->left);
				Root = RR(Root);
				Root->clr = black;
				Root->right->clr = Root->left->clr = red;					
			}
		}		
	}
	if(check_clr(Root->right)==red)
	{
		if(check_clr(Root->right->right)==red)
		{
			if(check_clr(Root->left)==red)
			{
				altered = 1;
				Root->clr = red;
				Root->right->clr = Root->left->clr = black;	
			}
			else
			{
				altered = 1;
				Root = LL(Root);
				Root->clr = black;
				Root->right->clr = Root->left->clr = red;					
			}
		}		
		if(check_clr(Root->right->left)==red)
		{
			if(check_clr(Root->left)==red)
			{
				altered = 1;
				Root->clr = red;
				Root->right->clr = Root->left->clr = black;	
			}
			else
			{
				altered = 1;
				Root->right = RR(Root->right);
				Root = LL(Root);
				Root->clr = black;
				Root->right->clr = Root->left->clr = red;					
			}
		}				
	}
	return Root;
}

Node* Rb_Tree_insert(Node *Tree,int n)
{
	altered = printinit = 0;
	if(Tree==NULL)
	{
		Tree = create(n);
		Tree->clr = black;
		Print(Tree);
		fprintf(fout,"\n");
	}
	else
		Tree = rb_insert(Tree,n);
	Tree->clr = black;
	if(altered)
	{
		Print(Tree);
		fprintf(fout,"\n");
		altered = 0;
	}
	return Tree;
}

int main()
{
	fin = fopen("input.txt","r");
	fout = fopen("output.txt","w");
	int n;
	Tree = NULL;
	while(!feof(fin))
	{
		fscanf(fin,"%d\n",&n);
		//printf("%d\n",n);
		Tree = Rb_Tree_insert(Tree,n);
	}
	fclose(fout);	
	return 0;
}
