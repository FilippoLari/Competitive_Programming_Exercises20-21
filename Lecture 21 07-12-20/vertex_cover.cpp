#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> tree;
vector<vector<int>> dp;

void dfs(int node, int parent)
{
    for (int child : tree[node])
    {
        if (child != parent)
        {
            dfs(child, node);
            dp[0][node] += dp[1][child];
            dp[1][node] += min(dp[0][child], dp[1][child]);
        }
    }

    dp[1][node]++;
}

/*
    The algorithm computes the size of the vertex cover 
    using the following dynamic programming table:

    dp[0][u] = size of the vertex cover of the tree with root u
               which doesn't include u.
    dp[1][u] = size of the vertex cover of the tree with root u
               which includes u.

    It performs a DFS visit of the tree and for each internal node
    u considers the two cases. u is not part of the vertex cover, hence
    its children must be included in the vertex cover, or u is part of
    the vertex cover, hence it considers the minimum between inserting its
    childs or not.

    Finally the result is the minimum between dp[0][1] and dp[1][1].

    Time: O(n) because each position of dp is filled in O(1) time.
    Space: O(n).
*/

int main()
{
    int n, u, v, i;

    cin >> n;

    dp = vector<vector<int>>(2);
    dp[0] = vector<int>(n+1,0);
    dp[1] = vector<int>(n+1,0);

    tree.reserve(n+1);

    for (i=0; i<n-1; i++)
    {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1, -1);

    cout << min(dp[1][1],dp[0][1]) << "\n";

    return 0;
}