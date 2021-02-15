#include <bits/stdc++.h>

using namespace std;

struct frog {
    long x;
    long xt;
    int idx;
    
    bool operator<(frog const& f) const
    {
        return (xt < f.xt);
    }
};
 
struct mosquitoe {
    long b;
    long a;

    bool operator<(mosquitoe const& m) const
    {
        return (b < m.b);
    }
};

/*
    The algorithm implements the solution discussed in class.

    Time: O((n+m)logn)
    Space: O(n+m)
*/

int cmpFrogs(const frog &a, const frog &b)
{
    return a.x < b.x;
}

int main(void)
{
    int n, m, i;
    long x, xt;

    cin >> n >> m;

    vector<pair<long,long>> ans(n);
    vector<frog> initial_frogs(n);

    set<frog> frogs;
    multiset<mosquitoe> mosquitoes;

    for(i=0; i<n; i++)
    {
        cin >> x >> xt;
        initial_frogs[i] = {x, x+xt, i};
        ans[i] = {0, xt};
    }

    sort(initial_frogs.begin(), initial_frogs.end(), cmpFrogs);

    frog curr = initial_frogs[0];

    frogs.insert(curr);

    for (i=1; i<n; i++) 
    {
        if (initial_frogs[i].x <= curr.xt ) 
        {
            if (initial_frogs[i].xt > curr.xt) 
            {
                initial_frogs[i].x = curr.xt + 1;
                frogs.insert(initial_frogs[i]);
                curr = initial_frogs[i];
            }
        }
        else 
        {
            frogs.insert(initial_frogs[i]);
            curr = initial_frogs[i];
        }
    }


    for(i=0; i<m; i++)
    {
        mosquitoe mos;

        cin >> mos.b >> mos.a;

        mosquitoes.insert(mos);

        auto it = frogs.lower_bound({0, mos.b, 0});

        if(it!=frogs.end() && it->x <= mos.b) 
        {
            frog f = *it;

            auto mosquito = mosquitoes.lower_bound({f.x, 0});

            while (mosquito != mosquitoes.end() && mosquito->b <= f.xt && mosquito->b >= f.x) 
            {
                ans[f.idx].first++;
                ans[f.idx].second += mosquito->a;

                f.xt += mosquito->a;
                mosquito = mosquitoes.erase(mosquito);
            }

            auto it2 = frogs.erase(it);

            while(it2 != frogs.end() && it2->x <= f.xt && it2->x >=f.x) 
            {
                if(it2->xt > f.xt)
                {
                    frog nf = { f.xt + 1, it2->xt, it2->idx};
                    frogs.erase(it2);
                    frogs.insert(nf);
                    break;
                }
                else
                    it2=frogs.erase(it2);
            }

            frogs.insert(f);
        }
    }

    for(i=0; i<n; i++)
        cout << ans[i].first << " " << ans[i].second << "\n";

    return 0;
}