#include <bits/stdc++.h>

using namespace std;

/*
    We can notice that the minimum number of
    operations is equal to the sum of absolute values
    of the differences between adjacent elements of B.
    
    Time: O(n) for the linear scan.
    Space: O(1) we only need two variables not the whole array.
*/

int main(void)
{
    int n, i;

    cin >> n;

    long long diff = 0;
    int prec = 0, curr;

    for(i=0; i<n; i++)
    {
        cin >> curr;
        diff += abs(prec-curr);
        prec = curr;
    }
    
    cout << diff << "\n";

    return 0;
}