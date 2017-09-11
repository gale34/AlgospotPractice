#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

typedef struct fortress
{
    int x;
    int y;
    int r;
    int h;
    vector<struct fortress> underFortress;
    struct fortress* parent;
} Fortress;

void makeTreeFortress(Fortress& obj, Fortress& another);
int calTreeHeight(Fortress& obj);
void getMaxPath(Fortress& obj);

int answer;

int main()
{
    //freopen("input.txt","r",stdin);

    int c;

    cin >> c;

    for(int i = 0 ; i < c; i++)
    {
        int n;
        Fortress root;
        answer = 0;

        cin >> n;

        root.h = 1;
        root.parent = NULL;
        for(int j = 0; j < n; j++)
        {
            if(j == 0)
                cin >> root.x >> root.y >> root.r;
            else
            {
                Fortress another;
                cin >> another.x >> another.y >> another.r;
                makeTreeFortress(root, another);
            }
        }

        calTreeHeight(root);
        getMaxPath(root);

        cout << answer << endl;

    }
    return 0;
}

void makeTreeFortress(Fortress& obj, Fortress& another)
{
    another.h = 1;
    double distCenter = sqrt((double)pow((obj.x - another.x),2) + (double)pow((obj.y - another.y),2));

    if(distCenter >= obj.r + another.r) // outside of obj
        obj.parent->underFortress.push_back(another);
    else // inside of obj
    {
        if(obj.underFortress.empty())
            obj.underFortress.push_back(another);
        else
        {
            int idx = 0;
            for(idx = 0; idx < (int)obj.underFortress.size(); idx++)
            {
                double subDistCenter = sqrt((double)pow((obj.underFortress[idx].x - another.x),2) + (double)pow((obj.underFortress[idx].y - another.y),2));

                if(subDistCenter < obj.underFortress[idx].r + another.r)
                    break;
            }
            if(idx == (int)obj.underFortress.size())
                obj.underFortress.push_back(another);
            else
                makeTreeFortress(obj.underFortress[idx],another);

        }
    }
}

int calTreeHeight(Fortress& obj)
{
    for(int i = 0; i < (int)obj.underFortress.size(); i++)
        obj.h = max(obj.h,calTreeHeight(obj.underFortress[i]));
    return obj.h + 1;
}

void getMaxPath(Fortress& obj)
{
    int max2Height = 0;
    int max1Height = 0;
    int isFoundMaxHeight = false;

    for(int i = 0; i < (int)obj.underFortress.size(); i++)
        getMaxPath(obj.underFortress[i]);

    for(int i = 0; i < (int)obj.underFortress.size(); i++)
    {
        if(isFoundMaxHeight == false && obj.underFortress[i].h == obj.h-1)
        {
            isFoundMaxHeight = true;
            max1Height = obj.underFortress[i].h;
        }
        else
            max2Height = max(max2Height,obj.underFortress[i].h);
    }

    answer = max(answer,max1Height+max2Height);
}
