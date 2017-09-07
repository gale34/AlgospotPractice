#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

unsigned int getNextNumber(int preNumber);
int getSumOfK(int n, int k);

int main()
{
    freopen("input.txt", "r", stdin);

    int c;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int k,n;
        int answer = 0;

        cin >> k >> n;

        answer = getSumOfK(n, k);

        cout << answer << endl;
    }
    return 0;
}

unsigned int getNextNumber(int preNumber)
{
    return preNumber * 214013 + 2531011;
}

int getSumOfK(int n, int k)
{
    unsigned int start = 1983;
    unsigned int sum = 0;

    int answer = 0;

    queue<unsigned int> seq;

    for(int i = 0; i < n; i++)
    {
        seq.push(start);
        sum += seq.back() % 10000 + 1;

        while(sum > k)
        {
            sum -= seq.front() % 10000 + 1;
            seq.pop();
        }

        if(sum == k)
            answer++;

        start = getNextNumber(start);
    }

    return answer;
}
