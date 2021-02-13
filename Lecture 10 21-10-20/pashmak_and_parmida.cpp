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
    First of all the algorithm remaps the values to be smaller or
    equal to n by replacing them with their rank in the sorted
    array.

    After this it build two arrays L and R such that:
    R[i] = f(1,i,a[i]) and L[j] = f(j,n,a[j]).

    We can observe that by scanning R and L backwards, starting
    by i = n, if we build another array B where for each position
    we add a 1 in position L[i-1, the number of positions j such that i<j and
    f(1,i,a[i])>f(j,n,a[j]) is given by a prefix sum on B up to
    position R[i]-1.

    The algorithm implements this observation with a Fenwick tree.

    Time: O(nlogn) because of the sorting and because for each
          position of R we make a call to Add and Sum, which both costs O(logn).

    Space: O(n) because of the additional arrays.
*/

int main(void)
{
    int n, i;
    
    cin >> n;

    vector<long long> l(n+1,0), r(n+1,0), freq(n+1,0), a(n+1);
    fenwick_tree<long long> ft(n, 0);

    for(i=1; i<=n; i++)
        cin >> a[i];

    remap<long long>(a);

    for(i=1; i<=n; i++)
    {
        freq[a[i]]++;
        r[i] = freq[a[i]];
    }

    memset(&freq[0], 0, (n+1) * sizeof freq[0]);

    for(i=n; i>=1; i--)
    {
        freq[a[i]]++;
        l[i] = freq[a[i]];
    }

    long long ans = 0;

    for(i=n-1; i>=1; i--)
    {
        ft.add(l[i+1], 1);
        ans += ft.sum(r[i]-1);
    }

    cout << ans << "\n";

    return 0;
}