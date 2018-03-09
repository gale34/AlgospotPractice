#include <iostream>
#include <cstdio>

using namespace std;

double get_Min_avg();

int main()
{
    int c;
    //freopen("input.txt", "r", stdin);

    cin >> c;

    cout.precision(10);
    for(int i = 0; i < c; i++)
         cout << fixed << get_Min_avg() << endl;


    return 0;
}

double get_Min_avg()
{
    int n, l;
    int* concertHall;
    int temp = 0;
    double answer = 1000.0;

    cin >> n >> l;
    concertHall = new int[n];

    for(int i = 0; i < n; i++)
    {
        cin >> temp;
        if(i == 0)
            concertHall[i] = temp;
        else
            concertHall[i] = concertHall[i-1] + temp;
    }

    for(int i = 0; i <= n - l; i++)
    {
        double avg = 0.0;
        for(int j = i+l-1; j < n; j++)
        {
            if(i == 0)
            {
                avg = (double)concertHall[j]/(j+1);
                if(answer > avg)
                    answer = avg;
            }
            else
            {
                avg = (double)(concertHall[j] - concertHall[i-1]) / (j - i + 1);
                if(answer > avg)
                    answer = avg;
            }
        }
    }

    delete concertHall;

    return answer;
}
