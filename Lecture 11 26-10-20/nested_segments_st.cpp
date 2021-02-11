#include <bits/stdc++.h>

using namespace std;

const int N = 400001;  

int arr_s = 0;

int tree[2 * N]; 

void build(vector<int> &arr)  
{  
    arr_s = arr.size();

    for (int i=0; i<arr_s; i++)     
        tree[arr_s+i] = arr[i]; 
      
    for (int i = arr_s - 1; i > 0; --i)      
        tree[i] = tree[i<<1] + tree[i<<1 | 1];     
} 
  
void updateTreeNode(int p, int value)  
{  
    tree[p+arr_s] = value; 
    p = p+arr_s; 
      
    for (int i=p; i > 1; i >>= 1) 
        tree[i>>1] = tree[i] + tree[i^1]; 
} 
  
int query(int l, int r) 
{  
    int res = 0; 
      
    for (l += arr_s, r += arr_s; l < r; l >>= 1, r >>= 1) 
    { 
        if (l&1)  
            res += tree[l++]; 
      
        if (r&1)  
            res += tree[--r]; 
    } 
      
    return res; 
} 

/*
    Same logic as nested segments but uses a Segment tree instead of
    a Fenwick tree.

    Time: O(nlogn)
    Space: O(n)
*/

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l, r, i;

    cin >> n;

    vector<tuple<int,int,int>> s(n);
    vector<int> all;

    for(i=0; i<n; i++)
    {
        cin >> l >> r;
        s[i] = make_tuple(l, r, i);
        all.push_back(l);
        all.push_back(r);
    }

    sort(all.begin(), all.end());

    vector<int> b(2*n, 0);
    vector<int> ans(n);

    for(i=0; i<n; i++)
    {
        get<0>(s[i]) = distance(all.begin(), lower_bound(all.begin(), all.end(), get<0>(s[i])));
        get<1>(s[i]) = distance(all.begin(), lower_bound(all.begin(), all.end(), get<1>(s[i])));

        b[get<1>(s[i])] = 1;
    }

    sort(s.begin(), s.end(), [](const tuple<int,int,int> &a, const tuple<int,int,int> &b){ return get<0>(a)<get<0>(b);});

    build(b);

    for(i=0; i<n; i++)
    {
        ans[get<2>(s[i])] = query(get<0>(s[i]), get<1>(s[i]));
        updateTreeNode(get<1>(s[i]), 0);
    }

    for(i=0; i<n; i++)
        cout << ans[i] << "\n";
}