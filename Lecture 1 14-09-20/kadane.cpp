// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends


/*
    An optimal solution has the following properties:
    
    1) The sum of each prefix is positive.
    
    2) The element that preceds the first one of the
       solution is negative.
    
    Exploiting 1) and 2) the algorithm scans the array
    computing the sum of the examined values and whenever the 
    sum becomes negative it drops the current solution and set
    the sum to the current element.
    
    Time: O(n)
    Space: O(1)
*/

int maxSubarraySum(int arr[], int n){
    int sum=0, max=0;
    for(size_t i=0; i<n; i++)
    {
        if(sum>0) sum += arr[i];
        else sum = arr[i];
        
        if(sum>max) max = sum;
    }    
    return max;
}


// { Driver Code Starts.

int main()
{
    int t,n;
    
    cin>>t; //input testcases
    while(t--) //while testcases exist
    {
        
        cin>>n; //input size of array
        
        int a[n];
        
        for(int i=0;i<n;i++)
            cin>>a[i]; //inputting elements of array
        
        cout << maxSubarraySum(a, n) << endl;
    }
}
  // } Driver Code Ends