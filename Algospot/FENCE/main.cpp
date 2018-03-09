#include <iostream>
#include <cstdio>

using namespace std;

long cutFences(int* fence, int left, int right);
long getMax(long currentMax, long compareVal);
int getMinInt(int a, int b);

int main()
{
    int c,n;

    //freopen("input.txt", "r", stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int *fence;
        long max_fence = 0;

        cin >> n;

        fence = new int[n];
        for(int j = 0; j < n; j++)
            cin >> fence[j];

        max_fence = cutFences(fence,0,n-1);

        cout << max_fence << endl;
        delete fence;
    }


    return 0;
}

long cutFences(int* fence, int left, int right)
{
    long max_fence = 0;
    int mid = (left + right) / 2;
    int minLeftHeight = 20000;
    int minRightHeight = 20000;
    int height = 20000;
    int preHeight = height;
    int subLeft = mid;
    int subRight = mid+1;


    if(left == right)
        return fence[left];

    max_fence = getMax(max_fence, cutFences(fence, left, mid));
    max_fence = getMax(max_fence, cutFences(fence, mid+1, right));

    while(1)
    {
        height = getMinInt(fence[subLeft],fence[subRight]);
        height = getMinInt(height, preHeight);

        max_fence = getMax(max_fence,(long)(height * (subRight - subLeft + 1)));

        //cout << "test : " << max_fence << endl;
        //cout << "subLeft : " << subLeft << endl;
        //cout << "subRight : " << subRight << endl;

        if(subLeft - 1 < left && subRight + 1 > right)
            break;
        else if(subLeft - 1 < left && subRight + 1 <= right)
            subRight++;
        else if(subLeft - 1 >= left && subRight + 1 > right)
            subLeft--;
        else
        {
            if(fence[subLeft - 1] >= fence[subRight + 1])
                subLeft--;
            else
                subRight++;
        }

        preHeight = height;
    }

    /*for(int i = mid-1; i >= left; i--)
    {
        minLeftHeight = getMinInt(minLeftHeight,fence[i]);

        for(int j = mid; j <= right; j++)
        {
            minRightHeight = getMinInt(minRightHeight,fence[j]);

            max_fence = getMax((long)(getMinInt(minRightHeight,minLeftHeight) * (j-i+1))
                   , max_fence);
        }

        minRightHeight = 20000;
    }*/

    return max_fence;
}

long getMax(long currentMax, long compareVal)
{
    if(currentMax < compareVal)
        return compareVal;
    else
        return currentMax;
}

int getMinInt(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}
