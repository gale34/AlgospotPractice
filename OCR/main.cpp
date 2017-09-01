#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
    freopen("input.txt","r",stdin);

    int words, seqs;
    string* texts;
    double* firstChance;
    double** nextChance;
    double** missChance;

    cin >> words >> seqs;

    texts = new string[words];

    for(int i = 0; i < words; i++)
        cin >> texts[i];

    firstChance = new double[words];
    nextChance = new double*[words];
    missChance = new double*[words];

    for(int i = 0; i < words; i++)
    {
        nextChance[i] = new double[words];
        missChance[i] = new double[words];
        memset(nextChance[i], 0, sizeof(double) * words);
        memset(missChance[i], 0, sizeof(double) * words);
    }

    for(int i = 0; i < words; i++)
        cin >> firstChance[i];


    for(int i = 0; i < words; i++)
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

        example = new string[n];

        for(int j = 0; j < n; j++)
            cin >> example[j];

        cout << "Hello world!" << endl;

        delete example;
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
