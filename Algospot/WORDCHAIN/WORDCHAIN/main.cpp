#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

vector<vector<int> > adj;
vector<string> graph[26][26];
vector<int> indegree, outdegree;

void makeGraph(const vector<string>& wordList);
void getEullerCircult(int here, vector<int>& circuit);
bool checkEuler();
string solve(const vector<string>& wordList);

int main()
{
    //freopen("input.txt","r",stdin);

    int c;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n;
        vector<string> wordList;
        string answer = "";

        cin >> n;

        for(int j = 0; j < n; j++)
        {
            string temp;

            cin >> temp;
            wordList.push_back(temp);
        }

        answer = solve(wordList);
        cout << answer <<endl;
    }

    return 0;
}

void makeGraph(const vector<string>& wordList)
{
    for(int i = 0; i < 26; i++)
        for(int j = 0; j < 26; j++)
            graph[i][j].clear();

    adj = vector<vector<int> >(26, vector<int>(26,0));
    indegree = outdegree = vector<int>(26,0);

    for(int i = 0; i < wordList.size(); i++)
    {
        int a = wordList[i][0] - 'a';
        int b = wordList[i][wordList[i].size()-1] - 'a';
        graph[a][b].push_back(wordList[i]);
        adj[a][b]++;
        outdegree[a]++;
        indegree[b]++;
    }
}

void getEulerCircuit(int here, vector<int>& circuit)
{
    for(int there = 0; there < adj.size(); there++)
        while(adj[here][there] > 0)
        {
            adj[here][there]--;
            getEulerCircuit(there,circuit);
        }
    circuit.push_back(here);
}

vector<int> getEulerTrailOrCircuit()
{
    vector<int> circuit;

    for(int i = 0; i < 26; i++)
    {
        if(outdegree[i] == indegree[i]+1)
        {
            getEulerCircuit(i,circuit);
            return circuit;
        }
    }

    for(int i = 0; i < 26; i++)
    {
        if(outdegree[i])
        {
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }
    return circuit;
}

bool checkEuler()
{
    int plus1 = 0;
    int minus1 = 0;

    for(int i = 0; i < 26; i++)
    {
        int delta = outdegree[i] - indegree[i];

        if(delta < -1 || 1 < delta)
            return false;
        if(delta == 1)
            plus1++;
        if(delta == -1)
            minus1++;
    }
    return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

string solve(const vector<string>& wordList)
{
    makeGraph(wordList);
    if(!checkEuler())
        return "IMPOSSIBLE";

    vector<int> circuit = getEulerTrailOrCircuit();

    if(circuit.size() != wordList.size() + 1)
        return "IMPOSSIBLE";

    reverse(circuit.begin(), circuit.end());
    string ret;

    for(int i = 1; i < circuit.size(); i++)
    {
        int a = circuit[i-1], b = circuit[i];
        if(ret.size())
            ret += " ";
        ret += graph[a][b].back();
        graph[a][b].pop_back();
    }
    return ret;
}


/*vector<string> getWordChain(int** wordGraph, vector<string>& wordList);
void checkWords(int* visited, int** wordGraph, vector<string>& wordList, vector<string>& answer, int idx);

int main()
{
    freopen("input.txt","r",stdin);

    int c;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n;
        vector<string> answer;
        int* visited;
        vector<string> wordList;
        int** wordGraph;

        cin >> n;

        wordGraph = new int*[n];
        for(int j = 0; j < n; j++)
        {
            wordGraph[j] = new int[n];
            memset(wordGraph[j],0,sizeof(int)*n);
        }

        visited = new int[n];
        memset(visited, 0, sizeof(int)*n);

        for(int j = 0; j < n; j++)
        {
            string temp;

            cin >> temp;
            wordList.push_back(temp);
        }

        for(int j = 0; j < n; j++)
        {
            string::reverse_iterator lastChar;
            lastChar = wordList[j].rbegin();

            for(int k = 0; k < n; k++)
            {
                string::iterator firstChar;
                firstChar = wordList[k].begin();

                if(j == k)
                    continue;

                if(*lastChar == *firstChar)
                    wordGraph[j][k] = 1;
            }
        }

        for(int j = 0; j < n; j++)
        {
            answer.clear();
            memset(visited, 0, sizeof(int)*n);
            visited[j] = 1;
            checkWords(visited,wordGraph,wordList,answer,j);
            //cout << (int)answer.size() << endl;
            if((int)answer.size() == n)
                break;
        }
        if((int)answer.size() != n)
            cout << "IMPOSSIBLE" << endl;
        else
        {
            for(int j = n-1; j >= 0; j--)
                cout << answer[j] << " ";
            cout << endl;
        }

    }
    return 0;
}

void checkWords(int* visited, int** wordGraph, vector<string>& wordList, vector<string>& answer, int idx)
{
    for(int i = 0; i < (int)wordList.size(); i++)
    {
        if(wordGraph[idx][i] == 1 && visited[i] == 0)
        {
            wordGraph[idx][i] = 0;
            visited[i] = 1;
            checkWords(visited, wordGraph, wordList, answer, i);
            break;
        }
    }
    answer.push_back(wordList[idx]);
}
*/
