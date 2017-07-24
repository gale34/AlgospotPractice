#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

int getIncSubSeq(const vector<int>& seq1, const vector<int>& seq2, int** memory, int s1, int s2);
int getMax(int a, int b);
int getMin(int a, int b);

int main()
{
    int c,n,m;

    freopen("input.txt", "r", stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int x;
        vector<int> sequence1, sequence2;
        int** memory;
        int answer = 0;

        cin >> n >> m;

        memory = new int*[n];

        for(int j = 0; j < n; j++)
        {
            memory[j] = new int[m];
            memset(memory[j],0,sizeof(int)*m);
        }

        for(int j = 0; j < n; j++)
        {
            cin >> x;
            sequence1.push_back(x);
        }
        for(int j = 0; j < m; j++)
        {
            cin >> x;
            sequence2.push_back(x);
        }


        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < m; k++)
                answer = getMax(answer,getIncSubSeq(sequence1,sequence2,memory,j,k));
        }

        cout << answer << endl;
        sequence1.clear();
        sequence2.clear();

        for(int j = 0; j < n; j++)
            delete [] memory[j];
        delete memory;
    }

    return 0;
}

int getIncSubSeq(const vector<int>& seq1, const vector<int>& seq2, int** memory, int s1, int s2)
{
    int& answer = memory[s1][s2];
    long long Val;

    if(answer != 0)
        return answer;

    //cout << " s1 : " << s1 << " s2 : " << s2 << " answer : " << answer << endl;

    /*if(seq1[s1] == seq2[s2])
    {
        answer = 1;
        Val = (long long)seq1[s1];
    }
    else
    {*/
        answer = 1;
        Val = (long long)getMin(seq1[s1], seq2[s2]);
    //}

    //cout << "Val : " << Val << " s1 : " << s1 << " s2 : " << s2 << " answer : " << answer << endl;
    //cout << endl;

    for(int i = s1 + 1; i < seq1.size(); i++)
    {
        if(Val < seq1[i])
            answer = getMax(answer, getIncSubSeq(seq1,seq2,memory,i,s2) + 1);
    }
    for(int i = s2 + 1; i < seq2.size(); i++)
    {
        if(Val < seq2[i])
            answer = getMax(answer, getIncSubSeq(seq1,seq2,memory,s1,i) + 1);
    }

    return answer;

}

int getMax(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int getMin(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}
