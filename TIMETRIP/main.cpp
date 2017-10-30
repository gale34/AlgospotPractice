#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

void getAnswer(vector<vector<pair<int, int> > >& graph,vector<int>& fast,vector<int>& slow);
bool checkPath(vector<vector<pair<int, int> > >& graph,int start, int dest);

const int INF = 100000000;


int main()
{
    freopen("input.txt","r",stdin);
    int c;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int v,w;
        vector<vector<pair<int, int> > > graph;
        vector<int> fast;
        vector<int> slow;

        cin >> v >> w;

        graph.resize(v);
        slow.resize(v,-INF);
        fast.resize(v,INF);

        for(int j = 0; j < w; j++)
        {
            int start, dest, dist;

            cin >> start >> dest >> dist;

            graph[start].push_back(make_pair(dest, dist));
        }

        getAnswer(graph,fast,slow);

        if(fast.empty())
            cout << "INFINITY";
        else if(fast[1] == INF)
        {
            cout << "UNREACHABLE" << endl;
            continue;
        }
        else
            cout << fast[1];

        if(slow.empty())
            cout << " INFINITY" << endl;
        else
            cout << " " << slow[1] << endl;
    }


    return 0;
}

void getAnswer(vector<vector<pair<int, int> > >& graph,vector<int>& fast,vector<int>& slow)
{
    bool isUpdated = false;

    slow[0] = 0;
    fast[0] = 0;
    for(int i = 0; i < graph.size() - 1; i++)
    {
        isUpdated = false;
        for(int j = 0; j < graph.size(); j++)
        {
            for(int k = 0 ; k < graph[j].size(); k++)
            {
                int target = graph[j][k].first;
                int dist = graph[j][k].second;
                if(fast[target] > fast[j] + dist)
                {
                    fast[target] = fast[j] + dist;
                    isUpdated = true;
                }
                if(slow[target] < slow[j] + dist)
                {
                    slow[target] = slow[j] + dist;
                    isUpdated = true;
                }
            }
        }

        if(!isUpdated) break;
    }

    //cout << "test" << endl;
    //cout << fast[1] << " " << slow[1] <<endl;

    for(int j = 0; j < graph.size(); j++)
    {
        for(int k = 0 ; k < graph[j].size(); k++)
        {
            int target = graph[j][k].first;
            int dist = graph[j][k].second;
            if(!slow.empty() && slow[target] < slow[j] + dist)
            {
                if(checkPath(graph,0,target) && checkPath(graph,target,1))
                    slow.clear();
            }
            if(!fast.empty() && fast[target] > fast[j] + dist)
            {
                if(checkPath(graph,0,target) && checkPath(graph,target,1))
                    fast.clear();
            }
        }
    }

    return ;
}

bool checkPath(vector<vector<pair<int, int> > >& graph,int start, int dest)
{
    bool isAnswer = false;

    vector<bool> isVisited(graph.size(),0);
    queue<int> savesave;

    isVisited[start] = 1;

    savesave.push(start);

    while(!savesave.empty())
    {
        int temp = savesave.front();
        savesave.pop();

        isVisited[temp] = 1;
        for(int i = 0; i < graph[temp].size(); i++)
        {
            int temp2 = graph[temp][i].first;
            if(isVisited[temp2] == 0)
            savesave.push(temp2);
        }
    }

    if(isVisited[dest] == 0)
        return false;
    else
        return true;
}
