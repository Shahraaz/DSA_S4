#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fin, *fout;
int a[1000], b[1000];
int cnt = 0;
typedef struct node
{
    int data;
    int l, r;
    struct node *next;
} Node;
Node *Hash[1000];
int CNT[1000] = {0};

int find(int num1, int num2)
{
    int k = num1 % 1000, k2 = num2 % 1000;
    Node *Head = Hash[k];
    int cnt=0;
    while (Head != NULL)
    {
        if (Head->data == k2 && Head->l == num1 && Head->r == num2)
            cnt++;
	if(cnt==2) return 1;
        Head = Head->next;
    }
    return 0;
}

void Push(int num1, int num2)
{
    int k = num1 % 1000, k2 = num2 % 1000;
    Node *temp = malloc(sizeof(Node));
    temp->data = k2;
    temp->l = num1;
    temp->r = num2;
    temp->next = Hash[k];
    Hash[k] = temp;
    CNT[k]++;
}

void insert(int num1, int num2)
{
	if(num1>num2)
	{
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}
    Push(num1, num2);
    if (find(num1, num2))
    {
        a[cnt] = num1;
        b[cnt] = num2;
        cnt++;
    }
}

int main()
{
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    if (fin == NULL || fout == NULL)
        return 0;
    for (int i = 0; i < 1000; i++)
        Hash[i] = NULL;
    char Choice;
    int num1 = 0, num2 = 0;
    while (!feof(fin))
    {
        Choice = getc(fin);
        switch (Choice)
        {
        case 's':
            while ((Choice = getc(fin)) != '(')
                ;
            while ((Choice = getc(fin)) != ',')
                num1 = num1 * 10 + (Choice - '0');
            while ((Choice = getc(fin)) == ' ')
                ;
	    num2 = Choice - '0';
            while ((Choice = getc(fin)) != ')')
                num2 = num2 * 10 + (Choice - '0');
            while ((Choice = getc(fin)) != '\n')
                ;
            insert(num1, num2);
            num1 = num2 = 0;
            break;
        case 'p':
            while ((Choice = getc(fin)) != '\n')
                ;
            for (int i = 0; i < cnt; i++)
                printf( "(%d, %d)\n", a[i], b[i]);
            break;
        case 'e':
            return 0;
        }
    }
    return 0;
}
