#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

int getIncSubSeq(const vector<int>& seq, int* memory, int s);
int getMax(int a, int b);

int main()
{
    int c,n;

    //freopen("input.txt", "r", stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int x;
        vector<int> sequence;
        int* memory;
        int answer = 0;

        cin >> n;

        memory = new int[n];

        memset(memory,0,sizeof(int)*n);

        for(int j = 0; j < n; j++)
        {
            cin >> x;
            sequence.push_back(x);
        }

        for(int j = 0; j < n; j++)
            answer = getMax(answer,getIncSubSeq(sequence,memory,j));

        cout << answer << endl;
        sequence.clear();

        delete memory;
    }

    return 0;
}

int getIncSubSeq(const vector<int>& seq, int* memory, int s)
{
    int& answer = memory[s];

    if(answer != 0)
        return answer;

    answer = 1;

    for(int i = s + 1; i < seq.size(); i++)
    {
        if(seq[s] < seq[i])
            answer = getMax(answer, getIncSubSeq(seq,memory,i) + 1);
    }

    return answer;

    /*if(seq.empty())
        return 0;

    int answer = 0;
    vector<int> subSeq;

    for(int i = 0; i < seq.size(); i++)
    {
        vector<int> subSeq;
        for(int j = i + 1; j < seq.size(); j++)
        {
            if(seq[j] > seq[i])
                subSeq.push_back(seq[j]);
        }
        answer = getMax(answer, getIncSubSeq(subSeq) + 1);
    }

    return answer;*/
}

int getMax(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
