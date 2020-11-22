#include <bits/stdc++.h>

using namespace std;

/*
 * The algorithm builds a table dp such that
 * for each (i,j) dp[i][j] is the maximum value it can obtain
 * with i items and a knapsack os size j.
 * 
 * The table is filled up in this way, if w[i] > j it can't choose
 * item i, hence dp[i][j] = dp[i-1][j]. Otherwise it look at the maximum
 * value that it can obtain by choosing item i or not, hence 
 * dp[i][j] = max(dp[i-1[j], v[i]+dp[i-1][j-w[i]]).
 * 
 * The result is contained in dp[n][S] where S is the size of the knapsack and
 * n the number of items.
 * 
 * Time: each position of dp is filled in constant time therefore
 *       the time required for computing dp[n][S] is theta(n*S).
 * Space: theta(n*S)
 */

int main(void)
{
    int s, n;
    
    cin >> s >> n;
    
    int w[n], v[n], dp[n+1][s+1], i, j;
    
    for(i=0; i<n; i++)
        cin >> w[i] >> v[i];
    
    //max value with a knapsack of size 0
    for(i=0; i<n+1; i++)
        dp[i][0] = 0;
        
    //max value if we don't have any items to choose
    for(j=0; j<s+1; j++)
        dp[0][j] = 0;
    
    for(i=1; i<n+1; i++)
        for(j=1; j<s+1; j++)
            if(w[i-1]>j) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max(dp[i-1][j], v[i-1]+dp[i-1][j-w[i-1]]);
    
    cout << dp[n][s] << "\n";
}
