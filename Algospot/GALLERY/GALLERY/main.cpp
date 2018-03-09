#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

#define UNWATCHED 0
#define WATCHED 1
#define INSTALLED 2

int answer;

int checkCCTY(int* visited,int* installed, vector<vector<int> >& galleryGraph, int idx);
/*int dfs(int here,int* visited,vector<vector<int> >& galleryGraph)
{
    visited[here] = 1;
    int children[3] = {0,0,0};
    for(int i = 0; i < galleryGraph[here].size(); i++)
    {
        int there = galleryGraph[here][i];
        if(!visited[there])
            ++children[dfs(there,visited,galleryGraph)];
    }

    if(children[UNWATCHED])
    {
        ++answer;
        return INSTALLED;
    }

    if(children[INSTALLED])
        return WATCHED;
    return UNWATCHED;
}
*/

int main()
{
    int c;
    freopen("input.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int g,h;
        int* visited;
        int* installed;
        answer = 0;

        vector<vector<int> > galleryGraph;

        cin >> g >> h;

        visited = new int[g];
        installed = new int[g];
        memset(visited,0,sizeof(int)*g);
        memset(installed,UNWATCHED,sizeof(int)*g);

        galleryGraph = vector<vector<int> >(g);

        for(int j = 0; j < h; j++)
        {
            int a,b;

            cin >> a >> b;

            galleryGraph[a].push_back(b);
            galleryGraph[b].push_back(a);
        }

        /*for(int j = 0; j < g; j++)
        {
            for(int k = 0; k < galleryGraph[j].size(); k++)
                cout << galleryGraph[j][k] << " ";
            cout << endl;
        }*/
        for(int j = 0; j < g; j++)
        {
            if(visited[j] == 0 && checkCCTY(visited,installed,galleryGraph,j) == UNWATCHED)
                answer++;
        }

        cout << answer << endl;

        delete visited;
        delete installed;
    }
    return 0;
}

int checkCCTY(int* visited,int* installed, vector<vector<int> >& galleryGraph, int idx)
{
    //cout << "test : " << idx << endl;
    //int answer = 0;
    visited[idx] = 1;
    vector<int> countChild;
    bool HasToBeInstalled = false;

    for(int i = 0; i < galleryGraph[idx].size(); i++)
    {
        int next = galleryGraph[idx][i];
        if(visited[next] == 0)
        {
            //cout << "Test : " << i <<endl;
            countChild.push_back(next);
            checkCCTY(visited, installed, galleryGraph, next);
        }
    }

    for(int i = 0; i < countChild.size(); i++)
    {
        int next = countChild[i];
        //cout << "idx : " << idx << " count : "<< countChild[i] << endl;
        if(installed[next] == UNWATCHED)
        {
            //cout << "install : " << idx << endl;
            answer++;
            return installed[idx] = INSTALLED;
        }
    }
    for(int i = 0; i < countChild.size(); i++)
    {
        int next = countChild[i];
        //cout << "idx : " << idx << " count : "<< countChild[i] << endl;
        if(installed[next] == INSTALLED)
            return installed[idx] = WATCHED;
    }
    return installed[idx] = UNWATCHED;
        //cout << "install : " << idx << endl;
}
