#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int answer = 0;

bool matchingCouple(bool* isCoupled,int** friends,int n);

int main()
{
    int c, n, m;

    //freopen("inputPicnic.txt", "r", stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int** friends;
        bool* isCoupled;
        int x,y;

        cin >> n >> m;

        friends = new int*[n];
        isCoupled = new bool[n];


        for(int i = 0; i < n; i++)
        {
            friends[i] = new int[n];
            memset(friends[i], 0, sizeof(int)*n);
            isCoupled[i] = false;
        }

        for(int j = 0; j < m; j++)
        {
            cin >> x >> y;

            friends[x][y] = 1;
            friends[y][x] = 1;
        }

        matchingCouple(isCoupled,friends,n);

        cout << answer << endl;

        answer = 0;

        for(int i = 0; i < n; i++)
            delete [] friends[i];
        delete [] friends;
    }


    return 0;
}

bool matchingCouple(bool* isCoupled,int** friends,int n)
{
    int i = 0;

    for(i = 0; i < n; i++)
    {
        if(isCoupled[i] == false)
            break;
    }
    if(i == n)
    {
        answer++;
        return true;
    }

    for(int l = i+1; l < n; l++)
    {
        if(isCoupled[l] == false && friends[l][i] == true)
        {
            isCoupled[l] = true;
            isCoupled[i] = true;
            //cout << "(" << i << "," << l << ")" << endl;
            matchingCouple(isCoupled,friends,n);
            isCoupled[l] = false;
            isCoupled[i] = false;
        }
    }

}
