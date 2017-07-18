#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define YES 1
#define NO 0
#define NOT_DISCOVERED 2

bool isWayToDst(int** board, int** isPossible,int x, int y, int n);

int main()
{
    int c;

    //freopen("input.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n;
        int** board;
        int** isPossible;

        cin >> n;

        board = new int*[n];
        isPossible = new int*[n];

        for(int j = 0; j < n; j++)
        {
            board[j] = new int[n];
            isPossible[j] = new int[n];
            memset(board[j], 0, sizeof(int)*n);
        }

        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < n; k++)
            {
                cin >> board[j][k];
                isPossible[j][k] = NOT_DISCOVERED;
            }
        }

        if(isWayToDst(board,isPossible,0,0,n))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        for(int j = 0; j < n; j++)
        {
            delete [] isPossible[j];
            delete [] board[j];
        }
        delete [] board;
        delete [] isPossible;


    }
    return 0;
}

bool isWayToDst(int** board, int** isPossible,int x, int y, int n)
{
    //cout << "x : " << x << " y : " << y << endl;

    if(x == y && y == n-1)
    {
        isPossible[x][y] = YES;
        return YES;
    }
    else if(isPossible[x][y] == YES)
    {
        isPossible[x][y] = YES;
        return YES;
    }
    else if(isPossible[x][y] == NO)
    {
        isPossible[x][y] = NO;
        return NO;
    }
    else
    {
        if(x + board[x][y] < n)
        {
            if(isWayToDst(board,isPossible,x + board[x][y],y,n))
            {
                isPossible[x][y] = YES;
                return YES;
            }
        }
        if(y + board[x][y] < n)
        {
            if(isWayToDst(board,isPossible,x,y + board[x][y],n))
            {
                isPossible[x][y] = YES;
                return YES;
            }
        }
            isPossible[x][y] = NO;
            return NO;
    }
}
