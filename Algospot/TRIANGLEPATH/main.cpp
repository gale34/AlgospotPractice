#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int getMaxPath(const vector<vector<int> > triangle, int x, int y);

vector<vector<int> > path;

int main()
{
    int c, n;
    //freopen("input.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        vector<vector<int> > triangle;

        cin >> n;

        for(int j = 0; j < n; j++)
        {
            vector<int> row;
            row.resize(j+1);
            triangle.push_back(row);
            for(int k = 0; k < j+1; k++)
                cin >> triangle[j][k];
        }
        path = triangle;

        cout << getMaxPath(triangle, 0 ,0) << endl;

        for(int j = 0; j < (int)path.size(); j++)
            path[j].clear();
        path.clear();

        for(int j = 0; j < (int)triangle.size(); j++)
            triangle[j].clear();
        triangle.clear();
    }
    return 0;
}

int getMaxPath(const vector<vector<int> > triangle,int x, int y)
{
    int answerA = 0;
    int answerB = 0;
    int answer = 0;

    if(x == (int)triangle.size())
        return 0;

    if(path[x][y] > triangle[x][y])
        return path[x][y];

    answer = triangle[x][y];

    answerA = getMaxPath(triangle,x+1,y);
    answerB = getMaxPath(triangle,x+1,y+1);

    if(answerA > answerB)
        answer += answerA;
    else
        answer += answerB;

    path[x][y] = answer;

    return answer;
}
