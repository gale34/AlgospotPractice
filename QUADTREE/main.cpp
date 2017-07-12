#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

string reverseQuad(string& quad);
int ptr = 0;

int main()
{
    int c;
    string quad;

    //freopen("input.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        cin >> quad;

        cout << reverseQuad(quad) << endl;
        ptr = 0;
    }

    return 0;
}

string reverseQuad(string& quad)
{
    int x = 0;

    string quadrant[4];
    string subString;

    if(quad.at(ptr) == 'x')
    {
        subString += "x";
        ptr++;

        for(int i = 0; i < 4; i++)
            quadrant[i] = reverseQuad(quad);

        for(int i = 0; i < 4; i++)
            subString += quadrant[(i+2)%4];

        return subString;
    }
    else
    {
        subString += quad.at(ptr++);

        return subString;
    }
}
