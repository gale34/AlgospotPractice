#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

void preCal(map<vector<int>,int>& sample,int n);
int getAnswer(map<vector<int>,int>& sample, vector<int> seq);

int main()
{
    freopen("input.txt","r",stdin);

    int c;

    cin >> c;

    map<vector<int>, int> sample;

    for(int i = 1; i <= 8; i++)
        preCal(sample,i);

    for(int i = 0; i < c; i++)
    {
        int n;
        int answer;

        vector<int> seq;

        cin >> n;

        for(int j = 0; j < n; j++)
        {
            int temp;
            cin >> temp;

            seq.push_back(temp);
        }

        answer = getAnswer(sample, seq);

        cout << answer << endl;

    }
    return 0;
}

void preCal(map<vector<int>,int>& sample,int n)
{
    int reverseCnt = 0;
    vector<int> original;
    vector<int> temp;
    queue<vector<int> > saveSea;

    for(int i = 1; i <= n; i++)
        original.push_back(i);

    saveSea.push(original);
    sample[original] = 0;

    while(!saveSea.empty())
    {
        temp = saveSea.front();
        saveSea.pop();

        reverseCnt = sample[temp];

        for(int i = 0; i < n; i++)
        {
            for(int j = i + 2; j <= n; j++)
            {
                reverse(temp.begin()+i, temp.begin()+j);
                reverseCnt++;
                if(sample.find(temp) == sample.end())
                {
                    saveSea.push(temp);
                    sample[temp] = reverseCnt;
                }
                else
                    sample[temp] = min(sample[temp],reverseCnt);
                reverse(temp.begin()+i, temp.begin()+j);
                reverseCnt--;
            }
        }
    }
}

int getAnswer(map<vector<int>,int>& sample, vector<int> seq)
{
    int answer;
    vector<int> temp = seq;
    map<int, int> tempMap;

    sort(temp.begin(), temp.end());

    for(int i = 0; i < temp.size(); i++)
        tempMap[temp[i]] = i+1;

    for(int i = 0; i < seq.size(); i++)
        seq[i] = tempMap[seq[i]];

    answer = sample[seq];
    return answer;
}
