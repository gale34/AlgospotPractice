#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<windows.h>

#define DIGIT_MAX_NUMBER 4

using namespace std;

void num2Korean(int c);

wstring kor_number[] = {L"",L"일",L"이",L"삼",L"사",L"오",L"육",L"칠",L"팔",L"구"};
wstring kor_10number[] = {L"",L"십",L"백",L"천"};

int main()
{
    //std::wcout.imbue(std::locale(""));
    setlocale(LC_ALL,"");
    int c;

    wcout << L"1 ~ 99999 사이의 정수를 입력하세요 : ";
    cin >> c;

    while(c < 1 || c > 99999)
    {
        wcout << L"다시 입력하세요 : ";
        cin >> c;
    }

    num2Korean(c);

    return 0;
}

void num2Korean(int c)
{
    vector<int> splitNumber;
    wstring answer = L"";

    while(c > 0)
    {
        splitNumber.push_back(c % 10);
        c /= 10;
    }
    reverse(splitNumber.begin(),splitNumber.end());

    for(int i = 0; i < splitNumber.size(); i++)
    {
        if(splitNumber[i] != 0)
        {
            int target = splitNumber.size() - i;
            int digit = (target - 1) % DIGIT_MAX_NUMBER;

            answer += kor_number[splitNumber[i]];
            answer += kor_10number[digit];

            if((splitNumber.size()-i) % (DIGIT_MAX_NUMBER + 1) == 0)
                answer += L"만";
        }

    }
    cout << endl;
    wcout << answer << endl;
}
