#include <iostream>
#include <cstdio>
#include <cstring>

#define MAX_TOWN_NUMBER 51
#define MAX_DAYS 101

using namespace std;

double traceCriminal(bool** town, double** memory, int* numAdjacentTown, int days, int townNumber, int startTown, int maxTownNumber);

int main()
{
    int c, n, d, p, t;

    //freopen("input.txt","r",stdin);
    cout.precision(10);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        bool** town;
        double** memory;
        int* q_town;
        int* numAdjacentTown;

        memory = new double*[MAX_TOWN_NUMBER];
        for(int j = 0; j < MAX_TOWN_NUMBER; j++)
        {
            memory[j] = new double[MAX_DAYS];
            for(int k = 0; k < MAX_DAYS; k++)
                memory[j][k] = -1;
        }

        cin >> n >> d >> p;

        numAdjacentTown = new int[n];
        town = new bool*[n];
        for(int j = 0; j < n; j++)
            town[j] = new bool[n];

        for(int j = 0; j < n; j++)
        {
            int cnt = 0;
            for(int k = 0; k < n; k++)
            {
                cin >> town[j][k];
                if(town[j][k] == 1)
                    cnt++;
            }
            numAdjacentTown[j] = cnt;
        }

        cin >> t;

        q_town = new int[t];


        for(int j = 0; j < t; j++)
        {
            cin >> q_town[j];
            cout << traceCriminal(town,memory,numAdjacentTown,d,q_town[j],p,n) << " ";
        }
        cout << endl;

        delete numAdjacentTown;
        delete q_town;

        for(int j = 0; j < MAX_TOWN_NUMBER; j++)
            delete [] memory[j];
        delete [] memory;

        for(int j = 0; j < n; j++)
            delete [] town[j];
        delete [] town;

    }
    return 0;
}

double traceCriminal(bool** town, double** memory, int* numAdjacentTown, int days, int townNumber, int startTown, int maxTownNumber)
{
    if(days == 0)
    {
        if(startTown == townNumber)
            return 1;
        else
            return 0;
    }

    double& answer = memory[townNumber][days];

    if(answer != -1)
        return answer;

    answer = 0;

    for(int i = 0; i < maxTownNumber; i++)
    {
        if(town[i][townNumber] == 1)
            answer += traceCriminal(town, memory,numAdjacentTown, days - 1, i, startTown, maxTownNumber) / (double)numAdjacentTown[i];
    }

    return answer;
}
