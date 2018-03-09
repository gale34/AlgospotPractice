#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

void pushHeap(vector<long long>& h, long long next, bool isMaxHeap);
long long popHeap(vector<long long>& heap, bool isMaxHeap);
long long getMedian(vector<long long>& maxHeap, vector<long long>& minHeap, long long next);
long long getNextNumber(long long* seq, int a, int b, int idx);

int main()
{
    //freopen("input.txt","r",stdin);

    int c;

    cin >> c;
    for(int i = 0; i < c; i++)
    {
        int n,a,b;
        long long* seq;
        long long medNumber = 0;
        int answer = 0;
        vector<long long> maxHeap, minHeap;

        cin >> n >> a >> b;

        seq = new long long[n+1];
        memset(seq,0,sizeof(long long)*(n+1));

        for(int j = 0; j < n; j++)
        {
            long long next = getNextNumber(seq, a, b, j);

            medNumber = getMedian(maxHeap, minHeap, next);

            answer += medNumber;
            answer %= 20090711;

            //cout << "n : " << n << "  med : " << medNumber << "  answer : " << answer << endl;
        }


        cout << answer << endl;

        delete seq;
    }

    return 0;
}

void pushHeap(vector<long long>& heap, long long next, bool isMaxHeap)
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
long long popHeap(vector<long long>& heap, bool isMaxHeap)
{
    long long popVal = heap[0];
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

            if(heap[leftChild] < heap[idx])
                next = leftChild;

            if(rightChild < (int)heap.size() && heap[rightChild] < heap[next])
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

long long getMedian(vector<long long>& maxHeap, vector<long long>& minHeap, long long next)
{
    if(maxHeap.empty() && minHeap.empty())
        pushHeap(maxHeap,next,true);
    else
    {
        if(maxHeap[0] <= next) // next number is bigger than the median number
        {
            if((int)maxHeap.size() > (int)minHeap.size())
                pushHeap(minHeap,next,false);
            else// equal..
            {
                int moveNumber = 0;
                pushHeap(minHeap,next,false);
                moveNumber = popHeap(minHeap,false);
                pushHeap(maxHeap,moveNumber,true);

            }

        }
        else // next number is lower than the median number
        {
            if((int)maxHeap.size() > (int)minHeap.size())
            {
                int moveNumber = 0;
                pushHeap(maxHeap,next,true);
                moveNumber = popHeap(maxHeap,true);
                pushHeap(minHeap,moveNumber,false);
            }
            else
                pushHeap(maxHeap,next,true);
        }

    }

    /*if(!maxHeap.empty() && !minHeap.empty() && minHeap[0] < maxHeap[0])
    {
        __int64 a = maxHeap[0];
        __int64 b = minHeap[0];
        popHeap(maxHeap,true);
        popHeap(minHeap,false);
        pushHeap(maxHeap,b,true);
        pushHeap(minHeap,a,false);
    }*/

    return maxHeap[0];
}

long long getNextNumber(long long* seq, int a, int b, int idx)
{
    if(idx == 0)
        return seq[idx] = 1983;
    else
        return seq[idx] = ((seq[idx-1] * a) + b) % 20090711;
}
