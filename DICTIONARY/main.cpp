#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>

using namespace std;

#define ERROR_MESSAGE "INVALID HYPOTHESIS"

string getDictionary(vector<string>& wordList);
void dfs(int idx);

int** alphabet;
vector<int> visited;// 0 : visited, 1: visited X and no edge, 2: visited X and edge
vector<int> answer;

int main()
{
    freopen("input.txt", "r", stdin);

    int c;

    cin >> c;

    alphabet = new int*[26];
    for(int i = 0; i < 26; i++)
    {
        alphabet[i] = new int[26];
        memset(alphabet[i],0,sizeof(int)*26);
    }

    for(int i = 0; i < c; i++)
    {
        int n;
        vector<string> wordList;
        string answers;

        cin >> n;

        for(int j = 0; j < n; j++)
        {
            string temp;

            cin >> temp;

            wordList.push_back(temp);

        }

        answers = getDictionary(wordList);

        cout << answers << endl;

        /*for(int j = 0; j < 26; j++)
        {
            for(int k = 0; k < 26; k++)
                cout << alphabet[j][k] << " ";
            cout<< endl;

        }*/

        answer.clear();
        visited.clear();
        for(int j = 0; j < 26; j++)
            memset(alphabet[j],0,sizeof(int)*26);
    }

    delete alphabet;
    return 0;
}

string getDictionary(vector<string>& wordList)
{
    string dictionary = "";

    visited = vector<int>(27,1);

    for(int i = 0; i < (int)wordList.size() - 1; i++)
    {
        for(int j = 0; j < (int)wordList[i].size(); j++)
        {
            if(wordList[i+1].size() <= j)
                break;

            if(wordList[i].at(j) != wordList[i+1].at(j))
            {
                alphabet[wordList[i].at(j) - 97][wordList[i+1].at(j) - 97] = 1;
                visited[wordList[i].at(j) - 97] = 2;
                break;
            }
        }
    }

    for(int i = 0; i < 26; i++)
    {
        for(int j = i + 1; j < 26; j++)
        {
            if(alphabet[i][j] == alphabet[j][i] && alphabet[i][j] == 1)
                return ERROR_MESSAGE;
        }
    }

    for(int i = 0; i < 26; i++)
        if(visited[i] == 2)
            dfs(i);

    for(int i = 25; i >= 0; i--)
        if(visited[i] != 0)
            dfs(i);

    for(int i = (int)answer.size() - 1; i >= 0; i--)
    {
        dictionary += (char)(answer[i]+97);
    }

    return dictionary;
}

void dfs(int idx)
{
    visited[idx] = 0;

    for(int i = 0; i < 26; i++)
    {
        if(alphabet[idx][i] == 1 && visited[i] != 0)
            dfs(i);
    }
    answer.push_back(idx);
}
