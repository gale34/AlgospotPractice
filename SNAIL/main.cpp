#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

double snailMem[1001][1001];

double getSnailAnswer(int n, int m, int x, int y);

int main()
{
    int c, n, m;
    freopen("input.txt", "r", stdin);

    cin >> c;

    for(int i = 0; i < 1001; i++)
        memset(snailMem[i],0,sizeof(double)*1001);

    cout.precision(10);

    for(int i = 0; i < c; i++)
    {
        cin >> n >> m;

        cout << getSnailAnswer(n, m,0,0) << endl;
    }

    return 0;
}

double getSnailAnswer(int n, int m, int x, int y)
{
    if(y >= m)
        return 0;

    if(x >= n)
        return 1;

    double& answer = snailMem[x][y];

    if(answer != 0)
        return answer;

    answer = (0.75 * getSnailAnswer(n,m,x+2,y+1)) + (0.25 * getSnailAnswer(n,m,x+1,y+1));

    cout << "t : " << answer << endl;

    return answer;
}
