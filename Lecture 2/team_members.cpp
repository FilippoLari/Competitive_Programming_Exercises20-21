#include <bits/stdc++.h>
#include <vector>
 
using namespace std;

/*
	The algorithm read the input and make an array of tuples
	(i, j, str) which denotes the strenght of a team composed by i and j.
	Then, sorts this array by the strenght value and start making teams
	from the strongest one to the weakest one, keeping track of which people
	have not yet been selected.
	
	Time: O(n^2log(n)) as we sort an array of length bin(2*n, 2) = n*(2*n-1) = O(n^2).
	Space: theta(n) assuming sort doesn't use any extra space.
*/

bool sortby(const tuple<int,int,int> &a, const tuple<int,int,int> &b)
{
    return (get<2>(a) > get<2>(b));
}
 
int main(void)
{
    vector<tuple <int, int, int>> members;
    vector<bool> selected;
    vector<int> result;
    int n, i, j, str;
 
    cin >> n;
 
    members.reserve(n*(2*n-1));
    result.reserve(2*n+1);
 
    for(i=0; i<2*n+1; i++)
        result[i] = 0;
 
    for(i=2; i<=2*n; i++)
        for(j=1; j<=i-1; j++)
        {
            cin >> str;
            members.push_back(make_tuple(i,j,str));
        }
 
    sort(members.begin(), members.end(), sortby);
 
    int first, second;
 
    for(i=0; i<members.size(); i++)
    {
        first = get<0>(members[i]);
        second = get<1>(members[i]);
 
        if(!result[first] && !result[second])
        {
            result[first] = second;
            result[second] = first;
        }
    }
 
    for(i=1; i<2*n+1; i++)
        cout << result[i] << " ";
 
    return 0;
}