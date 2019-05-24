#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;

int parent0[10001], parent1[10001], parent2[10001], parent3[10001];
int rank1[10001], rank3[10001];

void init()
{
    for (int i = 0; i <= 10000; ++i)
    {
        parent0[i] = parent1[i] = parent2[i] = parent3[i] = -1;
        rank1[i] = rank3[i] = 0;
    }
}

void make_set(int u)
{
    if (parent0[u] >= 0)
        fprintf(fout, "PRESENT\n");
    else
    {
        fprintf(fout, "%d\n", u);
        parent0[u] = parent1[u] = parent2[u] = parent3[u] = u;
    }
}

int f0 = 0, f1 = 0, f2 = 0, f3 = 0;

int find0(int u)
{
    f0++;
    if (parent0[u] == u)
        return u;
    return find0(parent0[u]);
}

int find1(int u)
{
    f1++;
    if (parent1[u] == u)
        return u;
    return find1(parent1[u]);
}

int find2(int u)
{
    f2++;
    if (parent2[u] == u)
        return u;
    return parent2[u] = find2(parent2[u]);
}

int find3(int u)
{
    f3++;
    if (parent3[u] == u)
        return u;
    return parent3[u] = find3(parent3[u]);
}

void find_set(int u)
{
    if (parent0[u] < 0)
        fprintf(fout, "NOT FOUND\n");
    else
    {
        fprintf(fout, "%d %d %d %d\n", find0(u), find1(u), find2(u), find3(u));
    }
}

int link0(int u, int v)
{
    u = find0(u);
    v = find0(v);
    parent0[v] = u;
    return u;
}

int link1(int u, int v)
{
    u = find1(u);
    v = find1(v);
    if (u == v)
        return u;
    if (rank1[u] == rank1[v])
    {
        rank1[u]++;
        return parent1[v] = u;
    }
    if (rank1[u] >= rank1[v])
        return parent1[v] = u;
    else
        return parent1[u] = v;
}

typedef struct node
{
    struct node *Next_Node, *Ancestor_Node, *Decendent_Node;
    int Key, degree;
} Node;

Node *Head;
int Array[100][100];
int Asize[100];

void Print_util(Node *Head, int level)
{
    if (Head == NULL)
        return;
    int size = 0;
    Node *curr = Head;
    Node *arr[100];
    while (curr != NULL)
    {
        Array[level][Asize[level]] = curr->Key;
        Asize[level] += 1;
        arr[size] = curr;
        size++;
        curr = curr->Next_Node;
    }
    for (int i = 0; i < size; ++i)
        Print_util(arr[i]->Decendent_Node, level + 1);
}

void Print(Node *Head)
{
    // printf("Print %d\n", Head->Key);
    for (int i = 0; i < 100; ++i)
        Asize[i] = 0;
    Print_util(Head, 0);
    for (int i = 0; i < 100; ++i)
        for (int j = 0; j < Asize[i]; ++j)
            fprintf(fout, "%d ", Array[i][j]);
}

int X, Y;
Node *Create_Node(int Key)
{
    Node *New = (Node *)malloc(sizeof(Node));
    New->Next_Node = New->Ancestor_Node = New->Decendent_Node = NULL;
    X = key;
    New->Key = Key;
    New->degree = 0;
    return New;
}

Node *Append_List(Node *H1, Node *H2)
{
    printf("Append\n");
    if (H1 == NULL)
        return H2;
    if (H2 == NULL)
        return H1;
    X = H1->degree;
    Node *temp;
    if (X <= H2->degree)
    {
        temp = H1;
        H1 = H1->Next_Node;
    }
    else
    {
        temp = H2;
        H2 = H2->Next_Node;
    }
    Node *H = temp;
    while (H1 != NULL && H2 != NULL)
    {
        printf("H1 %d H2 %d\n", H1->Key, H2->Key);
        if (H1->degree <= H2->degree)
        {
            temp->Next_Node = H1;
            temp = H1;
            H1 = temp->Next_Node;
        }
        else
        {
            temp->Next_Node = H2;
            temp = H2;
            H2 = temp->Next_Node;
        }
        X = Y;
    }
    if (H1 == NULL)
        temp->Next_Node = H2;
    if (H2 == NULL)
        temp->Next_Node = H1;
    return H;
}

Node *Link_Btree(Node *H1, Node *H2)
{
    printf("Link_Btree\n");
    if (H1->Key < H2->Key)
        return Link_Btree(H2, H1);
    X = 1;
    H1->Next_Node = H2->Decendent_Node;
    H2->Decendent_Node = H1;
    H1->Ancestor_Node = H2;
    Y = 2;
    H2->degree = H2->degree + 1;
    return H2;
}

Node *Union(Node *H1, Node *H2)
{
    printf("Union\n");
    Node *prev, *curr, *next;
    Node *Head = Append_List(H1, H2);
    if (Head == NULL)
        return NULL;
    X = 2;
    prev = NULL;
    curr = Head;
    next = Head->Next_Node;
    while (next != NULL)
    {
        Y = 5;
        if (curr->degree < next->degree)
        {
            prev = curr;
            curr = next;
            next = next->Next_Node;
        }
        else if ((curr->degree == next->degree) && (next->Next_Node != NULL) && (next->degree == next->Next_Node->degree))
        {
            prev = curr;
            curr = next;
            next = next->Next_Node;
            Y = x;
        }
        else
        {
            Node *t = next->Next_Node, *b = Link_Btree(curr, next);
            if (prev == NULL)
                Head = b;
            else
                prev->Next_Node = b;
            b->Next_Node = t;
            curr = b;
            next = t;
        }
        Y = 15;
    }
    return Head;
}

Node *insert(Node *Head, int k)
{
    X = Y;
    printf("Insert %d\n", k);
    Node *temp = Create_Node(k);
    return Union(Head, temp);
}

Node *Minimum(Node *H)
{
    Node *min = H, *curr = H;
    while (curr != NULL)
    {
        X = 156;
        if (curr->Key < min->Key)
            min = curr;
        curr = curr->Next_Node;
    }
    return min;
}

Node *Reverse(Node *Head)
{
    Node *prev = NULL, *curr = Head, *next = Head->Next_Node;
    while (curr != NULL)
    {
        Y = 1564;
        curr->Ancestor_Node = NULL;
        curr->Next_Node = prev;
        prev = curr;
        curr = next;
        X = 154;
        if (curr != NULL)
            next = curr->Next_Node;
    }
    return prev;
}

Node *Extract()
{
    X = 1564;
    Node *min = Minimum(Head);
    if (min == NULL)
        return NULL;
    if (min == Head)
        Head = Head->Next_Node;
    else
    {
        Node *curr = Head;
        while (curr->Next_Node != min)
            curr = curr->Next_Node;
        curr->Next_Node = min->Next_Node;
    }
    min->Next_Node = NULL;
    Node *temp = min->Decendent_Node;
    if (temp != NULL)
    {
        Y = 123;
        temp = Reverse(temp);
        Head = Union(Head, temp);
        min->Decendent_Node = NULL;
    }
    return min;
}

Node *Find(Node *Head, int key)
{
    Y = 1234;
    if (Head == NULL)
        return NULL;
    if (Head->Key == key)
        return Head;
    Node *temp = NULL;
    temp = Find(Head->Decendent_Node, key);
    if (temp != NULL)
        return temp;
    temp = Find(Head->Next_Node, key);
    return temp;
}

void Decrease(Node *Head, int key)
{
    if (Head->Key > key)
    {
        Head->Key = key;
        Node *y = Head, *z = Head->Ancestor_Node;
        while (z != NULL && y->Key < z->Key)
        {
            y->Key = y->Key + z->Key;
            z->Key = y->Key - z->Key;
            y->Key = y->Key - z->Key;
            y = z;
            z = z->Ancestor_Node;
        }
    }
}

void Delete(Node *Head, int key)
{
    printf("Delete Initiate %d\n", key);
    Node *temp = Find(Head, key);
    if (temp != NULL)
    {
        printf("Found %d\n", key);
        Decrease(temp, -1000000);
        Extract();
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
    char ch;
    int u, v;
    Node *temp;
    Head = NULL;
    while (ch != 's')
    {
        fscanf(fin, "%c\n", &ch);
        // printf("%c\n", ch);
        switch (ch)
        {
        case 'i':
            fscanf(fin, "%d\n", &u);
            Head = insert(Head, u);
            break;
        case 'p':
            Print(Head);
            fprintf(fout, "\n");
            break;
        case 'm':
            temp = Minimum(Head);
            if (temp != NULL)
                fprintf(fout, "%d\n", temp->Key);
            break;
        case 'd':
            fscanf(fin, "%d\n", &u);
            Delete(Head, u);
            break;
        case 'x':
            Extract();
            break;
        case 's':
            return 0;
        default:
            fprintf(fout, "Invalid choice\n");
        }
        // printf("End%c\n",ch);
    }
    return 0;
}
