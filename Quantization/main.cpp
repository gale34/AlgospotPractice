#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>

#define INF 99999999

using namespace std;

int getMinError(const vector<int>& seq,const vector<int>& seqSum,const vector<int>& seqSumSquare, int start, int last);
int getQuantization(const vector<int>& seq,const vector<int>& seqSum,const vector<int>& seqSumSquare, int n, int s, int start, int** memory);

int main()
{

    int c;

    //freopen("input.txt" , "r", stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n,s;
        vector<int> seq, seqSum, seqSumSquare;
        int** memory;

        cin >> n >> s;

        memory = new int*[101];
        for(int j = 0; j < 101; j++)
        {
            memory[j] = new int[11];
            memset(memory[j], -1, sizeof(int)*11);
        }

        for(int j = 0; j < n; j++)
        {
            int temp = 0;

            cin >> temp;

            seq.push_back(temp);
        }
        sort(seq.begin(), seq.end());

        vector<int>::iterator itr;

        for(itr = seq.begin(); itr != seq.end(); itr++)
        {
            if(itr == seq.begin())
            {
                seqSum.push_back(*itr);
                seqSumSquare.push_back((*itr) * (*itr));
            }
            else
            {
                seqSum.push_back(*itr + seqSum.back());
                seqSumSquare.push_back((*itr) * (*itr) + seqSumSquare.back());
            }
        }

        /*for(itr = seqSumSquare.begin(); itr != seqSumSquare.end(); itr++)
            cout << *itr << " ";
        cout << endl;*/

        cout << getQuantization(seq,seqSum,seqSumSquare,n,s,0,memory) << endl;

        for(int j = 0; j < s; j++)
            delete [] memory[j];
        delete [] memory;

    }

    return 0;
}

int getMinError(const vector<int>& seq,const vector<int>& seqSum,const vector<int>& seqSumSquare, int start, int last) // (start,end)
{
    int avg = 0;
    int seqSubTotal = 0;
    int seqSquareTotal = 0;
    int answer = 0;

    if(start == 0)
    {
        seqSubTotal = seqSum[last];
        seqSquareTotal = seqSumSquare[last];
    }
    else
    {
        seqSubTotal = seqSum[last] - seqSum[start - 1];
        seqSquareTotal = seqSumSquare[last] - seqSumSquare[start - 1];
    }

    avg = floor((seqSubTotal / (double)(last - start + 1)) + 0.5);

    answer = seqSquareTotal - (2*avg*seqSubTotal) + (int)pow((double)avg,2)*(last - start + 1);

    //cout << "d : " << answer << endl;

    return answer;
}

int getQuantization(const vector<int>& seq,const vector<int>& seqSum,const vector<int>& seqSumSquare,int n, int s, int start, int** memory)
{
    if(start == n)
        return 0;
    if(s == 0)
        return INF;

    int& answer = memory[start][s];

    if(answer != -1)
        return answer;

    answer = INF;

    for(int i = 1; i + start <= n; i++)
        answer = min(answer, getMinError(seq,seqSum,seqSumSquare,start,start + i - 1)
                     + getQuantization(seq,seqSum,seqSumSquare,n,s-1,start+i,memory));

    //cout << "t : " << answer << endl;

    return answer;
}
