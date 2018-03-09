#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;

int getState(int state, int index);
int setState(int state, int index, int value);
int getMinHanoi4(int* check,int start, int finish, int n);
int getMinHanoi4BIS(int* check,int start, int finish, int n);
int getSign(int x);
int incABS(int x);

const int MAX_DISKS = 12;
int check[1<<(MAX_DISKS * 2)];
int main()
{
    freopen("input.txt","r",stdin);

    int c;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n;
        int state = 0;
        int answer = 0;
        int goal = 0;

        cin >> n;

        for(int j = 0; j < 4; j++)
        {
            int temp;

            cin >> temp;

            for(int k = 0; k < temp; k++)
            {
                int temp2;
                cin >> temp2;

                state = setState(state,temp2-1,j);
            }
        }

        for(int j = 0; j < n; j++)
            goal = setState(goal,j,3);

        //answer = getMinHanoi4(check,state,goal,n);
        answer = getMinHanoi4BIS(check,state,goal,n);
        cout <<answer <<endl;
    }

    return 0;
}

int getState(int state, int index)
{
    return (state >> (index*2)) & 3; // 3-> 11(2)
}
//EX) state : ...1100, index : 1
// => state : ...11 & 3=11 => 11 -> 4th place

int setState(int state, int index, int value)
{
    return (state & ~(3 << (index * 2))) | (value << (index * 2));
}
//Ex) state : ...1100, index : 1, value : 2
//3 << (index * 2) => 1100 -> ~1100 = 0011
//state & 0011 => 0000
//value : 10(2), value << (index*2) => 1000
//==>>> 1000 -> 3rd place

int getMinHanoi4(int* check,int start, int finish, int n)
{

    //start : start State, finish : finish State, n : number of disks
    if(start == finish)
        return 0;
    queue<int> bfsq;
    memset(check,-1,sizeof(int)*(1<<(MAX_DISKS * 2)));
    check[start] = 0;
    bfsq.push(start);

    while(!bfsq.empty())
    {
        int topOfDisks[4] = {-1,-1,-1,-1};
        int ptr = bfsq.front();
        bfsq.pop();
        for(int i = 0; i < n; i++)
        {
            int temp = getState(ptr,i);

            if(topOfDisks[temp] == -1)
                topOfDisks[temp] = i;
        }
        for(int i = 0; i < 4; i++)
        {
            if(topOfDisks[i] != -1)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(i != j && (topOfDisks[i] < topOfDisks[j] || topOfDisks[j] == -1))// move to the jth disk
                    {
                        int next = setState(ptr,topOfDisks[i],j);
                        if(check[next] != -1)
                            continue;
                        check[next] = check[ptr]+1;
                        if(next == finish)
                            return check[next];

                        bfsq.push(next);
                    }
                }
            }
        }
    }

    return -1;
}

int getSign(int x)
{
    if(x == 0)
        return 0;
    else if(x < 0)
        return -1;
    else
        return 1;
}

int incABS(int x)
{
    if(x < 0)
        return x-1;
    else
        return x+1;
}

int getMinHanoi4BIS(int* check,int start, int finish, int n)
{
    //start : start State, finish : finish State, n : number of disks
    if(start == finish)
        return 0;
    queue<int> bfsq;
    memset(check,0,sizeof(int)*(1<<(MAX_DISKS * 2)));

    check[start] = 1;
    check[finish] = -1;
    bfsq.push(start);
    bfsq.push(finish);

    while(!bfsq.empty())
    {
        int topOfDisks[4] = {-1,-1,-1,-1};
        int ptr = bfsq.front();
        bfsq.pop();
        for(int i = 0; i < n; i++)
        {
            int temp = getState(ptr,i);

            if(topOfDisks[temp] == -1)
                topOfDisks[temp] = i;
        }
        for(int i = 0; i < 4; i++)
        {
            if(topOfDisks[i] != -1)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(i != j && (topOfDisks[i] < topOfDisks[j] || topOfDisks[j] == -1))// move to the jth disk
                    {
                        int next = setState(ptr,topOfDisks[i],j);
                        if(check[next] == 0)
                        {
                            check[next] = incABS(check[ptr]);
                            bfsq.push(next);
                        }
                        else if(getSign(check[next]) != getSign(check[ptr]))
                            return abs(check[next]) + abs(check[ptr]) - 1;
                    }
                }
            }
        }
    }

    return -1;
}
