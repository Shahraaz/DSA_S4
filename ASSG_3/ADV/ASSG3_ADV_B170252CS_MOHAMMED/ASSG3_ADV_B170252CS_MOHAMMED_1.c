#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;

int size, capacity;

int *push(int *arr, int d)
{
    // printf("push %d\n", d);
    arr[size] = d;
    size = size + 1;
    if (size == capacity)
    {
        capacity = capacity * 2;
        arr = realloc(arr, sizeof(int) * (capacity));
    }
    return arr;
}

int *getarray()
{
    char ch = '0';
    while (ch != '(')
        ch = getc(fin);
    int *arr = (int *)malloc(sizeof(int) * 16);
    size = 0;
    capacity = 16;
    int d;
    while (ch != ')')
    {
        int num = 0,temp = 0;
        ch = getc(fin);
        while (ch != ' ' && ch != ')')
        {
            temp = 1;
            num = num * 10 + ch - '0';
            ch = getc(fin);
        }
        if(temp)
            arr = push(arr,num);
    }
    fscanf(fin, "%c", &ch);
    return arr;
}

void print(int *arr, int start, int end)
{
    // printf("Print s\n");
    for (int i = start; i < end; ++i)
    {
        fprintf(fout, "%d", arr[i]);
        if (i != end - 1)
            fprintf(fout, " ");
    }
    // printf("Print e\n");
}

int *Concat(int *arr, int *arr1, int size1)
{
    for (int i = 0; i < size1; ++i)
        arr = push(arr, arr1[i]);
    return arr;
}

int search(int *arr, int x)
{
    for (int i = 0; i < size; ++i)
        if (arr[i] == x)
            return 1;
    return 0;
}

int main()
{
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    if (fin == NULL || fout == NULL)
        return 0;
    char ch;
    int x, y;
    int *arr,*arr1;
    while (ch != 'x')
    {
        ch = getc(fin);
        //printf("%c\n",ch);
        switch (ch)
        {
        case 'a':
            arr = getarray();
            fscanf(fin, " %d\n", &x);
            arr = push(arr, x);
            fprintf(fout,"(");
            print(arr, 0, size);
            fprintf(fout,")\n");
            break;
        case 'c':
            arr = getarray();
            int s1 = size, c1 = capacity;
            arr1 = getarray();
            x = size;
            size = s1;
            capacity = c1;
            arr = Concat(arr, arr1, x);
            fprintf(fout,"(");
            print(arr, 0, size);
            fprintf(fout,")\n");
            break;
        case 'm':
            arr = getarray();
            fscanf(fin, " %d\n", &x);
            fprintf(fout, "%d\n", search(arr, x));
            break;
        case 'l':
            arr = getarray();
            fprintf(fout, "%d\n", size);
            break;
        case 's':
            arr = getarray();
            fscanf(fin, " %d %d\n", &x, &y);
            print(arr, x - 1, y);
            break;
        case 'x':
	    fclose(fout);
            return 0;
        default:
            fprintf(fout, "Invalid case\n");
        }
    }
    return 0;
}
