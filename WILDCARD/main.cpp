#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

bool isWildcard(string wildcard, string target);
string erase2Asterisk(string target);

int main()
{
    int c;
    //freopen("input.txt","r", stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n;
        string wildcard;
        string temp;
        vector<string> fileNames;
        vector<string>::iterator ptr;

        cin >> wildcard;
        cin >> n;

        for(int j = 0; j < n; j++)
        {
            cin >> temp;
            fileNames.push_back(temp);
        }

        sort(fileNames.begin(),fileNames.end());

        wildcard = erase2Asterisk(wildcard);

        for(int j = 0; j < n; j++)
        {
            if(isWildcard(wildcard,fileNames[j]))
                cout << fileNames[j] << endl;
        }

    }

    return 0;
}

bool isWildcard(string wildcard, string target)
{

    int w_ptr = 0, t_ptr = 0;

    while(1)
    {
        if(w_ptr >= wildcard.size() && t_ptr >= target.size())
            return true;
        else if(w_ptr == wildcard.size() && t_ptr != target.size())
            return false;
        else if(t_ptr == target.size() && w_ptr != wildcard.size())
        {
            if((int)wildcard.at(w_ptr) == 42 && w_ptr == wildcard.size() - 1)
                return true;
            return false;
        }
        else
        {
            if((int)wildcard.at(w_ptr) != 42)
            {
                if((int)wildcard.at(w_ptr) == (int)target.at(t_ptr) || (int)wildcard.at(w_ptr) == 63)
                {
                    w_ptr++;
                    t_ptr++;
                }
                else
                    return false;
            }
            else if((int)wildcard.at(w_ptr) == 42)
            {
                if(w_ptr == wildcard.size() - 1)
                    return true;
                else
                {
                    int temp_ptr = w_ptr+1;
                    while(t_ptr < target.size())
                    {
                        if(isWildcard(wildcard.substr(temp_ptr),target.substr(t_ptr)))
                            return true;
                        t_ptr++;
                    }
                }
            }
        }
    }

}

string erase2Asterisk(string target)
{
    bool isOverrapped = false;

    for(int i = 0; i < target.length(); i++)
    {
        char c = target.at(i);

        if(c == '*')
        {
            if(isOverrapped == false)
                isOverrapped = true;
            else
                target.erase(i--,1);
        }
        else
        {
            if(isOverrapped == true)
                isOverrapped = false;
        }
    }

    return target;
}
