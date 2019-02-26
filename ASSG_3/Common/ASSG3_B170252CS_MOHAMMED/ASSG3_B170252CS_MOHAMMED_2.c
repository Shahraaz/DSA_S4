#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;

typedef struct node
{
    struct node *Left, *Right;
    int data, height;
} Node;

Node *newNode(int data)
{
    Node *New = (Node *)malloc(sizeof(Node));
    New->Left = NULL;
    New->Right = NULL;
    New->data = data;
    New->height = 0;
    return New;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int Height(Node *temp)
{
    if (temp == NULL)
        return -1;
    return temp->height;
}

Node *Left_Rotate(Node *x)
{
    Node *y = x->Right;
    if (y != NULL)
    {
        x->Right = y->Left;
        y->Left = x;
        x->height = 1 + max(Height(x->Left), Height(x->Right));
        y->height = 1 + max(Height(y->Left), Height(y->Right));
        return y;
    }
    return x;
}

Node *Right_Rotate(Node *x)
{
    Node *y = x->Left;
    if (y != NULL)
    {
        x->Left = y->Right;
        y->Right = x;
        x->height = 1 + max(Height(x->Left), Height(x->Right));
        y->height = 1 + max(Height(y->Left), Height(y->Right));
        return y;
    }
    return x;
}

Node *search(Node *Root, int x)
{
    if (Root == NULL)
        return NULL;
    if (Root->data == x)
        return Root;
    if (Root->data > x)
        return search(Root->Left, x);
    return search(Root->Right, x);
}

int getBalance(Node *Root, int x)
{
    Node *temp = search(Root, x);
    if (temp == NULL)
        return 0;
    return Height(temp->Left) - Height(temp->Right);
}

Node *Insert(Node *Root, int element)
{
    if (Root == NULL)
        return newNode(element);
    if (Root->data == element)
        return Root;
    if (Root->data > element)
        Root->Left = Insert(Root->Left, element);
    else if (Root->data < element)
        Root->Right = Insert(Root->Right, element);
    Root->height = 1 + max(Height(Root->Left), Height(Root->Right));
    int balance = Height(Root->Left) - Height(Root->Right);
    if (balance > 1 && element < Root->Left->data)
        return Right_Rotate(Root);
    if (balance < -1 && element > Root->Right->data)
        return Left_Rotate(Root);
    if (balance > 1 && element > Root->Left->data)
    {
        Root->Left = Left_Rotate(Root->Left);
        return Right_Rotate(Root);
    }
    if (balance < -1 && element < Root->Left->data)
    {
        Root->Right = Right_Rotate(Root->Right);
        return Left_Rotate(Root);
    }
    return Root;
}

Node *Min(Node *x)
{
    if (x->Left == NULL)
        return x;
    return Min(x->Left);
}

int bal(Node* root)
{
	if(root==NULL)
		return 0;
	return Height(root->Left) - Height(root->Right);
}

Node *Delete(Node *Root, int element)
{
    if (Root == NULL)
        return Root;
    if (Root->data != element)
    {
        if (element < Root->data)
            Root->Left = Delete(Root->Left, element);
        else
            Root->Right = Delete(Root->Right, element);
    }
    else if (Root->Left == NULL)
        Root =  Root->Right;
    else if (Root->Right == NULL)
        Root =  Root->Left;
    else
	{
	    Node *y = Min(Root->Right);
	    Node *z = Delete(Root->Right, y->data);
	    y->Right = z;
	    y->Left = Root->Left;
	    y->height = 1 + max(Height(y->Left), Height(y->Right));
	    Root = y;
	}
    if(Root==NULL)
		return NULL;
    Root->height = 1 + max(Height(Root->Left), Height(Root->Right));
    int balance = bal(Root);
	if(balance > 1 && bal(Root->Left)>=0 )
		return Right_Rotate(Root);
	if(balance > 1 && bal(Root->Left)<0 )
	{
		if(Root->Left!=NULL)
			Root->Left = Left_Rotate(Root->Left);
		return Right_Rotate(Root);	
	}
	if(balance < -1 && bal(Root->Right)<=0 )
		return Left_Rotate(Root);
	if(balance < -1 && bal(Root->Right)>0 )
	{
		if(Root->Right!=NULL)
			Root->Right = Right_Rotate(Root->Right);
		return Left_Rotate(Root);	
	}
    return Root;
}

int IsAvl(Node *Root)
{
    if (Root == NULL)
        return 1;
    int x = Height(Root->Left), y = Height(Root->Right);
    if (x > y)
    {
        if (x - y <= 1)
            return IsAvl(Root->Left) && IsAvl(Root->Right);
        return 0;
    }
    if (x - y <= 1)
        return IsAvl(Root->Left) && IsAvl(Root->Right);
    return 0;
}

void Print(Node *Root)
{
    if (Root == NULL)
    {
        fprintf(fout, "()");
        return;
    }
    fprintf(fout, "(%d", Root->data);
    if (Root->Left == NULL && Root->Right == NULL)
    {
        fprintf(fout, ")");
        return;
    }
    Print(Root->Left);
    Print(Root->Right);
    fprintf(fout, ")");
}

Node *Rot(Node *Root, int x, int k)
{
    if (Root == NULL)
        return Root;
    if (Root->data == x)
    {
        if (k)
            Root = Left_Rotate(Root);
        else
            Root = Right_Rotate(Root);
        return Root;
    }
    if (Root->data > x)
        Root->Left = Rot(Root->Left, x, k);
    else Root->Right = Rot(Root->Right, x, k);
    return Root;
}

int main()
{
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    if (fin == NULL || fout == NULL)
    {
        printf("Unable to open files\n");
        return 0;
    }
    int ch = 0;
    int u;
    Node *Root = NULL;
    while (ch != 9)
    {
        fscanf(fin, "%d\n", &ch);
	//printf("%d\n",ch);
	if(feof(fin)) return 0;
        switch (ch)
        {
        case 1:
            fscanf(fin, "%d\n", &u);
            Root = Insert(Root, u);
            break;
        case 2:
            fscanf(fin, "%d\n", &u);
            if (Root == NULL)
                fprintf(fout, "EMPTY\n");
            Root = Delete(Root, u);
            break;
        case 3:
            fscanf(fin, "%d\n", &u);
            Root = Rot(Root, u, 1);
            break;
        case 4:
            fscanf(fin, "%d\n", &u);
            Root = Rot(Root, u, 0);
            break;
        case 5:
            fscanf(fin, "%d\n", &u);
            fprintf(fout, "%d\n", getBalance(Root, u));
            break;
        case 6:
            Print(Root);
            fprintf(fout, "\n");
            break;
        case 7:
            if (IsAvl(Root))
                fprintf(fout, "TRUE\n");
            else
                fprintf(fout, "FALSE\n");
            break;
        case 8:
            fscanf(fin, "%d\n", &u);
            if (search(Root, u) == NULL)
                fprintf(fout, "FALSE\n");
            else
                fprintf(fout, "TRUE\n");
            break;
        case 9:
            return 0;
        default:
            fprintf(fout, "Invalid choice\n");
        }
    }
    return 0;
}
