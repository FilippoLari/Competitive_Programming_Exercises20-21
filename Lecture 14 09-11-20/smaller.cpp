#include <bits/stdc++.h>

using namespace std;

/*
    To answer the queries is sufficient to keep
    updated an array of frequency of elements in the given ranges.
    The result of a query count(i,j,X) is the prefix sum of the array up to
    position X.

    The array can be kept updated using Mo's algorithm and a Fenwick tree.

    Time: O((n+m)sqrt(n)log(n))
    Space: theta(n)
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

struct Query {
    int l, r, x, block_size, idx;
    bool operator<(Query other) const
    {
        if(l/block_size != other.l/block_size)
            return make_pair(l / block_size, r) < make_pair(other.l / block_size, other.r);
        else
            return (l/block_size & 1) ? (r<other.r) : (r>other.r);
    }
};

void add(int idx, fenwick_tree<int> &f)
{
    f.add(idx, 1);
}

void remove(int idx, fenwick_tree<int> &f)
{
    f.add(idx,-1);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, l, r, x, i, block_size;

    cin >> n >> m;

    block_size = sqrt(n);

    vector<int> a(n);
    vector<Query> q(m);
    vector<int> ans(m);
    fenwick_tree<int> f = fenwick_tree<int>(n);

    for(i=0; i<n; i++)
        cin >> a[i];

    for(i=0; i<m; i++)
    {
        cin >> l >> r >> x;
        q[i] = {l,r,x,block_size,i};
    }

    sort(q.begin(), q.end());

    int cur_l = 0;
    int cur_r = -1;

    for (Query q : q) {
        while (cur_l > q.l) {
            cur_l--;
            add(a[cur_l], f);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(a[cur_r], f);
        }
        while (cur_l < q.l) {
            remove(a[cur_l], f);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(a[cur_r], f);
            cur_r--;
        }
        ans[q.idx] = f.sum(q.x);
    }

    for(i=0; i<m; i++)
        cout << ans[i] << "\n";
} 