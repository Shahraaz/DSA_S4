#include<bits/stdc++.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int m = 100;
    while(m--)
    {
        int ch = rand()%7;
        switch(ch)
        {
            case 0:
            case 5:
            case 6:
            cout << "i" << ' ' << rand()%20 << '\n';
            break;
            case 1:
            cout << "d" << ' ' << rand()%20 << '\n';
            break;
            case 2:
                cout << "p\n";
                break;
            case 3:
                cout << "m\n";
                break;
            case 4:
                cout << "x\n";
        }
    }
    cout << "s";
    return 0;
}