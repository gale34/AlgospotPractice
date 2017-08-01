#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int getMaxPath(const vector<vector<int> > triangle, int x, int y);
unsigned int countMaxPath(int x, int y);

vector<vector<int> > path;
vector<vector<unsigned int> > countPath;

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
            vector<unsigned int> row2;
            row.resize(j+1);
            row2.resize(j+1);
            triangle.push_back(row);
            countPath.push_back(row2);
            for(int k = 0; k < j+1; k++)
            {
                cin >> triangle[j][k];
                countPath[j][k] = 0;
            }
        }
        path = triangle;
        getMaxPath(triangle, 0 ,0);

        cout << countMaxPath(0,0) << endl;

        /*for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < j+1; k++)
            {
                cout << path[j][k] << " ";
            }
            cout << endl;
        }*/

        for(int j = 0; j < (int)path.size(); j++)
            path[j].clear();
        path.clear();

        for(int j = 0; j < (int)triangle.size(); j++)
            triangle[j].clear();
        triangle.clear();

        for(int j = 0; j < (int)countPath.size(); j++)
            countPath[j].clear();
        countPath.clear();
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

unsigned int countMaxPath(int x, int y)
{
    unsigned int& answer = countPath[x][y];

    if(answer != 0)
        return answer;

    if(x == (int)countPath.size() - 1)
        return answer = 1;

    if(path[x+1][y] > path[x+1][y+1])
        answer = max(answer, countMaxPath(x+1,y));
    else if(path[x+1][y] < path[x+1][y+1])
        answer = max(answer, countMaxPath(x+1,y+1));
    else
        answer = max(answer, countMaxPath(x+1,y) + countMaxPath(x+1,y+1));

    return answer;
}
