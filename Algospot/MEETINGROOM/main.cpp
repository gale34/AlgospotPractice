#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdio>

using namespace std;

bool isOverrapped(const pair<int,int>& a, const pair<int,int>& b);

void makeGraph(const vector<pair<int,int> >& meetingTime, vector<vector<int> >& graph);
vector<int> tarjanSCC(vector<vector<int> >& graph, vector<int>& visited, stack<int>& stackSCC, vector<int>& sccId);
int scc(vector<vector<int> >& graph, vector<int>& visited, stack<int>& stackSCC, vector<int>& sccId, int idx);
vector<int> solve2SAT(vector<vector<int> >& graph);

int sccCounter, vertexCounter;

int main()
{
    int c;
    freopen("input.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n;
        vector<vector<int> > graph;
        vector<pair<int,int> > meetingTime;
        vector<int> answer;

        cin >> n;

        for(int j = 0; j < n; j++)
        {
            int a, b;
            cin >> a >> b;
            meetingTime.push_back(make_pair(a,b));

            cin >> a >> b;
            meetingTime.push_back(make_pair(a,b));
        }

        makeGraph(meetingTime,graph);
        answer = solve2SAT(graph);

        if(answer.empty())
        {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        else
            cout << "POSSIBLE" << endl;

        for(int j = 0; j < answer.size(); j++)
            cout << answer[j] << " ";
        cout << endl;
    }

    return 0;
}

bool isOverrapped(const pair<int,int>& a, const pair<int,int>& b)
{
    return !(a.second <= b.first || b.second <= a.first);
}

void makeGraph(const vector<pair<int,int> >& meetingTime, vector<vector<int> >& graph)
{
    graph.clear();
    graph.resize(meetingTime.size() * 2);

    for(int i = 0; i < meetingTime.size(); i+= 2)
    {
        int j = i + 1;
        graph[i*2 + 1].push_back(j * 2); // i*2 + 1 : no weekly meeting time -> j*2 = i*2 + 2 : monthly meeting time
        graph[j*2 + 1].push_back(i * 2); // j*2 + 1 = i*2 + 3 : no monthly meeting time -> i*2 : weekly meeting time
    }

    for(int i = 0; i < meetingTime.size(); i++)
    {
        for(int j = 0; j < i; ++j)
        {
            if(isOverrapped(meetingTime[i],meetingTime[j]))
            {
                graph[i*2].push_back(j*2 + 1);
                graph[j*2].push_back(i*2 + 1);
            }
        }
    }
}

vector<int> tarjanSCC(vector<vector<int> >& graph, vector<int>& visited, stack<int>& stackSCC, vector<int>& sccId)
{
    sccId = visited = vector<int>(graph.size(), -1);

    sccCounter = vertexCounter = 0;

    for(int i = 0; i < graph.size(); i++)
        if(visited[i] == -1)
            scc(graph,visited,stackSCC,sccId,i);
    return sccId;
}

int scc(vector<vector<int> >& graph, vector<int>& visited, stack<int>& stackSCC, vector<int>& sccId, int idx)
{
    int answer = visited[idx] = vertexCounter++;
    stackSCC.push(idx);

    for(int i = 0; i < graph[idx].size(); i++)
    {
        int next = graph[idx][i];

        if(visited[next] == -1)
            answer = min(answer, scc(graph,visited,stackSCC,sccId,next));
        else if(sccId[next] == -1)
            answer = min(answer,visited[next]);
    }

    if(answer == visited[idx])
    {
        while(1)
        {
            int t = stackSCC.top();
            stackSCC.pop();
            sccId[t] = sccCounter++;

            if(t == idx)
                break;
        }
        sccCounter++;
    }
    return answer;
}

vector<int> solve2SAT(vector<vector<int> >& graph)
{
    int n = graph.size() / 2;
    vector<int> visited;
    stack<int> stackSCC;
    vector<int> sccId;

    vector<int> label = tarjanSCC(graph,visited,stackSCC,sccId);

    for(int i = 0; i < 2 * n; i += 2)
    {
        if(label[i] == label[i+1])
            return vector<int>();
    }

    vector<int> value(2*n, -1);

    vector<pair<int,int> > order;

    for(int i = 0; i < 2 * n; i++)
        order.push_back(make_pair(-label[i],i));

    sort(order.begin(), order.end());

    for(int i = 0; i < 2*n; i++)
    {
        int vertex = order[i].second;
        int variable = vertex / 2;
        int isTrue = vertex % 2 == 0;
        if(value[variable] != -1)
            continue;

        value[variable] = !isTrue;
    }
    return value;
}
