// { Driver Code Starts

#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends


/*
 * We can look at positions of the array as nodes of a graph,
 * for each position (j,i) with j<i, we have an edge from j to i
 * if the distance from i to j is at least the
 * value in position j. The weight of those edges is 
 * equal to the distance between i and j. In this way
 * the minimum number of jumps required to reach position i
 * is equal to the minimum number of jumps to reach the node
 * connected to i with maximum weight plus one. The function
 * minJumps1 implement this idea using an array 'dp' of size n.
 * 
 * Time: in the worst case for each position  1<=i<=n-1 the algorithm
         examine i positions, hence the running time is O(n^2).
 * Space: theta(n)
 *
 * Unfortunately a quadratic running time is not enougth to get accepted, and
 * i was not able to find the linear time solution. The function 
 * minJumps is an implementation from: 
 *
 * https://www.geeksforgeeks.org/minimum-number-jumps-reach-endset-2on-solution/
 */


// Function to return minimum number of jumps to end of array
int minJumps1(int arr[], int n){
    
    if(arr[0]==0) return -1;
    if(arr[0]>=n) return 1;
    
    long dp[n], i, j, max, idx;
    dp[0] = 0;
    
    for(i=1; i<n; i++)
    {
        max=0, idx=0;
        
        for(j=0; j<i; j++)
            if(i-j<=arr[j] && i-j>max) {max = i-j; idx = j;}
        
        /*
         * if it can't update the max it means that
         * from position 0 we can't reach position i,
         * therefore not even position n is reachable.
         */
        if(max==0) return -1;
            
        dp[i] = dp[idx]+1;
        
        if(arr[i]>=n-1-i && i!=n-1) return dp[i]+1;
    }
    
    return dp[n-1];
}

int minJumps(int arr[], int n)
{
    if (n <= 1)
        return 0;

    if (arr[0] == 0)
        return -1;

    int maxReach = arr[0];
    int step = arr[0];

    int jump = 1;
 
    int i = 1;
    for (i = 1; i < n; i++) {
        if (i == n - 1)
            return jump;
 
        maxReach = max(maxReach, i + arr[i]);
 
        step--;

        if (step == 0) {
            jump++;
            if (i >= maxReach)
                return -1;
            step = maxReach - i;
        }
    }
 
    return -1;
}


// { Driver Code Starts.

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,i,j;
        cin>>n;
        int arr[n];
        for(int i=0; i<n; i++)
            cin>>arr[i];
            
        cout<<minJumps(arr, n)<<endl;
    }
    return 0;
}
  // } Driver Code Ends
