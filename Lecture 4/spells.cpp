#include <iostream>
#include <set>

using namespace std;

int compute_damage(const set<int> &f, const set<int> &l)
{
    auto l_start = l.begin(), f_start = f.begin(), f_end = f.end();
    auto lr_start = l.rbegin();
    
    int max_damage = 0;
    bool d = false;
    
    while(!l.empty() && *l_start!=*lr_start && f_start!=f_end)
    {
        if(*l_start>*f_start)
        {
            max_damage += *lr_start + 2*(*l_start);
            lr_start++;
            l_start++;
        }
        else
        {
            max_damage += *lr_start + 2*(*f_start);
            lr_start++;
            f_start++;
        }
    }
    
    if(!l.empty() && *l_start==*lr_start) {max_damage += *l_start; d=true;}
    
    while(f_start!=f_end)
    {
        if(d){max_damage += 2*(*f_start); d=false;}
        else max_damage += *f_start;
        f_start++;
    }
        
    while(!l.empty() && *l_start!=*lr_start)
    {
        max_damage += *lr_start + 2*(*l_start);
        l_start++;
        lr_start++;
    }
        
    return max_damage;
}

int main()
{
    int n, tp, d;
    set<int> f, l;
    
    cin >> n;
    
    while(n--)
    {
        cin >> tp >> d;
        
        if(d<0) if(!tp) f.erase(d*-1); else l.erase(d*-1);
        else if(!tp) f.insert(d); else l.insert(d);
        
        cout << compute_damage(f, l) << "\n";
    }
    
    return 0;
}
