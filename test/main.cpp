#include<string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
bool solution(string a, string b);
int main()
{
    map<pair<int,int>, bool> visitor;

    for(int i = 1; i <= 100; i++)
    {
        for(int j = 1; j <= 100; j++)
        {
            //cout << "test" <<endl;
            visitor[make_pair(i,i)] = true;
        }
    }

    cout <<"[";
    for(map<pair<int,int>, bool>::iterator it = visitor.begin(); it != visitor.end(); it++)
        cout << "[" << it->first.first << "," << it->first.second << "],";
    cout << "]" << endl;
    /*bool answer ;

    answer = solution("listen","silent");

    if(answer == true)
        cout << "true" <<endl;
    else
        cout << "false" << endl;
    cout << answer <<endl;

    vector<vector<int> > temp;
    temp.resize()*/

    return 0;
}
bool solution(string a, string b)
{
    bool answer = true;

    transform(a.begin(), a.end(), a.begin(), ::tolower);
    transform(b.begin(), b.end(), b.begin(), ::tolower);

    if(a.size() != b.size())
        answer = false;
    else
    {
        for(int i = 0; i < a.size(); i++)
        {
            if(a[i] != b[b.size() - 1 - i])
            {
                answer = false;
                break;
            }
        }
    }
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;

    return answer;
}
