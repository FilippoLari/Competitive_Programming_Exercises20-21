#include <bits/stdc++.h>

using namespace std;

/*
    We can observe that k must be at least the maximum
    differences among consecutive elements, i.e k >= max{r[i] - r[i+1] | 0<=i<=n-1}.
    We can also have multiple occurrences of the maximum difference, so to compute the answer
    it is sufficient to simulate the process and update the maximum accordingly.

    The algorithm implements the above observations.

    Time: O(n) per test case.
    Space: O(1).
*/

int main(void)
{
    int n, t, i, j;
    long long curr, prec, max_diff, diff, tmp;

    cin >> t;

    for(j=1; j<=t; j++)
    {
        cin >> n;

        vector<long> a(n+1);
        a[0] = 0;

        prec     = 0;
        max_diff = 0;

        for(i=1; i<=n; i++)
        {
            cin >> curr;
            diff = curr-prec;
            if(diff>max_diff) max_diff=diff;
            a[i] = curr;
            prec = curr;
        }

        tmp = max_diff;

        for(i=1; i<=n; i++)
        {
            diff = a[i]-a[i-1];

            if(diff==tmp)
                tmp--;
            else if(diff>tmp)
            {
                max_diff++;
                break;
            }
        }

        cout << "Case " << j << ": " << max_diff << "\n";
    }

    return 0;
}