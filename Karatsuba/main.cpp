#include <iostream>
#include <vector>

using namespace std;

void addTo(vector<int>& a, const vector<int>& b, int k);
void subFrom(vector<int>& a, const vector<int>& b);
vector<int> karatsuba(const vector<int>& a, const vector<int>& b);

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

void addTo(vector<int>& a, const vector<int>& b, int k)
{
    for(int i = 0; i < n; i++)
    {

    }
}

void subFrom(vector<int>& a, const vector<int>& b)
{

}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b)
{
    int an = a.size(), bn = b.size();

    if(an < bn) return karatsuba(b,a);

    if(an == 0 || bn == 0) return vecton<int>();

    if(an <= 50) return multiply(a,b);

    int half = an / 2;


    vector<int> a0(a.begin(),a.begin()+ half);
    vector<int> a1(a.begin()+ half, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
}
