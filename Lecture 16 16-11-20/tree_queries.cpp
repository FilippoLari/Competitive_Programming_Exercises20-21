#include <bits/stdc++.h>

using namespace std;

#define MAXN 200001

struct Query {
    int l, r, v, k, block_size, idx;
    bool operator<(Query other) const
    {
        if(l/block_size != other.l/block_size)
            return make_pair(l / block_size, r) < make_pair(other.l / block_size, other.r);
        else
            return (l/block_size & 1) ? (r<other.r) : (r>other.r);
    }
};

vector<vector<int>> tree;
vector<int> colors;
vector<int> freq;
vector<int> first;
vector<int> last;
vector<int> euler;
vector<int> cc;

void add(int color, int k)
{
    freq[color]++;
    cc[freq[color]]++;
}

void remove(int color, int k)
{
    cc[freq[color]]--;
    freq[color]--;
}

int t = 0;

void dfs(int v, int p){
	t++;
    first[v] = t;
    euler[t] = v;
	for(auto &u : tree[v]) 
        if(u != p) 
            dfs(u, v);

	last[v] = t;
}

/*
    The algorithm computes three arrays using a dfs visit on the tree.
    
    -euler such that euler[i] = node visited at step i.
    -first such that first[i] = 
    -last such that last[i] = 

    After this each node u in a query can be converted into
    a pair composed by first[u] and last[u]. In this way
    it can uses mo's algorithm to solve the set of queries.

    Time: O((n+m)sqrt(n))
    Space: O(n) because of the additional arrays.
*/

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, i, v, k;
    
    cin >> n >> m;

    colors = vector<int>(MAXN);
    freq = vector<int>(MAXN, 0);
    euler = vector<int>(MAXN);
    cc = vector<int>(MAXN,0);
    const int block_size = sqrt(n);

    for(i=1; i<=n; i++)
        cin >> colors[i];

    tree = vector<vector<int>>(n+1);
    first = vector<int>(n+1);
    last = vector<int>(n+1);

    for(i=0; i<n-1; i++)
    {
        cin >> v >> k;
        tree[v].push_back(k);
        tree[k].push_back(v);
    }

    dfs(1, 0);

    vector<Query> q(m);
    vector<int> ans(m, 0);

    for(i=0; i<m; i++)
    {
        cin >> v >> k;
        q[i] = {first[v],last[v],v,k,block_size,i}; 
    }

    sort(q.begin(), q.end());

    int cur_l = 0;
    int cur_r = 0;

    for (Query q : q) {
        while (cur_l > q.l) {
            cur_l--;
            add(colors[euler[cur_l]], q.k);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(colors[euler[cur_r]], q.k);
        }
        while (cur_l < q.l) {
            remove(colors[euler[cur_l]], q.k);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(colors[euler[cur_r]], q.k);
            cur_r--;
        }

        ans[q.idx] = cc[q.k];
    }

    for(i=0; i<m; i++)
        cout << ans[i] << "\n";

    return 0;
}