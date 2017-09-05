#include <iostream>
#include <list>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

void whoIsTheSurvivers(list<int>& soliders, int n, int k);

int main()
{
    freopen("input.txt","r",stdin);

    list<int> soliders;
    int c;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n, k;

        cin >> n >> k;

        for(int j = 1; j < n+1; j++)
            soliders.push_back(j);

        for(list<int>::iterator ptr = soliders.begin() ; ptr != soliders.end(); ptr++)
            cout << *ptr << " ";
        cout << endl;

        whoIsTheSurvivers(soliders, n,k);

        soliders.sort();

        cout << soliders.front() << " " << soliders.back() << endl;

        soliders.clear();
    }
    return 0;
}

void whoIsTheSurvivers(list<int>& soliders, int n, int k)
{
    list<int>::iterator ptr;
    list<int>::iterator ptr_start;
    int next = 0;
    int now = 0;
    ptr = soliders.begin();


    for(int i = 0; i < n; i++)
    {
        int SSize = 0;

        if(ptr != soliders.end())
        {
            ptr_start = ++ptr;
            --ptr;
        }
        else
            ptr_start = soliders.begin();

        soliders.erase(ptr);

        ptr = ptr_start;

        for(list<int>::iterator ptr1 = soliders.begin() ; ptr1 != soliders.end(); ptr1++)
            cout << *ptr1 << " ";
        cout << endl;

        SSize = soliders.size();

        if(k-1 + next < SSize)
            next = k-1 + next;
        else
        {
            next = (k-1 + next - SSize - 1) % SSize;
            ptr = soliders.begin();
        }
        for(int j = 0; j < next; j++)
            ptr++;

        cout << "next : " << next << endl;

        cout << "? : " << *ptr << endl;

        if(soliders.size() == 2)
            break;
    }
}
