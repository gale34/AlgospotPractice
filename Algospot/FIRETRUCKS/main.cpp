#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cstdio>

using namespace std;

int getSumDistFire(vector<vector<pair<int,int> > >& graph, vector<int>& firePlace,int v);

int main()
{
    int c;
    //freopen("input.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int v,e,n,m;
        int answer;
        vector<vector<pair<int,int> > > graph;
        vector<int> firePlace;
        vector<int> fireDept;

        cin >> v >> e >> n >> m;

        graph.resize(v+1);

        for(int j = 0; j < e; j++)
        {
            int a,b,t;

            cin >> a >> b >> t;

            graph[a-1].push_back(make_pair(b-1,t));
            graph[b-1].push_back(make_pair(a-1,t));
        }

        for(int j = 0; j < n; j++)
        {
            int temp;
            cin >> temp;

            firePlace.push_back(temp-1);
        }
        for(int j = 0; j < m; j++)
        {
            int temp;
            cin >> temp;

            fireDept.push_back(temp-1);
            graph[v].push_back(make_pair(temp-1,0));
            graph[temp-1].push_back(make_pair(v,0));
        }

        answer = getSumDistFire(graph, firePlace,v);
        cout <<answer << endl;
    }


    return 0;
}


int getSumDistFire(vector<vector<pair<int,int> > >& graph, vector<int>& firePlace,int v)
{
    int answer = 0;
    int* dist = new int[v+1];
    priority_queue<pair<int, int> > vertex;

    memset(dist,-1,sizeof(int)*(v+1));

    dist[v] = 0;

    vertex.push(make_pair(0,v));

    while(!vertex.empty())
    {
        int distance = -vertex.top().first;
        int now = vertex.top().second;

        vertex.pop();

        if(dist[now] != -1 && dist[now] < distance)
            continue;
        for(int i = 0; i < graph[now].size(); i++)
        {
            int target = graph[now][i].first;
            int nextDist = distance + graph[now][i].second;

            if(dist[target] == -1 || dist[target] > nextDist)
            {
                dist[target] = nextDist;
                vertex.push(make_pair(-nextDist,target));
            }
        }
    }

    for(int i = 0; i < firePlace.size(); i++)
        answer += dist[firePlace[i]];
    return answer;
}
