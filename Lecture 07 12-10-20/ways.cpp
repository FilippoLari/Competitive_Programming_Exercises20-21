#include <bits/stdc++.h>

using namespace std;

/*
    The algorithm first computes an array C such that
    C[i] = number of ways we can split A[i,n] such that the
    sum of the parts is equal to S/3, where S in the sum
    of all the elements in A.

    In order to compute C the algortihm scans A backwards
    computing the sum of each suffix, if one of these sums is
    equal to S/3 it sets C[i] to 1. After this, it computes the
    suffix sum of C.

    Finally, it scans A and for each prefix A[0,i] for which the sum is S/3
    it increases a counter by c[i+2]. The answer to the problem is
    the final value of the counter.


    Time: O(n)
    Space: O(n) because of the additional array.
*/

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, i;
    long long sum, psum, ways;

    cin >> n;

    vector<long> a(n);
    vector<long> c(n,0);

    sum = 0;
    ways = 0;

    for(i=0; i<n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }

    if(sum%3==0)
    {
        psum = sum/3;
        sum = 0;

        for(i=n-1; i>=0; i--)
        {
            sum += a[i];
            if(sum==psum) c[i] = 1;
        }

        for(i=n-2; i>=0; i--)
            c[i] += c[i+1];

        sum = 0;

        for(i=0; i<n-2; i++)
        {
            sum += a[i];
            if(sum==psum) ways+=c[i+2];
        }
    }

    cout << ways << "\n";
    
    return 0;
}