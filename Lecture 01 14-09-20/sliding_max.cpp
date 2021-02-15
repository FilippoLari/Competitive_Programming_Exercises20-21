// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends

/*
    The algorithm scans the array and keeps a queue
    of the positions of the largest k elements. Each time
    a window "ends" the maximum is the element at position
    given by the top of the queue.

    Time: The number of operations is proportional to
          the number of operations done on the queue.
          Each element is pushed once and popped at most once.
          Hence the cost is O(n).
          
    Space: O(n) because at most n elements are in the queue.
*/

vector <int> max_of_subarrays(int *arr, int n, int k){
    
    deque<int> queue;
    vector<int> maxs;
    int i;
    
    maxs.reserve(n-k+1);
    
    for(i=0; i<n; ++i)
    {
        while(!queue.empty() && queue.front()<=i-k)
            queue.pop_front();
        
        while(!queue.empty() && arr[i]>=arr[queue.back()])
            queue.pop_back();
            
        queue.push_back(i);
        
        if(i >= k-1)
            maxs.push_back(arr[queue.front()]);
    }
    
    return maxs;
}


// { Driver Code Starts.

int main() {
	
	int t;
	cin >> t;
	
	while(t--){
	    
	    int n, k;
	    cin >> n >> k;
	    
	    int arr[n];
	    for(int i = 0;i<n;i++) 
	        cin >> arr[i];
	    
	    vector <int> res = max_of_subarrays(arr, n, k);
	    for (int i = 0; i < res.size (); i++) 
	        cout << res[i] << " ";
	    cout << endl;
	    
	}
	
	return 0;
}  // } Driver Code Ends