#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

double snailMem[1001][2002];

double getSnailAnswer(int n, int m, int x, int y);

int main()
{
    int c, n, m;
    //freopen("input.txt", "r", stdin);

    cin >> c;

    for(int j = 0; j < 1001; j++)
        memset(snailMem[j],-1,sizeof(double)*2002);

    cout.precision(10);

    for(int i = 0; i < c; i++)
    {
        cin >> n >> m;

        cout << getSnailAnswer(n, m,0,0) << endl;

        for(int j = 0; j < 1001; j++)
            memset(snailMem[j],-1,sizeof(double)*2002);
    }

    return 0;
}

double getSnailAnswer(int depth, int days, int dx, int dy)
{
    if(dy >= days)
    {
        if(dx >= depth)
            return 1;
        else
            return 0;
    }

    if(dx >= depth)
        return 1;

    double& answer = snailMem[dx][dy];


    if(answer >= 0)
        return answer;

    answer = (0.75 * getSnailAnswer(depth,days,dx+2,dy+1)) + (0.25 * getSnailAnswer(depth,days,dx+1,dy+1));


    //cout << " x : " << dx << " y : " << dy << " " << answer << endl;

    return answer;
}
