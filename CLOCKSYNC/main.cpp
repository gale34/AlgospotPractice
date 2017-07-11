#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int syncSwitch[10][6] = {
{0,0,1,2,-1,-1},
{0,3,7,9,11,-1},
{0,4,10,14,15,-1},
{0,0,4,5,6,7},
{0,6,7,8,10,12},
{0,0,2,14,15,-1},
{0,3,14,15,-1,-1},
{0,4,5,7,14,15},
{0,1,2,3,4,5},
{0,3,4,5,9,13}
};

int minAnswer = 999;
void syncClocks(int* clock, int n);
bool are12(int* clock);

int main()
{
    int c;
    int clock[16];

    //freopen("input.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        for(int j = 0; j < 16; j++)
            cin >> clock[j];

        syncClocks(clock,0);

        if(minAnswer == 999)
            cout << "-1" << endl;
        else
            cout << minAnswer << endl;

        minAnswer = 999;
    }


    return 0;
}

void syncClocks(int* clock,int n)
{
    int answer = 0;

    if(n == 10)
        return ;

    for(int i = 0; i < 4; i++)
    {

        syncSwitch[n][0] = i;

        if(i != 0)
        {
            for(int k = 1; k < 6; k++)
            {
            //cout << syncSwitch[n][k] << " ";

                if(syncSwitch[n][k] == -1)
                    break;
                clock[syncSwitch[n][k]] += 3;
                if(clock[syncSwitch[n][k]] == 15)
                    clock[syncSwitch[n][k]] = 3;
            }

            //cout << endl;
        }

        if(are12(clock))
        {
            for(int k = 0; k < 10; k++)
                answer += syncSwitch[k][0];

            if(minAnswer > answer)
            {
                //for(int k = 0; k < 10; k++)
                  //  cout << syncSwitch[k][0] << " ";
                //cout << endl;
                minAnswer = answer;
            }

        }

        syncClocks(clock,n+1);
    }

    syncSwitch[n][0] = 0;

    for(int k = 1; k < 6; k++)
    {
        if(syncSwitch[n][k] == -1)
            break;
        clock[syncSwitch[n][k]] += 3;

        if(clock[syncSwitch[n][k]] == 15)
            clock[syncSwitch[n][k]] = 3;
    }

    return ;

}

bool are12(int* clock)
{
    for(int k = 0; k < 16; k++)
    {
        if(clock[k] != 12)
            return false;
    }

    return true;
}
