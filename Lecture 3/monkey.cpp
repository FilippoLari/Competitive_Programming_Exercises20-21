#include <bits/stdc++.h>
#include <vector>
 
using namespace std;
 
/*
    We can observe that the minimum k is in the interval
    [0, 10 ^ 7]. Also for increasing values of k in that interval
    the sequence of results is monotone, so we can use binary search
    to find the minimum k, obtaining an algorithm whose execution time is
    O(nlogn).
    
    P.S: the solution is not accepted by the site, i think the reasoning
         is correct, but i can't find what i'm missing in the implementation.
*/
 
bool check(const vector<int> &r, int n, int k)
{
    for(int i=1; i<=n; i++)
    {
        if(r[i]-r[i-1]>k) return false;
        if(r[i]-r[i-1]==k) k--;
    }
 
    return true;
}
 
// iterative binary search
int search(const vector<int> &ref, int n)
{
    int mid, res = 0, l=1, r=10000000;
 
    while(l<=r){
        
        mid = (l+r)/2;
 
        if(check(ref, n, mid))
        {
            r = mid-1;
            res = mid;
        }
        else
        {
            l = mid+1;   
        }
    }
    
    return res;
}
 
int main(void)
{
    int t, n, i, j;
 
    cin >> t;
 
    for(j=1; j<=t; j++)
    {
        cin >> n;
 
        vector<int> r;
        r.reserve(n+1);
 
        r[0] = 0;
 
        for(i=1; i<=n; i++)
            cin >> r[i];
 
        printf("Case %i: %i\n", j, search(r, n));
    }
 
    return 0;
}
