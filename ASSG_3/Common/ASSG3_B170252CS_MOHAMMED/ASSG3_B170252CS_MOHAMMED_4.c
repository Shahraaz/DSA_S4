#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;

typedef struct node
{
    struct node *Head, *Tail, *Next;
    int data;
    int size;
} Node;

Node *parent0[10001], *parent1[10001];

Node *newNode(int data)
{
    Node *New = (Node *)malloc(sizeof(Node));
    New->Head = New;
    New->Tail = New;
    New->data = data;
    New->Next = NULL;
    New->size = 1;
    return New;
}

void init()
{
    // printf("Ininit\n");
    for (int i = 0; i <= 10000; ++i)
    {
        parent0[i] = newNode(-1);
        parent1[i] = newNode(-1);
    }
}

void make_set(int u)
{
    // printf("make_set\n");
    if (parent0[u]->data >= 0)
        fprintf(fout, "PRESENT\n");
    else
    {
        fprintf(fout, "%d\n", u);
        parent0[u]->data = u;
        parent1[u]->data = u;
    }
}

Node *find0(int u)
{
    // printf("find0\n");
    return parent0[u]->Head;
}

Node *find1(int u)
{
    // printf("find1\n");
    return parent1[u]->Head;
}

void find_set(int u)
{
    if (parent0[u]->data < 0)
        fprintf(fout, "NOT FOUND\n");
    else
        fprintf(fout, "%d %d\n", find0(u)->data, find1(u)->data);
}

int link0(int u, int v)
{
    // printf("In link0\n");
    Node* U = find0(u);
    Node* V = find0(v);
    Node *curr = U->Tail,*curr2 = V->Head;
    while(curr2!=NULL)
    {
        curr2->Head = U;
        curr->Next = curr2;
        curr = curr2;
        curr2 = curr2->Next;
    }
    U->size = U->size + V->size;
    U->Tail = V->Tail;
    return U->data;
}

int link1(int u, int v)
{
    // printf("In link1\n");
    Node* U = find1(u);
    Node* V = find1(v);
    if(U->size<V->size)
        return link1(v,u);
    if(U->size==V->size)
        if(U->data>V->data)
            return link1(v,u);
    Node *curr = U->Tail,*curr2 = V->Head;
    while(curr2!=NULL)
    {
        curr2->Head = U;
        curr->Next = curr2;
        curr = curr2;
        curr2 = curr2->Next;
    }
    U->size = U->size + V->size;
    U->Tail = V->Tail;
    return U->data;    
}

void union_set(int u, int v)
{
    if (parent0[u]->data < 0 || parent0[v]->data < 0)
        fprintf(fout, "ERROR\n");
    else
    {
        fprintf(fout, "%d %d\n", link0(u, v), link1(u, v));
    }
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
    init();
    char ch;
    int u, v;
    while (ch != 's')
    {
        fscanf(fin, "%c\n", &ch);
        switch (ch)
        {
        case 'm':
            fscanf(fin, "%d\n", &u);
            make_set(u);
            break;
        case 'f':
            fscanf(fin, "%d\n", &u);
            find_set(u);
            break;
        case 'u':
            fscanf(fin, "%d %d\n", &u, &v);
            union_set(u, v);
            break;
        case 's':
            return 0;
        default:
            fprintf(fout, "Invalid choice\n");
        }
    }
    return 0;
}