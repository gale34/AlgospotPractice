#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int getTilings(int* tiles, int n, int start);
int getAsymyilings(int* tiles, int* asymtiles, int n, int start);

int main()
{
    int c,n;
    int* tiles;
    int* asymtiles;
    int a = 0, b = 0;

    tiles = new int[101];
    memset(tiles,0,sizeof(int)*(101));
    asymtiles = new int[101];
    memset(asymtiles,-1,sizeof(int)*(101));

    //freopen("input.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        cin >> n;

        a = getTilings(tiles,n,n) % 1000000007;
        b = getAsymyilings(tiles, asymtiles,n,n) % 1000000007;
        if(a < b)
            cout << a + 1000000007 - b << endl;
        else
            cout << a - b << endl;

        //cout << (getTilings(tiles,n,n) % 1000000007) - (getAsymyilings(tiles, asymtiles,n,n) % 1000000007) << endl;
        //cout << (getTilings(tiles,n,n) % 1000000007)<< endl;
        //cout << (getAsymyilings(tiles, asymtiles,n,n) % 1000000007) << endl;
    }

    delete tiles;
    delete asymtiles;

    return 0;
}

int getTilings(int* tiles, int n, int start)
{
    if(start == 0)
        return 0;

    int& answer = tiles[start];

    if(answer != 0)
        return answer;

    if(start == 1)
        return answer = 1;
    else if(start == 2)
        return answer = 2;
    else
        return answer = (getTilings(tiles,n,start - 1)%1000000007)+ (getTilings(tiles,n,start - 2) % 1000000007);
}

int getAsymyilings(int* tiles, int* asymtiles, int n, int start)
{
    if(start == 0)
        return 0;

    int& answer = asymtiles[start];

    if(answer != -1)
        return answer;

    if(start == 1)
        return answer = 1;
    else if(start == 2)
        return answer = 2;
    else if(start % 2 == 0)
        return answer = (getTilings(tiles,n/2,n/2)%1000000007) + (getTilings(tiles,n/2 - 1,n/2 - 1)%1000000007);
    else
        return answer = (getTilings(tiles,n/2,n/2)%1000000007);

}
