#include <bits/stdc++.h>

using namespace std;

struct FenwickTree {
    vector<int> bit;
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

int sortTuple(const tuple<int,int,int> &a, const tuple<int,int,int> &b)
{
    return get<0>(a)<get<0>(b);
}

/*
    The algorithm remaps all the segments <l_i,r_i> such that
    l_i and r_i are <= n. This is done by sorting and replacing
    l_i and r_i with their rank.

    After this, for each segment <l_i, r_i> the answer is the number of segments
    <l_j, r_j> for which l_j > l_i and r_j < r_i. In order to compute this number
    it uses a Fenwick tree and add a one in correspondence of the right extreme of each
    segment. In this way, processing the segments in increasing order of the left extreme,
    a range sum from l_i to (r_i)-1, is the number of segments inside the interval <l_i, r_i>.
    After computing an answer for a segment <l_i, r_i> we also need to decrease position
    r_i by one, in order to avoid to count it multiple times. 

    Time: O(nlogn) because of sorting and for each segment we execute a sum operation two times
          which takes O(logn).

    Space: O(n) because of the fenwick tree.
*/

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l, r, i;

    cin >> n;

    vector<tuple<int,int,int>> s(n);
    vector<int> all;
    all.reserve(2*n);

    for(i=0; i<n; i++)
    {
        cin >> l >> r;
        s[i] = make_tuple(l, r, i);
        all.push_back(l);
        all.push_back(r);
    }

    sort(all.begin(), all.end());

    for(i=0; i<n; i++)
    {
        get<0>(s[i]) = distance(all.begin(), lower_bound(all.begin(), all.end(), get<0>(s[i])));
        get<1>(s[i]) = distance(all.begin(), lower_bound(all.begin(), all.end(), get<1>(s[i])));
    }

    FenwickTree FT(2*n);
    vector<int> ans(n);

    sort(s.begin(), s.end(), sortTuple);

    for(i=0; i<n; i++)
        FT.add(get<1>(s[i]), 1);

    for(i=0; i<n; i++)
    {
        ans[get<2>(s[i])] = FT.sum(get<0>(s[i]), get<1>(s[i])-1);
        FT.add(get<1>(s[i]), -1);
    }

    for(i=0; i<n; i++)
        cout << ans[i] << "\n";
}