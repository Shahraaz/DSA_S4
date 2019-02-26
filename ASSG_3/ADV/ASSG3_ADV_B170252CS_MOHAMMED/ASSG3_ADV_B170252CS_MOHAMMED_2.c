#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;

int *arr[16];

void init()
{
    for (int i = 0; i < 16; ++i)
        arr[i] = NULL;
}

void Add_To_List(int x)
{
    int *Buffer = (int *)malloc(sizeof(int) * (1 << 16));
    int size = 1;
    Buffer[0] = x;
    for (int i = 0; i < 16; ++i)
    {
        if (arr[i] == NULL)
        {
            arr[i] = Buffer;
            return;
        }
        else
        {
            int temp[2 * size];
            int s1 = 0, s2 = 0, j = 0;
            while (s1 != size && s2 != size)
            {
                if (arr[i][s1] < Buffer[s2])
                {
                    temp[j] = arr[i][s1];
                    j++;
                    s1++;
                }
                else
                {
                    temp[j] = Buffer[s2];
                    j++;
                    s2++;
                }
            }
            while (s1 != size)
            {
                temp[j] = arr[i][s1];
                j++;
                s1++;
            }
            while (s2 != size)
            {
                temp[j] = Buffer[s2];
                j++;
                s2++;
            }
            arr[i] = NULL;
            size = size * 2;
            for (int k = 0; k < size; ++k)
                Buffer[k] = temp[k];
        }
    }
}

void print()
{
    //fprintf(fout,"Print INIT\n");
    for (int i = 0; i < 16; ++i)
    {
        if (arr[i] == NULL)
            continue;
        for (int j = 0; j < (1 << i); j++)
            fprintf(fout, "%d ", arr[i][j]);
    }
}

int Bsearch(int *A, int s, int e, int x)
{
    while (s < e)
    {
        // printf("%d %d\n",s,e);
        int mid = (s + e) / 2;
        if (A[mid] == x)
            return mid;
        if (A[mid] < x)
            s = mid + 1;
        else
            e = mid - 1;
    }
    if (s == e)
    {
        if (s >= 0)
            if (A[s] == x)
                return s;
    }
    return -1;
}

int find(int x)
{
    int add = 0;
    for (int i = 0; i < 16; ++i)
    {
        if (arr[i] == NULL)
            continue;
        int temp = Bsearch(arr[i], 0, (1 << i) - 1, x);
        if (temp >= 0)
            return add + temp;
        add = add + (1 << i);
    }
    return -1;
}

int main()
{
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    if (fin == NULL || fout == NULL)
        return 0;
    char ch;
    int x, y;
    init();
    while (ch != 'x')
    {
        fscanf(fin, "%c\n", &ch);
        //printf("%c\n", ch);
        switch (ch)
        {
        case 'i':
            fscanf(fin, " %d\n", &x);
            Add_To_List(x);
            break;
        case 'p':
            print();
            fprintf(fout, "\n");
            break;
        case 's':
            fscanf(fin, " %d\n", &x);
            x = find(x);
            if (x < 0)
                fprintf(fout, "NIL\n");
            else
                fprintf(fout, "1\n", x);
            break;
        case 'x':
            return 0;
        default:
            fprintf(fout, "Invalid case\n");
        }
        //printf("End\n");
    }
    return 0;
}
