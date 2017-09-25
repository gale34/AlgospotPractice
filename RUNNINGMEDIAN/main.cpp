#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

void pushHeap(vector<__int64>& h, __int64 next, bool isMaxHeap);
__int64 popHeap(vector<__int64>& heap, bool isMaxHeap);
__int64 getMedian(vector<__int64>& maxHeap, vector<__int64>& minHeap, __int64 next);
__int64 getNextNumber(__int64* seq, int a, int b, int idx);

int main()
{
    freopen("input.txt","r",stdin);

    int c;

    cin >> c;
    for(int i = 0; i < c; i++)
    {
        int n,a,b;
        __int64* seq;
        __int64 medNumber = 0;
        int answer = 0;
        vector<__int64> maxHeap, minHeap;

        cin >> n >> a >> b;

        seq = new __int64[n+1];
        memset(seq,0,sizeof(__int64)*(n+1));

        for(int j = 0; j < n; j++)
        {
            __int64 next = getNextNumber(seq, a, b, j);

            medNumber = getMedian(maxHeap, minHeap, next);

            cout << "test" << endl;
            for(int k = 0; k < (int)maxHeap.size(); k++)
            {
                cout << "maxHeap" << k << ": " <<maxHeap[k]<<endl;
            }
            for(int k = 0; k < (int)minHeap.size(); k++)
            {
                cout << "minHeap" << k << ": " <<minHeap[k]<<endl;
            }
            answer += medNumber;
            answer %= 20090711;

            //cout << "n : " << n << "  med : " << medNumber << "  answer : " << answer << endl;
        }


        cout << answer << endl;

        delete seq;
    }

    return 0;
}

void pushHeap(vector<__int64>& heap, __int64 next, bool isMaxHeap)
{
    heap.push_back(next);

    int idx = heap.size() - 1;

    if(isMaxHeap == true)
    {
        while(idx > 0)
        {
            if(heap[(idx - 1)/2] < heap[idx])
            {
                int temp = heap[(idx - 1)/2];
                heap[(idx - 1)/2] = heap[idx];
                heap[idx] = temp;
                idx = (idx - 1)/2;
            }
            else
                break;
        }
    }
    else
    {
        while(idx > 0)
        {
            if(heap[(idx - 1)/2] > heap[idx])
            {
                int temp = heap[(idx - 1)/2];
                heap[(idx - 1)/2] = heap[idx];
                heap[idx] = temp;
                idx = (idx - 1)/2;
            }
            else
                break;
        }
    }
}
__int64 popHeap(vector<__int64>& heap, bool isMaxHeap)
{
    __int64 popVal = heap[0];
    int idx = 0;
    heap[0] = heap.back();

    heap.pop_back();

    int next = 0;
    if(isMaxHeap == true)
    {
        while(idx < (int)heap.size())
        {
            int leftChild = (idx * 2) + 1;
            int rightChild = (idx * 2) + 2;

            int temp = 0;

            if(leftChild >= (int)heap.size())
                break;

            if(heap[leftChild] > heap[idx])
                next = leftChild;

            if(rightChild < (int)heap.size() && heap[rightChild] > heap[next])
                next = rightChild;

            if(next == idx)
                break;

            temp = heap[idx];
            heap[idx] = heap[next];
            heap[next] = temp;

            //cout << "next : " << next << " idx : " << idx <<endl;
            idx = next;
        }
    }
    else
    {
        while(idx < (int)heap.size())
        {
            int leftChild = (idx * 2) + 1;
            int rightChild = (idx * 2) + 2;
            int temp = 0;

            if(leftChild >= (int)heap.size())
                break;

            if(heap[leftChild] > heap[idx])
                next = leftChild;

            if(rightChild < (int)heap.size() && heap[rightChild] > heap[next])
                next = rightChild;

            if(next == idx)
                break;

            temp = heap[idx];
            heap[idx] = heap[next];
            heap[next] = temp;

            idx = next;
        }
    }

    return popVal;
}

__int64 getMedian(vector<__int64>& maxHeap, vector<__int64>& minHeap, __int64 next)
{
    if(maxHeap.empty() && minHeap.empty())
        pushHeap(maxHeap,next,true);
    else
    {
        if(maxHeap[0] <= next) // next number is bigger than the median number
        {
            if((int)maxHeap.size() > (int)minHeap.size())
                pushHeap(minHeap,next,false);
            else
            {
                int moveNumber = popHeap(minHeap,false);
                pushHeap(maxHeap,moveNumber,true);
                pushHeap(minHeap,next,false);
            }

        }
        else // next number is lower than the median number
        {
            if((int)maxHeap.size() > (int)minHeap.size())
            {
                int moveNumber = popHeap(maxHeap,true);
                pushHeap(minHeap,moveNumber,false);
                pushHeap(maxHeap,next,true);
            }
            else
                pushHeap(maxHeap,next,true);
        }
    }

    return maxHeap[0];
}

__int64 getNextNumber(__int64* seq, int a, int b, int idx)
{
    if(idx == 0)
        return seq[idx] = 1983;
    else
        return seq[idx] = ((seq[idx-1] * a) + b) % 20090711;
}
