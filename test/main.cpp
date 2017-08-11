#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int MOD = 20170805;
int dx[4];
int dy[4];

#define FROM_SOUTH 0
#define FROM_WEST 1
#define FROM_NORTH 2
#define FROM_EAST 3
#define START 4

//int checkColor(int x , int y,const vector<vector<int> >& picture, int** memory, int m, int n);
//vector<int> solution(int m, int n, vector<vector<int> > picture);
//int solution(int m, int n, vector<vector<int> > city_map);
//int checkWays(int dir, int x, int y,const vector<vector<int> >& city_map, int** memory_from_north,int** memory_from_west , int m, int n);

//int solution(int n);
//int get3rdWays(int n, int accum_number, int plusA);
int solution(int n, vector<vector<int> > data);

bool compareXY(const vector<int>& v1, const vector<int>& v2)
{
    if(v1.front() == v2.front())
        return v1.back() < v2.back();
    return v1.front() < v2.front();
}

int main()
{
    freopen("input.txt","r",stdin);

    int n;
    cin >> n;

    vector<vector<int> > data;
    int answer = 0;

    for(int i = 0; i < n; i++)
    {
        vector<int> row;
        row.resize(2);
        data.push_back(row);

        for(int j = 0; j < 2; j++)
            cin >> data[i][j];
    }

    sort(data.begin(),data.end(),compareXY);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 2; j++)
            cout << data[i][j] << " ";
        cout << endl;
    }

    answer = solution(n,data);
    cout << answer << endl;
    return 0;
}

int solution(int n, vector<vector<int> > data) {
    int answer = 0;
    bool isEmpty = true;
    int cntRect = 0;

    //sort(data.begin(),data.end(),compareXY);

    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(data[i][0] != data[j][0] && data[i][1] != data[j][1])
            {

                for(int k = i+1; k < j; k++)
                {
                    if((data[k][1] > data[i][1] && data[k][1] < data[j][1])
                       || (data[k][1] < data[i][1] && data[k][1] > data[j][1]))
                    {
                        isEmpty = false;
                        break;
                    }
                    else if((data[k][0] == data[j][0] && data[k][1] == data[i][1])
                       || (data[k][0] == data[i][0] && data[k][1] == data[j][1]))
                       cntRect++;
                }
                if(isEmpty)
                {
                    if(cntRect != 2)
                    {
                        cout << "(" << data[i][0] << "," << data[i][1] << ") " << "(" << data[j][0] << "," << data[j][1] << ") " << endl;
                        answer++;
                    }

                    //if(data[i][0] + (data[j][0] - data[i][0]),data[i][1] && data[i][0] , data[i][1] + (data[j][1] - data[i][1])


                }
                isEmpty = true;
                cntRect = 0;

            }
        }
    }

    return answer;
}


/*int solution(int n) {
    int answer = 0;

    answer = get3rdWays(n,1,2);

    return answer;
}

int get3rdWays(int n, int accum_number, int plusA)
{
    int answer = 0;
    accum_number *= 3;
    //cout << accum_number+plusA << endl;
    if(accum_number+plusA > n)
        return 0;
    else if(accum_number+plusA == n)
        return answer+1;
    else if(accum_number+plusA <= 0)
        return 0;
    else
    {
        for(int i = 0; i < plusA + 2; i++)
            answer += get3rdWays(n, accum_number+i,plusA + 2 - i);
        answer += get3rdWays(n, accum_number,plusA + 2); // *(*..)++
        answer += get3rdWays(n, accum_number+1,plusA + 1); // *+(*..)+
        answer += get3rdWays(n, accum_number+2,plusA); // *++(*..)
    }
    return answer;
}*/

/*int solution(int m, int n, vector<vector<int> > city_map) {
    int answer = 0;
    int destX = m-1;
    int destY = n-1;

    dx[0] = 0;
    dx[1] = 1;
    dx[2] = 0;
    dx[3] = -1;

    dy[0] = -1;
    dy[1] = 0;
    dy[2] = 1;
    dy[3] = 0;

    int** memory_from_north;
    int** memory_from_west;
    memory_from_north = new int*[m];
    memory_from_west = new int*[m];
    for(int i = 0; i < m; i++)
    {
        memory_from_north[i] = new int[n];
        memset(memory_from_north[i],-1,sizeof(int)*n);
        memory_from_west[i] = new int[n];
        memset(memory_from_west[i],-1,sizeof(int)*n);
    }

    answer = checkWays(START, 0, 0, city_map, memory_from_north,memory_from_west, m,n);

    return answer;
}

int checkWays(int dir, int x, int y,const vector<vector<int> >& city_map, int** memory_from_north,int** memory_from_west , int m, int n)
{
    if(x < 0 || x >= m || y < 0 || y >= n)
        return 0;

    if(x == m - 1 && y == n - 1)
    {
        memory_from_north[x][y] = 1;
        memory_from_west[x][y] = 1;
        return 1;
    }

    if(city_map[x][y] == 1)
    {
        memory_from_north[x][y] = 0;
        memory_from_west[x][y] = 0;
        return 0;
    }
    else if(city_map[x][y] == 2)
    {
        if(dir == FROM_WEST)
        {
            int& answer = memory_from_west[x][y];
            if(answer != -1)
                return answer % MOD;
            return answer = checkWays(FROM_WEST, x+dx[FROM_WEST], y+dy[FROM_WEST], city_map, memory_from_north,memory_from_west, m, n) % MOD;
        }
        else if(dir == FROM_NORTH)
        {
            int& answer = memory_from_north[x][y];
            if(answer != -1)
                return answer % MOD;
            return answer = checkWays(FROM_NORTH, x+dx[FROM_NORTH], y+dy[FROM_NORTH], city_map, memory_from_north,memory_from_west, m, n) % MOD;
        }
    }
    else
    {
        int& answer = memory_from_west[x][y];
        if(answer != -1)
            return answer % MOD;

        answer = 0;

        answer += checkWays(FROM_WEST, x+dx[FROM_WEST], y+dy[FROM_WEST], city_map, memory_from_north,memory_from_west, m, n);
        answer %= MOD;
        answer += checkWays(FROM_NORTH, x+dx[FROM_NORTH], y+dy[FROM_NORTH], city_map, memory_from_north,memory_from_west, m, n);

        memory_from_north[x][y] = answer;

        return (answer % MOD);
    }
}*/

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
/*vector<int> solution(int m, int n, vector<vector<int> > picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    int part_of_answer = 0;

    dx[0] = 0;
    dx[1] = 1;
    dx[2] = 0;
    dx[3] = -1;

    dy[0] = -1;
    dy[1] = 0;
    dy[2] = 1;
    dy[3] = 0;

    int** memory;
    memory = new int*[m];
    for(int i = 0; i < m; i++)
    {
        memory[i] = new int[n];
        memset(memory[i],-1,sizeof(int)*n);
    }

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {

            part_of_answer = checkColor(i,j,picture,memory,m,n);
//cout << "i : " << i << " j : " << j << endl;
            if(part_of_answer != 0)
            {
                number_of_area++;
                max_size_of_one_area = max(part_of_answer, max_size_of_one_area);
            }

        }
    }



    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}

int checkColor(int x, int y,const vector<vector<int> >& picture, int** memory, int m, int n)
{
    //cout << "i : " << x << " j : " << y << endl;
    if(memory[x][y] != -1)
        return 0;

    int answer = 0;

    memory[x][y] = picture[x][y];
    if(memory[x][y] == 0)
        return 0;
//cout << "i : " << x << " j : " << y << endl;
    for(int i = 0; i < 4; i++)
    {
        if(x + dx[i] >= 0 && x + dx[i] < m && y + dy[i] >= 0 && y + dy[i] < n)
        {
            cout << "i : " << x << " j : " << y << endl;
            if(picture[x+dx[i]][y+dy[i]] == picture[x][y])
           {
            answer += checkColor(x+dx[i], y+dy[i],picture,memory,m,n);
             //cout << "x : " << x << " y : " << y << " answer : " << answer << endl;

           }
        }


    }

    return answer + 1;
}*/
