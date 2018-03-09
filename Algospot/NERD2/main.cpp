#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int getParticipants(map<int,int>& nerds, int idx);

int main()
{
    int c;

    freopen("input.txt","r",stdin);

    map<int, int> nerds;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n;
        int answer = 0;
        cin >> n;

        for(int j = 0; j < n; j++)
        {
            int a, b;


            cin >> a >> b;
            nerds[a] = b;

            answer += getParticipants(nerds,a);

            /*map<int,int>::iterator it;
            for(it = nerds.begin(); it != nerds.end(); it++)
                cout << "x : " << it->first << " y : " << it->second << endl;
            cout << answer << endl;*/
        }
        nerds.clear();

        cout << answer << endl;
    }
    return 0;
}

int getParticipants(map<int,int>& nerds, int idx)
{
    if(nerds.size() == 1)
        return 1;

    map<int,int>::iterator i;

    if(nerds.upper_bound(idx) != nerds.end())
    {
        if(nerds[idx] < nerds.upper_bound(idx)->second)
        {
            nerds.erase(nerds.lower_bound(idx));
            return (int)nerds.size();
        }
    }

    i = nerds.lower_bound(idx);
    if(i == nerds.begin())
        return (int)nerds.size();
    else
        i--;
    while(1)
    {
        map<int,int>::iterator j;
        //cout << "test : " << i->second << endl;
        if(nerds[idx] > i->second)
        {

            if(i != nerds.begin())
            {
                j = i;
                j--;
                nerds.erase(i);
                i = j;
            }
            else
            {
                nerds.erase(i);
                break;
            }
        }
        else
            break;
    }

    return (int)nerds.size();
}
