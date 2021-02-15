// { Driver Code Starts

#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends


/*
 * The algorithm builds a table dp of size (|s|+1)x(|t|+1),
 * such that dp[i][j] = edit distance between s and t
 * up to i-th character of s and j-th character of t.
 * 
 * In this way we have that dp[0][j] = j for j = 0,1,2,..,|t|
 * because it's the edit distance between the empty string and
 * the string t up to the j-th character.
 * 
 * Using the same reasoning dp[0][i] = i for i=0,1,2,..,|s|.
 * 
 * The algorithm fill the table following this rules:
 * 
 * if s[i] == s[j] then the edit distance is the same
 * as the edit distance between s and t up to the (i-1)-th and
 * (j-1)-th characters, hence dp[i][j] = dp[i-1][j-1].
 * 
 * 
 * dp[i][j] = 1+min{dp[i-1][j-1], dp[i-1][j], dp[i][j-1]}
 * 
 * Time: each position of dp can be filled in costant time,
 *       hence the time required for computing dp[|s|][|t|]
 *       is theta(|s|x|t|).
 * 
 * Space: theta(|s|x|t|).
 */

class Solution
{
	public:
		int editDistance(string s, string t)
		{
		    int n = s.length(), m = t.length(), i, j;
		    int dp[n+1][m+1];
		    
            // edit distance between s and the empty string
		    for(i=0; i<n+1; i++)
		        dp[i][0] = i;
		        
            // edit distance between t and the empty string
		    for(j=0; j<m+1; j++)
		        dp[0][j] = j;
		    
		    for(i=1; i<n+1; i++)
		        for(j=1; j<m+1; j++)
		            if(s[i-1]==t[j-1]) dp[i][j] = dp[i-1][j-1];
		            else dp[i][j] = 1+min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1]));
            
		    return dp[n][m];
		}
};

// { Driver Code Starts.
int main(){
    int T;
    cin >> T;
    while(T--)
    {
    	string s, t;
    	cin >> s >> t;
    	Solution ob;
    	int ans = ob.editDistance(s, t);
    	cout << ans <<"\n";
    }
	return 0;
}
  // } Driver Code Ends
