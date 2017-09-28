#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;

vector<string> getWordChain(int** wordGraph, vector<string>& wordList);
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
