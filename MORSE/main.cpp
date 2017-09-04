#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

void sol(int** memory, int n, int m, int& k, string answer_seq);
int makeMemory1(int** memory1, int n, int m);
int makeMemory2(int** memory2, int n, int m);

#define MAX_K 1000000100

int main()
{
    int c;
    freopen("input.txt","r",stdin);

    int** memory1;
    int** memory2;
    memory1 = new int*[202];
    memory2 = new int*[202];

    for(int i = 0; i < 202; i++)
    {
        memory1[i] = new int[202];
        memory2[i] = new int[202];
        memset(memory1[i],0,sizeof(int)*202);
        memset(memory2[i],0,sizeof(int)*202);
    }

    cin >> c;

    makeMemory1(memory1,201,201);
    makeMemory2(memory2,201,201);

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
            cout << memory1[i][j] << " ";
        cout << "\n";
    }
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
            cout << memory2[i][j] << " ";
        cout << "\n";
    }
    for(int i = 0; i < c; i++)
    {
        int n,m,k;
        int answer = 0;
        string answer_seq;

        cin >> n >> m >> k;

        k--;
        sol(memory1,n,m,k,answer_seq);
    }


    for(int i = 0; i < 101; i++)
        delete [] memory1[i];
    delete [] memory1;

    for(int i = 0; i < 101; i++)
        delete [] memory2[i];
    delete [] memory2;
    return 0;
}

void sol(int** memory, int n, int m, int& k, string answer_seq)
{
    if(k < 0) return;

    if(n == 0 && m == 0)
    {
        if(k == 0) cout << answer_seq << "\n";
        k--;
        return;
    }

    if(memory[n+m][n] <= k)
    {
        k -= memory[n+m][n];
        return;
    }

    if(n > 0)
        sol(memory,n-1,m,k, answer_seq + "-");
    if(m > 0)
        sol(memory,n,m-1,k, answer_seq + "o");

}

int makeMemory1(int** memory, int n, int m)
{
    for(int i = 0; i <= 200; i++)
    {
        memory[i][0] = memory[i][i] = 1;

        for(int j = 1; j < i; j++)
            memory[i][j] = min(MAX_K, memory[i-1][j-1] + memory[i-1][j]);
    }
}


