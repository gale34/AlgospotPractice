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
            //map<int,int>::iterator it;

            cin >> a >> b;
            nerds[a] = b;

            answer += getParticipants(nerds,a);

            /*for(it = nerds.begin(); it != nerds.end(); it++)
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
    int temp = 0;

    if(nerds.upper_bound(idx) != nerds.end())
    {
        if(nerds[idx] < nerds.upper_bound(idx)->second)
        {
            nerds.erase(nerds.lower_bound(idx));
            return (int)nerds.size();
        }
    }

    temp = (nerds.begin()->first + idx) / 2;

    while(nerds.lower_bound(temp)->first != idx)
    {
        //cout << "temp : " << temp << endl;

        if(nerds.lower_bound(temp)->second > nerds[idx] && nerds.upper_bound(temp)->second <= nerds[idx])
            break;

        if(nerds.find(idx)->second > nerds.lower_bound(temp)->second)
            temp = (nerds.begin()->first + temp) / 2;
        else
            temp = (temp + idx) / 2;

        if(temp == nerds.begin()->first)
            break;
    }


    for(i = nerds.lower_bound(idx-1); i != nerds.begin(); i--)
    {
        if(nerds[idx] > i->second)
        {
            nerds.erase(i);
            break;
        }
    }

    return (int)nerds.size();
}
