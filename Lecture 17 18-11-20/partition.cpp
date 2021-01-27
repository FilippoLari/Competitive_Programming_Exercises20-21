// { Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends


// User function Template for C++

class Solution{
public:

    /*
     * The solution uses the same algorithm as in knapsack,
     * it sets the size of the knapsack equal to half the sum
     * of elements, also the vectors of weights and values are set
     * equals to the input vector.
     * 
     * In this way in dp[N][S/2] it will find a value which is
     * <= than S/2, because if E is the set of chosen items 
     * holds that sum of i in E of w[i] = sum of i in E of a[i] <= S/2.
     * The only thing that it need to do is to check
     * if dp[N][S/2] is exactly equal to S/2.
     * 
     * Time: each position of dp can be filled in constant time, hence
     *       computing dp[N][S/2] takes theta(N*S) time.
     * 
     * Space: theta(N*S) because dp is of size (N+1)x(s/2 +1).
     */


    int equalPartition(int N, int arr[])
    {
        int S = 0, i, j;
        
        for(i=0; i<N; i++)
            S+= arr[i];
            
        if(S&1) return 0;
        
        vector<vector<int>> dp(N+1, vector<int>((S/2)+1, 0));
        
        for(i=1; i<N+1; i++)
            for(j=1; j<(S/2)+1; j++)
                if(arr[i-1]>j) dp[i][j] = dp[i-1][j];
                else dp[i][j] = max(dp[i-1][j], arr[i-1]+dp[i-1][j-arr[i-1]]);
                
        return (dp[N][S/2]==S/2);
    }
};

// { Driver Code Starts.

int main(){
    int t;
    cin>>t;
    while(t--){
        int N;
        cin>>N;
        int arr[N];
        for(int i = 0;i < N;i++)
            cin>>arr[i];
        
        Solution ob;
        if(ob.equalPartition(N, arr))
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }
    return 0;
}  // } Driver Code Ends
