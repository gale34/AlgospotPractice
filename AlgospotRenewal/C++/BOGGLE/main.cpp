#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <map>

using namespace std;

int pX[8] = {-1,0,1,-1,1,-1,0,-1};
int pY[8] = {-1,-1,-1,0,0,1,1,1};
char pannel[5][5];
map<pair<int, int>, vector<string> > cache;

void getBogglePannel();
bool hasWord(string word);
bool hasWordAtPt(int x, int y, string word);

void saveCache(int x, int y, string word);
bool isCached(int x, int y, string word);

int main()
{
    freopen("input.txt","r",stdin);
    int numOfTest = 0;

    cin >> numOfTest;

    for(int i = 0; i < numOfTest; i++)
    {

        getBogglePannel();

        int numOfWord = 0;
        cin >> numOfWord;

        for(int j = 0; j < numOfWord; j++)
        {
            string word;
            cin >> word;

            bool answer = hasWord(word);

            if(answer)
                cout << word << " YES" <<endl;
            else
                cout << word << " NO" <<endl;
        }

    }

    return 0;
}

void getBogglePannel()
{
    for(int j = 0; j < 5; j++)
    {
        for(int k = 0; k < 5; k++)
        {
            cin >> pannel[j][k];
        }
    }
}

bool hasWord(string word)
{
    bool answer = false;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            string copy = word;
            if(pannel[i][j] == *(word.begin()))
                answer = hasWordAtPt(i,j,copy.erase(0,1));

            if(answer == true)
            {
                saveCache(i,j,word);
                return answer;
            }

        }
    }

    cache.clear();
    return answer;
}

bool hasWordAtPt(int x, int y, string word)
{
    if(word.empty())
        return true;

    if(isCached(x,y,word))
        return true;

    bool answer = false;
    for(int i = 0; i < 8; i++)
    {
        string copy = word;
        int targetX = x + pX[i];
        int targetY = y + pY[i];
        if(targetX >= 0 && targetX < 5 && targetY >= 0 && targetY < 5 && pannel[targetX][targetY] == *(word.begin()))
            answer = hasWordAtPt(x + pX[i], y + pY[i], copy.erase(0,1));

        if(answer == true)
        {
            saveCache(x,y,word);
            return answer;
        }
    }

    return answer;
}

void saveCache(int x, int y, string word)
{
    if(cache.find(make_pair(x,y)) != cache.end()) {
        if(!isCached(x,y,word))
            cache[make_pair(x,y)].push_back(word);
    }
    else {
        vector<string> value;
        value.push_back(word);
        cache[make_pair(x,y)] = value;
    }
}
bool isCached(int x, int y, string word)
{
    vector<string> target = cache[make_pair(x,y)];

    for(int i = 0; i < target.size(); i++)
    {
        if(target[i] == word)
            return true;
    }
}
