#include <bits/stdc++.h>
 
using namespace std;

/*
	For each position i of A the algorithm computes
	the number of queries that touches it. This can
	be done in linear time by computing an array B
	such that for each query <l,r> we do B[l]++ and B[r+1]--.
	Then we compute the prefix sums array of B and after this we have
	B[i] = number of queries that touches position i in A.
	
	We then sort both B and A in descending order and assign bigger
	elements of A to the most touched positions.

	Time: O(nlogn) because of sorting A and B that are both of size n.
	Space: O(n) because of the additional array B.
*/

int main(void)
{
    int n, q, i, l ,r;
 
    cin >> n >> q;
 
    vector<int> a(n+1);
    vector<long long> b(n+1, 0);
 
    for(i=1; i<=n; i++)
        cin >> a[i];
 
    for(i=0; i<q; i++)
    {
        cin >> l >> r;
        b[l] += 1;
        if(r+1<=n) b[r+1] -= 1;
    }
 
    for(i=1; i<=n; i++)
        b[i] += b[i-1];
 
    sort(a.begin()+1, a.end(), greater<>());
    sort(b.begin()+1, b.end(), greater<>());
 
    long long sum = 0;
 
    for(i=1; i<=n; i++)
        sum += a[i] * b[i];
 
    cout << sum << "\n";
 
    return 0;
}