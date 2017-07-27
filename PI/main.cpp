#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

#define INF 123456

int getPILevel(int* cases, string pi, int start);
int getCaseLevel(string n, int start, int finish);

int main()
{
    int c;

    //freopen("input2.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int* cases = new int[10001];
        memset(cases, 0, sizeof(int)*10001);

        string pi;

        cin >> pi;

        cout << getPILevel(cases, pi, 0) << endl;

        //for(int i = 0; i < pi.size(); i++)
            //cout << i << "ith : " << cases[i] << endl;

        delete cases;
    }
    return 0;
}

int getPILevel(int* cases, string pi, int start)
{

    if(start == pi.size())
        return 0;

    int& answer = cases[start];

    if(answer != 0)
        return answer;
    answer = INF;

    for(int i = 0; i < 3; i++)
    {
        int a = 0;
        int b = 0;
        if((start + i + 3) <= pi.size())
        {
            a = getCaseLevel(pi,start,i+3);

            //cout << "start : " << start << " " << i + 3 << "th " << "a : " << a << endl;
            b = getPILevel(cases, pi,start+i+3);
            //cout << "start : " << start << " " << i + 3 << "th " << " b : " << b << endl;
            a += b;
            answer = min(answer, a);
        }
    }
    return answer;
}

int getCaseLevel(string n, int start, int finish)
{
    string testStr = n.substr(start,finish);

    bool isSetLevel = false;
    bool isPlusSign = true;

    for(int i = 1; i < testStr.size(); i++)
    {
        if(testStr[i-1] != testStr[i])
        {
            isSetLevel = false;
            break;
        }
        else
            isSetLevel = true;
    }
    if(isSetLevel)
        return 1;

    for(int i = 2; i < testStr.size(); i++)
    {
        if(testStr[i] - testStr[i-1] == testStr[i-1] - testStr[i-2])
        {
            isPlusSign = true;
            isSetLevel = true;
        }
        else
        {
            isPlusSign = false;
            isSetLevel = false;
            break;
        }
    }
    if(isSetLevel && abs(testStr[1] - testStr[0]) == 1)
        return 2;

    for(int i = 2; i < testStr.size(); i++)
    {
        if(testStr[i % 2] == testStr[i])
            isSetLevel = true;
        else
        {
            isSetLevel = false;
            break;
        }
    }
    if(isSetLevel)
        return 4;

    if(isPlusSign)
        return 5;

    return 10;
}
