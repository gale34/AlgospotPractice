#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int answer = 0;
int nEmptyCell = 0;
int h,w;
int dx[8] = {-1,-1,-1,0,0,1,1,1};
int dy[8] = {-1,0,1,-1,1,-1,0,1};

void coverBoard(char** board);
bool isRange(int x, int y);
bool isCoverable(int x, int y, char** board);

int main()
{
    int c;

    //freopen("input.txt", "r", stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        char **board;

        cin >> h >> w;

        board = new char*[h];

        for(int j = 0; j < h; j++)
            board[j] = new char[w];

        for(int j = 0; j < h; j++)
        {
            for(int l = 0; l < w; l++)
            {
                cin >> board[j][l];
                if((int)board[j][l] == 46)
                    nEmptyCell++;
            }
        }

        if(nEmptyCell %3 != 0)
            answer = 0;
        else
            coverBoard(board);


        cout << answer << endl;

        answer = 0;
        nEmptyCell = 0;
        for(int j = 0; j < h; j++)
            delete [] board[j];
        delete [] board;
    }


    return 0;
}

void coverBoard(char** board)
{
    /*for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
            cout << board[i][j];
        cout << endl;
    }
    cout << "==============================" << endl;*/

//cout << "x : " << x << " y : " << y <<endl;

    int x = -1;
    int y = -1;
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if((int)board[i][j] == 46)
            {
                x = i;
                y = j;
                break;
            }
        }
        if(x >= 0)
            break;
    }
    if(x == -1)
    {
        answer++;
        return ;
    }

    for(int i = 0; i < 4; i++)
    {
        int a, b;
        switch(i)
        {
            case 0:
                a = 4;
                b = 6;
                break;
            case 1:
                a = 5;
                b = 6;
                break;
            case 2:
                a = 6;
                b = 7;
                break;
            case 3:
                a = 4;
                b = 7;
                break;
        }

        if(isRange(x+dx[a],y+dy[a]) && isRange(x+dx[b],y+dy[b]))
        {
            if(isCoverable(x+dx[a],y+dy[a],board) && isCoverable(x+dx[b],y+dy[b],board))
            {
                board[x][y] = '#';
                board[x+dx[a]][y+dy[a]] = '#';
                board[x+dx[b]][y+dy[b]] = '#';
                nEmptyCell -= 3;

                //cout << "ith -> " << i << " x : " << x << " y : " << y <<endl;
                coverBoard(board);
                board[x][y] = '.';
                board[x+dx[a]][y+dy[a]] = '.';
                board[x+dx[b]][y+dy[b]] = '.';
                nEmptyCell += 3;
            }
        }
    }

    return ;
}


bool isRange(int x, int y)
{
    if(x >= h || x < 0 || y >= w || y < 0)
        return false;
    else
        return true;
}

bool isCoverable(int x, int y, char** board)
{
    if((int)board[x][y] == 46)
        return true;
    else
        return false;
}
