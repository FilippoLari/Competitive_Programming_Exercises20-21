#include <bits/stdc++.h>

using namespace std;

template <class T>
struct fenwick_tree {
  std::vector<T> x;
  fenwick_tree(size_t n) : x(n+1) { } 
  
  // initialize by a constant
  fenwick_tree(size_t n, T a) : x(n+1, a) { 
    x[0] = 0;
    for (int k = 1; k+(k&-k) <= n; ++k) x[k+(k&-k)] += x[k];
  }
  
  // b[k] += a
  void add(int k, T a) { 
    for (++k; k < x.size(); k += k&-k) x[k] += a;
  }
  
  // sum b[0,k]
  T sum(int k) {
    T s = 0;
    for (++k; k > 0; k &= k-1) s += x[k];
    return s;
  }
};

/*
    The algorithm computes an array B such that
    B[j] = number of k in [j+1, n-1] s.t A[j] < A[k].

    To build B it scans A from right to left and for each position
    it computes the number of elements seen bigger than A[i] using
    a Fenwick tree, that is updated by one at position A[i] for 
    the next positions. In this way B is computed in O(nlogn) time.

    After that, it scans A from left to right with two indeces i and j
    and for each i < j such that A[i] < A[j] the number of triplets involving
    i and j is given by B[j].

    Time: O(nlogn) + O(n^2) = O(n^2) for computing B and for the two nested for loops.
    Space: O(n) for B.
*/

int main(void)
{
    int n, i, j;
    long long ans = 0;

    cin >> n;

    fenwick_tree<int> ft = fenwick_tree<int>(n, 0);
    vector<int> a(n);
    vector<long long> b(n, 0);

    for(i=0; i<n; i++)
        cin >> a[i];

    for(i=n-1; i>=0; i--)
    {
        b[i] = ft.sum(n)-ft.sum(a[i]);
        ft.add(a[i], 1);
    }

    for(i=0; i<n-2; i++)
        for(j=i+1; j<n-1; j++)
            if(a[i]<a[j] && b[j]>0)
                ans += b[j];

    cout << ans << "\n";
}