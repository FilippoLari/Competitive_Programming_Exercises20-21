#include <bits/stdc++.h>

using namespace std;

/*
    I was not able to find a solution, hence
    i followed this explanation: 
    
    https://github.com/rossanoventurini/CompetitiveProgramming/blob/master/notes/Greedy1.pdf

    Time: O(n) as the algorithm only scans the input string
    Space: O(n).
*/

int main()
{
    int n, res = 1, i;
    string s;

    cin >> n >> s;

    for(i=1; i < n; i++)
        if(s[i]!=s[i-1]) res++;
    
    cout << min(res + 2, n) << '\n';
}