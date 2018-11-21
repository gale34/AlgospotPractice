#include <iostream>
#include <cstdio>

using namespace std;

int minGraduation(unsigned int* preCourses, unsigned int* coursesInTerms,int n,int k,int m,int l);

int main()
{
    freopen("input.txt","r",stdin);

    int testCase;
    cin >> testCase;

    for(int t = 0; t < testCase; t++)
    {
        int n,k,m,l;

        cin >> n >> k >> m >> l;

        unsigned int* preCourses = new unsigned int[n];

        for(int i = 0; i < n; i++)
        {
            int r;
            cin >> r;

            preCourses[i] = 0;
            for(int j = 0; j < r; j++)
            {
                int p;
                cin >> p;

                preCourses[i] |= (1 << p);
            }
        }

        unsigned int* coursesInTerms = new unsigned int[m];

        for(int i = 0; i < m; i++)
        {
            int c;
            cin >> c;

            coursesInTerms[i] = 0;
            for(int j = 0; j < c; j++)
            {
                int course;
                cin >> course;

                coursesInTerms[i] |= (1 << course);
            }
        }

        int answer = minGraduation(preCourses,coursesInTerms,n,k,m,l);

        if(answer != -1)
            cout << answer << endl;
        else
            cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}

int minGraduation(unsigned int* preCourses, unsigned int* coursesInTerms,int n,int k,int m,int l)
{
    unsigned int result = 0;
    int termCount = 0;

    for(int i = 0; i < m; i++)
    {
        unsigned int courses = coursesInTerms[i];
        unsigned int nowTerm = 0;
        int classCount = 0;

        for(unsigned int target = courses; target; target &= (target - 1))
        {
            unsigned int targetClass = __builtin_ctz(target);

            if(!(result & (1 << targetClass)) && (((preCourses[targetClass] & ~result) == 0) || preCourses[targetClass] == 0) && classCount <= l)
            {
                nowTerm |= (1 << targetClass);
                classCount++;
            }
        }

        result |= nowTerm;

        if(classCount > 0)
            termCount++;

        int takingClass = __builtin_popcount(result);

        if(takingClass >= k)
            return termCount;
    }

    return -1;
}
