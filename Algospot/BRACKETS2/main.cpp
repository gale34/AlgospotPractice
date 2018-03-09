#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>

using namespace std;

bool IsPerfectBracket(string bracket);

int main()
{
    int c;
    freopen("input.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        string bracket;

        cin >> bracket;

        if(IsPerfectBracket(bracket))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}

bool IsPerfectBracket(string bracket)
{
    stack<char> box;

    for(int i = 0; i < bracket.size(); i++)
    {
        if(box.empty())
        {
            if((int)bracket.at(i) == 41 || (int)bracket.at(i) == 93 ||
               (int)bracket.at(i) == 125 )
                return false;
        }

        if((int)bracket.at(i) == 40 || (int)bracket.at(i) == 91 ||
            (int)bracket.at(i) == 123 )
        {
            box.push(bracket.at(i));
            continue;
        }

        if(((int)box.top() == 40 && (int)bracket.at(i) == 41)
           || ((int)box.top() == 91 && (int)bracket.at(i) == 93)
           || ((int)box.top() == 123 && (int)bracket.at(i) == 125))
            box.pop();
        else
            return false;
    }

    if(!box.empty())
        return false;
    else
        return true;
}
