#include <iostream>
#include <set>
#include <vector>
    
using namespace std;

/*
	The algorithm keeps two indexes, 's' the starting point
	of the current longest k-good segment and 'e' its ending point.

	It also keeps and additional array 'occ' of size (10^6)+1, such that:
	
		occ[a[i]] = #occurrences of a[i] in the current segment. 
	
	At each iteration, if the number of distinct elements in the segment
	is less than or equal k it increases e, otherwise it increases s and updates
	the maximum lenght and the starting/ending points if necessary.

	Using the array 'occ' the number of distinct elements in the current segment
	could be keep updated in O(1) time.

	Time: O(n)
	Space: O(n)
*/

int main(void)
{
    int n, k, i;
 
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    cin >> n >> k;
 
    vector<int> a;
    vector<int> occ(1000001, 0);
    a.reserve(n);
 
    for(i=0; i<n; i++)
        cin >> a[i];
 
    int s=0, e=0, max_s=0, max_e=0, max=-1, d=0;
 
    while(e<n)
    {
        if(d<=k)
        {
            if(occ[a[e]]==0) d++;
            occ[a[e]]++;
            e++;
        }
 
        if(d<=k && (e-s)>max)
        {
            max = e-s;
            max_s = s;
            max_e = e-1;
        }
 
        if(d>k)
        {
            if(occ[a[s]]==1) d--;
            occ[a[s]]--;
            s++;
        }
    }
 
    cout << max_s+1 << " " << max_e+1 << "\n";
 
    return 0;
}
