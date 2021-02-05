#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

/*
	The algorithm sorts the lengths then
	each sequence of single or repeating lengths is counted as
	one tower keeping track of the maximal height.
	
	Time:  O(nlogn) because of sorting.
	Space: O(1). 
*/

int main()
{
    int N, i;
    
    cin >> N;
    
    int l[N];
    
    for(i=0; i<N; i++)
        cin >> l[i];
        
    sort(l, l+N);
    
    int max=1, h=1, bars=1;
    
    for(i=1; i<N; i++)
    {
        if(l[i]!=l[i-1])
        {
            if(max<h) max=h;
            bars++;
            h = 1;
        }
        else
            h++;
    }
    
    if(max<h) max=h;
    
    cout << max << " " << bars;
    
    return 0;
}
