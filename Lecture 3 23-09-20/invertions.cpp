#include <bits/stdc++.h>

using namespace std;

template <class T>
struct fenwick_tree {
  std::vector<T> x;
  fenwick_tree(size_t n) : x(n+1) { } 
  
  fenwick_tree(size_t n, T a) : x(n+1, a) { 
    x[0] = 0;
    for (int k = 1; k+(k&-k) <= n; ++k) x[k+(k&-k)] += x[k];
  }
   
  fenwick_tree(std::vector<T> y) : x(y.size()+1) {
    for (int k = 0; k < y.size(); ++k) x[k+1] = y[k];
    for (int k = 1; k+(k&-k) < x.size(); ++k) x[k+(k&-k)] += x[k];
  }
  
  void add(int k, T a) { 
    for (++k; k < x.size(); k += k&-k) x[k] += a;
  }
  
  T sum(int k) {
    T s = 0;
    for (++k; k > 0; k &= k-1) s += x[k];
    return s;
  }
};

template<typename T> 
void remap(vector<T>& a) {
  vector<T> tmp(a.size());
  copy(a.begin(), a.end(), tmp.begin());
  sort(tmp.begin(), tmp.end());
  size_t sz = distance(tmp.begin(), unique(tmp.begin(), tmp.end()));
  tmp.resize(sz);
  
  for(auto &x : a)
    x = distance(tmp.begin(), lower_bound(tmp.begin(), tmp.end(), x));
}

/*
    The algorithm first remaps the values to be smaller or equal than
    n by replacing them with their rank in the sorted array.

    We can observe that if we scan the array from right to left keeping
    an additional array B where we add a one in position A[i], the number
    of inversions given by position i in A is given by a prefix sum
    up to position A[i]-1 in B.

    The algorithm implements this observation using a Fenwick tree.

    Time: O(nlogn) for test case, because of the calls to Add and Sum for each element of A
          which both costs O(logn). Also because of sorting.
    
    Space: O(n) because of the Fenwick tree.

    Note: i'm aware of the solution that uses a modification of the merge sort algorithm, but
          i preferred to implement this one.
*/

int main()
{
    int n, t, i;
    long ans;

    cin >> t;

    while(t--)
    {
        cin >> n;

        vector<int> a(n+1);

        for(i=1; i<=n; i++)
            cin >> a[i];

        remap<int>(a);

        fenwick_tree<int> ft(n+1, 0);

        ans = 0;

        for(i=n; i>=1; i--)
        {
            ft.add(a[i],1);
            ans += ft.sum(a[i]-1);
        }

        cout << ans << "\n";
    }

    return 0;
}