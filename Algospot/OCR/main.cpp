#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

double MaxProbSeq(double** memory, int oriNwords, string* original, double** nextChance, double** missChance, string* example, int examNum, int n, int w);

int main()
{
    freopen("input.txt","r",stdin);

    int words, seqs;
    string* texts;
    double** nextChance;
    double** missChance;

    cin >> words >> seqs;

    texts = new string[words];

    for(int i = 0; i < words; i++)
        cin >> texts[i];

    nextChance = new double*[words+1];
    missChance = new double*[words];

    for(int i = 0; i < words + 1; i++)
    {
        nextChance[i] = new double[words];
        memset(nextChance[i], 0, sizeof(double) * words);
    }

    for(int i = 0; i < words; i++)
    {
        missChance[i] = new double[words];
        memset(missChance[i], 0, sizeof(double) * words);
    }

    for(int i = 0; i < words; i++)
        cin >> nextChance[0][i];


    for(int i = 1; i < words + 1; i++)
    {
        for(int j = 0; j < words; j++)
            cin >> nextChance[i][j];
    }
    for(int i = 0; i < words; i++)
    {
        for(int j = 0; j < words; j++)
            cin >> missChance[i][j];
    }

    for(int i = 0; i < seqs; i++)
    {
        int n;
        string* example;
        cin >> n;

        double** memory;
        memory = new double[101];
        for(int j = 0; j < 101; j++)
            memory[j] = new double[words+1];

        for(int j = 0; j < 101; j++)
        {
            for(int k = 0; k < words + 1; k++)
                memory[j][k] = -1;
        }

        example = new string[n];

        for(int j = 0; j < n; j++)
            cin >> example[j];

        cout << "Hello world!" << endl;

        delete example;

        for(int j = 0; j < 101; j++)
            delete [] memory[j];
        delete [] memory;
    }

    delete firstChance;


    for(int i = 0; i < words; i++)
    {
        delete [] nextChance[i];
        delete [] missChance[i];
    }


    delete [] nextChance;
    delete [] missChance;

    return 0;
}

double MaxProbSeq(double** memory, int oriNwords, string* original, double** nextChance, double** missChance, string* example,int examNum, int n, int w)
{
    if(n == 0)
        return nextChance[n][w];

    int target = -1;
    double& answer = memory[n][w];
    double temp = 0;
    if(answer != -1)
        return answer;

    answer = 0;

    for(int i = 0; i < oriNwords; i++)
    {
        answer += nextChance[i][w] * MaxProbSeq(memory,oriNwords,original,nextChance,missChance,example,examNum, n-1 , i);
    }

    for(int i = 0; i < oriNwords; i++)
    {
        if(original[i].compare(example[n-1]) == 0)
        {
            target = i;
            break;
        }
    }

        missChance[w][target]


    return answer;

}
