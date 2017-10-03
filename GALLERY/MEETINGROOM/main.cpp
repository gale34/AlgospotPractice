#include <iostream>
#include <vector>

using namespace std;

bool isOverrapped(const pair<int,int>& a, const pair<int,int>& b);

void makeGraph(const vector<pair<int,int> >& meetingTime, vector<vector<int> >& graph);
int main()
{
    int c;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n;
        vector<vector<int> > graph;
        vector<pair<int,int> > meetingTime;

        cin >> n;

        for(int j = 0; j < n; j++)
        {
            int a, b;
            cin >> a >> b;
            meetingTime.push_back(make_pair(a,b));

            cin >> a >> b;
            meetingTime.push_back(make_pair(a,b));
        }
    }
    cout << "Hello world!" << endl;
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
