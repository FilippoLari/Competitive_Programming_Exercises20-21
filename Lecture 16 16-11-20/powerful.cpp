#include <bits/stdc++.h>

using namespace std;

/*
    The solution uses Mo's algorithm to answer each query.
    It keeps a frequency array which is update by the 
    functions add and remove.

    Both Add and Remove updates the frequency of the new element
    that enters or leave the range and updates also the current answer
    in O(1) time.

    Time: O(sqrt(n)*(n+q)) with q the number of queries.
    Space: theta(n)
*/

vector<long long> freq;
vector<long long> a;
int block_size;
long long res;

struct Query {
    int l, r, idx;

    /*
        sorting the right endpoints in ascending order in even blocks
        and in decreasing order in odd blocks reduces the movements of curr_r
        in Mo's algorithm. This optimization was needed in order to not get
        TLE in test case 56.
    */
    bool operator<(Query other) const
    {
        if(l/block_size != other.l/block_size)
            return make_pair(l / block_size, r) < make_pair(other.l / block_size, other.r);
        else
            return (l/block_size & 1) ? (r<other.r) : (r>other.r);
    }
};

void remove(int idx)
{
    freq[a[idx]]--;
    // removes the previous contribution of the frequency of the element that leaves the current range
    res = res - (freq[a[idx]]+1)*(freq[a[idx]]+1)*a[idx] + (freq[a[idx]])*(freq[a[idx]])*a[idx];
}

void add(int idx)
{
    freq[a[idx]]++;
    // removes the previous contribution of the frequency of the element that enters the current range
    res = res - (freq[a[idx]]-1)*(freq[a[idx]]-1)*a[idx] + (freq[a[idx]])*(freq[a[idx]])*a[idx];
}

vector<long long> mo_s_algorithm(vector<Query> queries) {
    vector<long long> answers(queries.size());
    sort(queries.begin(), queries.end());

    freq.resize(1000001, 0);

    int cur_l = 0;
    int cur_r = 0;

    res = 0;

    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = res;
    }
    return answers;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t, l, r, i;

    cin >> n >> t;

    a.reserve(n+1);
    a[0] = 0;
    vector<Query> q(t);

    block_size = sqrt(n);

    for(i=1; i<=n; i++)
        cin >> a[i];

    for(i=0; i<t; i++)
    {
        cin >> l >> r;
        q[i] = {l,r,i};
    }

    vector<long long> ans = mo_s_algorithm(q);

    for(i=0; i<t; i++)
        cout << ans[i] << "\n";
}