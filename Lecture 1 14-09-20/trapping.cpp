// { Driver Code Starts
#include<bits/stdc++.h>

using namespace std;


 // } Driver Code Ends


/*
    We can observe that for each position that is able to
    contain water, the quantity of water contained is given by:
    
    s(i) = min{max 0<=j<=i-1 h[j],  max i+1<=j<=n-1 h[j] }-h[i]
    
    where h[i] is the height of position i. This value is negative
    if a position can't contain water.
    
    The algorithm first computes two arrays MR and ML such that:
    ML[i] = max 0<=j<=i h[j] while MR[i] = max i+1<=j<=n-1.
    In this way each s(i) can be computed in O(1). After this
    for each position i for which s(i)>0 it computes the total
    amount of trapped water.
    
    Time: O(n)
    Space: O(n) because of the two additional arrays ML and MR.
*/

int trappingWater(int arr[], int n){

    vector<int> ml(n), mr(n);
    int maxl = 0, maxr = 0;
    long long water = 0;
    size_t i;
    
    for(i=0; i<n; i++)
    {
        if(arr[i]>maxl)
            maxl = arr[i];
        
        if(arr[(n-1)-i]>maxr)
            maxr = arr[(n-1)-i];
        
        mr[(n-1)-i] = maxr;
        ml[i] = maxl;
    }
    
    for(i=1; i<n-1; i++)
        if(min(ml[i-1], mr[i+1])-arr[i]>0) water += min(ml[i-1], mr[i+1])-arr[i];
    
    return water;
}

// { Driver Code Starts.

int main(){
    
    int t;
    //testcases
    cin >> t;
    
    while(t--){
        int n;
        
        //size of array
        cin >> n;
        
        int a[n];
        
        //adding elements to the array
        for(int i =0;i<n;i++){
            cin >> a[i];            
        }
        
        //calling trappingWater() function
        cout << trappingWater(a, n) << endl;
        
    }
    
    return 0;
}  // } Driver Code Ends