#include <bits/stdc++.h>

using namespace std;

/*
    We can notice that the longest palindromic subsequence
    of a string can be obtained by computing the longest
    common subsequence between the string and the same string
    reversed. The algorithm reuses the same solution to LCS.
    
    Time: For each test case, O(n^2) where n is the length 
          of the considered string.
          
    Space: O(n^2).
*/

int lcs(int x, int y, string s1, string s2){
    int dp[x+1][y+1], i, j;

    for(i=0; i<x+1; i++)
        dp[i][0] = 0;

    for(j=0; j<y+1; j++)
        dp[0][j] = 0;

    for(i=1; i<x+1; i++)
        for(j=1; j<y+1; j++)
            if(s1[i-1]==s2[j-1]) dp[i][j] = dp[i-1][j-1]+1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    return dp[x][y];
}

int main() {
	
	int t;
	string s, rev;
	
	cin >> t;
	
	while(t--)
	{
	    cin >> s;
	    
	    rev = string(s.rbegin(),s.rend());
	    
	    cout << lcs(s.size(),s.size(),s,rev) << "\n";
	}
	
	return 0;
}