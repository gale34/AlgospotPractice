#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

string getMinGifts(vector<int>& dI, int n, int m);
int getNextVertex(int n, int now, int appendNumber);

int main()
{
    freopen("input.txt","r",stdin);

    int t;

    cin >> t;

    for(int i = 0; i < t; i++)
    {
        string d;
        int n, m;
        vector<int> dI;
        vector<vector<int> > graph;
        string answer;

        cin >> d >> n >> m;

        graph.resize(n);

        for(int j = 0; j < d.size(); j++)
            dI.push_back(d[j] - '0');

        sort(dI.begin(), dI.end());

        answer = getMinGifts(dI,n,m);

        cout << answer << endl;
    }
    return 0;
}

string getMinGifts(vector<int>& dI, int n, int m)
{
    int now;

    queue<int> bfs;
    vector<int> parent(2*n,-1);
    vector<int> digitChoice(2*n,-1);
    string answer;

    bfs.push(0);
    parent[0] = 0;

    while(!bfs.empty())
    {
        now = bfs.front();
        bfs.pop();

        for(int i = 0; i < dI.size(); i++)
        {
            int next = getNextVertex(n,now,dI[i]);
            if(parent[next] == -1)
            {
                bfs.push(next);
                parent[next] = now;
                digitChoice[next] = dI[i];
            }
        }
    }

    int path = n+m;

    if(parent[path] == -1)
        return "IMPOSSIBLE";

    while(parent[path] != path)
    {
        answer += (char)('0' + digitChoice[path]);
        path = parent[path];
    }
    reverse(answer.begin(),answer.end());

    return answer;
}

int getNextVertex(int n, int now, int appendNumber)
{
    int next = 0;

    next = now*10 + appendNumber;
    if(next >= n) // >= n+m이 아닌 이유는 어차피 parent[n + m]식으로 저장되기 때문
        return n + next % n;
    return next % n;
}
