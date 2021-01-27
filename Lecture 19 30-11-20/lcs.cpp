// { Driver Code Starts
#include<bits/stdc++.h>
const int mod=1e9+7;
using namespace std;

int lcs(int, int, string, string);

int main()
{
    int t,n,k,x,y;
    
    cin>>t;
    while(t--)
    {
        cin>>x>>y;          // Take size of both the strings as input
        string s1,s2;
        cin>>s1>>s2;        // Take both the string as input
        
        cout << lcs(x, y, s1, s2) << endl;
    }
    return 0;
}
// } Driver Code Ends


// function to find longest common subsequence


/*
    We can build a table dp of size |s1|+1*|s2|+1, such that 
    for each (i,j) dp[i][j] = lcs(s1[0,i],s2[0,j]).
    
    If s1[i] == s2[j] then we have found a common character
    in the two strings, hence lcs(s1[0,i],s2[0,j]) = lcs(s1[0,i-1],s2[0,j-1])+1.
    
    Otherwise we have to take the maximum between
    lcs(s1[0,i-1], s2[0,j]) and lcs(s1[0,i], s2[0,j-1]). 
    We don't need to include lcs(s1[0,i], s2[0,j]) in the maximum,
    because it will be always smaller or equal to the two above.
    
    Finally the result is contained in dp[|s1|][|s2|].
    
    Time: theta(|s1|*|s2|)
    Space: theta(|s1|*|s2|)
*/

int lcs(int x, int y, string s1, string s2){
    int dp[x+1][y+1], i, j;
    
    //computes the lcs between empty string and s1
    for(i=0; i<x+1; i++)
        dp[i][0] = 0;
        
    //computes the lcs between empty string and s2
    for(j=0; j<y+1; j++)
        dp[0][j] = 0;
    
    //computes dp according to the rule defined above
    for(i=1; i<x+1; i++)
        for(j=1; j<y+1; j++)
            if(s1[i-1]==s2[j-1]) dp[i][j] = dp[i-1][j-1]+1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    
    //dp[x][y] contains the lcs between s1 and s2
    return dp[x][y];
}

