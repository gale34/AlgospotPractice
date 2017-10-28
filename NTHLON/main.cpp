#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>

using namespace std;

void makeGraph(vector<pair<int, int> > graph[405], vector<pair<int, int> >& runs);
void getRecord(vector<pair<int,int> > graph[405], vector<int>& record,int v);
int main()
{
    //freopen("input.txt","r",stdin);

    int c;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int m;
        vector<pair<int, int> > runs;
        vector<pair<int, int> > graph[405];


        cin >> m;

        for(int j = 0; j < m; j++)
        {
            int a, b;
            cin >> a >> b;

            runs.push_back(make_pair(a,b));
        }

        vector<int> record(405,-1);

        makeGraph(graph,runs);
        getRecord(graph, record,401);

        if(record[200] == -1)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << record[200] << endl;
    }

    return 0;
}

void makeGraph(vector<pair<int, int> > graph[405], vector<pair<int, int> >& runs)
{
    for(int i = 0; i < 405; i++)
        graph[i].clear();
    //graph[0] ~ graph[199] -> -200 ~ -1
    //graph[200] -> 0
    //graph[201] ~ graph[400] -> 1 ~ 200

    const int START = 401;

    for(int i = 0; i < runs.size(); i++)
        graph[START].push_back(make_pair(runs[i].first - runs[i].second + 200, runs[i].first));

    for(int i = 0; i < START; i++)
    {
        for(int j = 0; j < runs.size(); j++)
        {
            int target = i-200 + runs[j].first - runs[j].second;
            if(abs(target) <= 200 && 0 <= abs(target))
                graph[i].push_back(make_pair(target+200, runs[j].first));
        }
    }

    /*for(int i = 0; i < START; i++)
    {
        cout << "start : " << i << " - ";
        for(int j = 0; j < graph[i].size(); j++)
            cout << graph[i][j].first << " ";
        cout <<endl;
    }*/
}

void getRecord(vector<pair<int,int> > graph[405], vector<int>& record,int v)
{
    priority_queue<pair<int, int> > vertex;

    record[v] = 0;

    vertex.push(make_pair(0,v));

    while(!vertex.empty())
    {
        int score = -vertex.top().first;
        int now = vertex.top().second;

        vertex.pop();

        if(record[now] != -1 && record[now] < score)
            continue;
        for(int i = 0; i < graph[now].size(); i++)
        {
            int target = graph[now][i].first;
            int accumRecord = score + graph[now][i].second;
//cout << "t : "<< target << " accRc : " << accumRecord << endl;
            if(record[target] == -1 || record[target] > accumRecord)
            {

                record[target] = accumRecord;
                vertex.push(make_pair(-accumRecord,target));
            }
        }
    }

    /*for(int i = 0; i < 405; i++)
        cout << record[i] << " ";
    cout <<endl;*/

    return ;
}

