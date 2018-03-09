#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>

using namespace std;

void calMindist(double* distance,vector<vector<pair<double, int> > >& graph);

int main()
{
    cout << fixed;
    cout.precision(10);
    //freopen("input.txt","r",stdin);
    int c;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n,m;
        double* distance;

        vector<vector<pair<double, int> > > graph;

        cin >> n >> m;
        distance = new double[n];
        fill(distance,distance + n,-1.0);

        graph.resize(n);

        for(int j = 0; j < m; j++)
        {
            int a,b;
            double temp;

            cin >> a >> b >> temp;

            graph[a].push_back(make_pair(temp,b));
            graph[b].push_back(make_pair(temp,a));

        }

        calMindist(distance,graph);



        cout << distance[n-1] << endl;
    }

    return 0;
}

void calMindist(double* distance,vector<vector<pair<double, int> > >& graph)
{
    priority_queue<pair<double, int> > order;
    distance[0] = 0;
    order.push(make_pair(0,0));

    while(!order.empty())
    {
        double nowCost = -order.top().first;
        int now = order.top().second;

        //cout << "now Cost?? " << nowCost << endl;

        if(nowCost == 0)
            nowCost = 1;


        order.pop();

        if(now != 0 && distance[now] != -1 && distance[now] < nowCost)
            continue;
        for(int i = 0; i < graph[now].size(); i++)
        {
            double nextDist = nowCost * graph[now][i].first;
            int next = graph[now][i].second;

            //cout << "next : " << next << " cost : " << nowCost <<endl;

            if(distance[next] == -1 || distance[next] > nextDist)
            {
                distance[next] = nextDist;
                order.push(make_pair(-nextDist,next));
            }
        }

        /*cout << "check : " << now << endl;
        for(int j = 0; j < graph.size(); j++)
            cout << j << " : " << distance[j] << endl;*/
    }
    return ;
}
