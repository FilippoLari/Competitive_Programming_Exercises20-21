#include <bits/stdc++.h>

using namespace std;

/*
    The algorithm uses a Fenwick tree. In order to make
    a range update (l,r,val) it add val to position l and
    subtract val from position r+1.

    After all the updates the value at position i is given
    by the sum up to i.

    Time: O((u+q)logn) where u is the number of updates and q the numebr of queries.
    Space: O(n) because of the fenwick tree.
*/

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

int main(void)
{
    int t, n ,u, l, r, q, index, i, val;

    cin >> t;

    while(t--)
    { 
        cin >> n >> u;

        fenwick_tree<long> f(n, 0);

        for(i=0; i<u; i++)
        {
            cin >> l >> r >> val;
            f.add(l,val);
            f.add(r+1,-val);
        }

        cin >> q;

        for(i=0; i<q; i++)
        {
            cin >> index;
            cout << f.sum(index) << "\n";
        }
    }

    return 0;
}