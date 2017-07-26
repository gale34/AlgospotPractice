#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>

using namespace std;

#define INF 10001

int getPILevel(int* cases, string pi);
int getCaseLevel(int* cases, string n);
int char2Int(char c);
int get3Min(int a, int b, int c);

int main()
{
    int c;

    freopen("input.txt","r",stdin);

    int* cases = new int[100000];
    memset(cases, 0, sizeof(int)*100000);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        string pi;

        cin >> pi;

        cout << getPILevel(cases, pi) << endl;

    }

    delete cases;
    return 0;
}

int getPILevel(int* cases, string pi)
{

    if(pi.size() < 3)
        return INF;

    int answer = 0;
    int Idx3 = atoi(pi.substr(0,3).c_str()), Idx4 = atoi(pi.substr(0,4).c_str()), Idx5 = atoi(pi.substr(0,5).c_str());
    int sub3 = INF,sub4 = INF,sub5 = INF;

    if(cases[Idx3] == 0)
        getCaseLevel(cases, pi.substr(0,3));

    if(cases[Idx4] == 0)
        getCaseLevel(cases, pi.substr(0,4));

    if(cases[Idx5] == 0)
        getCaseLevel(cases, pi.substr(0,5));

    /*cout << "pi : " << pi << endl;
    cout << "pi3 : " << pi.substr(0,3) << endl;
    cout << "pi4 : " << pi.substr(0,4) << endl;
    cout << "pi5 : " << pi.substr(0,5) << endl;*/

    if(pi.size() > 5)
        sub5 = getPILevel(cases, pi.substr(6,pi.size()));
    else
        sub5 = 0;

    if(pi.size() > 4)
        sub4 = getPILevel(cases, pi.substr(5,pi.size()));
    else
        sub4 = 0;

    if(pi.size() > 3)
        sub3 = getPILevel(cases, pi.substr(4,pi.size()));
    else
        sub3 = 0;

    answer = get3Min(cases[Idx3] + sub3,cases[Idx4] + sub4, cases[Idx5] + sub5);

    //cout << "answer : " << answer << endl;

    return answer;
}

int getCaseLevel(int* cases, string n)
{
    int index = atoi(n.c_str());
    vector<int> sequence;
    bool isSetLevel = false;
    bool isPlusSign = true;

    for(int i = 0; i < n.size(); i++)
        sequence.push_back(char2Int(n.at(i)));

    for(int i = 1; i < sequence.size(); i++)
    {
        if(sequence[i-1] != sequence[i])
        {
            isSetLevel = false;
            break;
        }
        else
            isSetLevel = true;
    }
    if(isSetLevel)
        return cases[index] = 1;

    if(sequence[0] > sequence[1])
        isPlusSign = false;
    else if(sequence[1] > sequence[0])
        isPlusSign = true;
    else
        return cases[index] = 10;

    for(int i = 2; i < sequence.size(); i++)
    {
        if(isPlusSign && sequence[i] - sequence[i-1] == 1)
            isSetLevel = true;
        else if(!isPlusSign && sequence[i-1] - sequence[i] == 1)
            isSetLevel = true;
        else
        {
            isSetLevel = false;
            break;
        }
    }
    if(isSetLevel)
        return cases[index] = 2;

    for(int i = 2; i < sequence.size(); i++)
    {
        if(sequence[i % 2] == sequence[i])
            isSetLevel = true;
        else
        {
            isSetLevel = false;
            break;
        }
    }
    if(isSetLevel)
        return cases[index] = 4;

    for(int i = 2; i < sequence.size(); i++)
    {
        if(isPlusSign && sequence[i] - sequence[i-1] == sequence[1] - sequence[0])
            isSetLevel = true;
        else if(!isPlusSign && sequence[i-1] - sequence[i] == sequence[0] - sequence[1])
            isSetLevel = true;
        else
        {
            isSetLevel = false;
            break;
        }
    }
    if(isSetLevel)
        return cases[index] = 5;

    return cases[index] = 10;
}

int char2Int(char c)
{
    return c - '0';
}

int get3Min(int a, int b, int c)
{
    if(a >= b && c >= b)
        return b;
    else if(b >= a && c >= a)
        return a;
    else
        return c;
}
