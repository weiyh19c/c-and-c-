// Convert this program to C++
// change to C++ io
// change to one line comments
// change defines of constants to const
// change array to vector<>
// inline any short function


#include <iostream>
#include <vector>
using namespace std;
const int N = 40;

inline void sum(int *p, int n, vector<int> vec)

{
    *p = 0;
    for (int i = 0; i < n; ++i)
        *p = *p + vec[i];
}

int main()
{
    int accum = 0;
    vector<int> v;
    for (int i = 0; i < N; ++i)
        v.push_back(i);

    sum(&accum, N, v);
    cout <<  "sum is " << accum << endl;
    return 0;
}