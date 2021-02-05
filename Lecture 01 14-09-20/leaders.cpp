// { Driver Code Starts
// C++ program to remove recurring digits from
// a given number
#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends


/*
    The algorithm uses a vector managed as a queue.
    For each element A[i], if the queue is not empty, 
    removes from it all the elements smaller than A[i], 
    after this pushes A[i] on the back of the queue.
    At end the queue contains all the leaders of the input array.
    
    Time: The number of operations performed is proportional
          to the number of operations done on the queue. Each
          element is pushed once and popped at most once. Hence
          the running time is O(n).
          
    Space: In the worst case the queue can consists of all the
           elements in the array, hence is O(n).
    
*/

vector<int> leaders(int a[], int n){
    
    vector<int> leaders(n);
    
    for(int i=0; i<n; i++)
    {
        while(!leaders.empty() && leaders.back()<a[i]) leaders.pop_back();
        
        leaders.push_back(a[i]);
    }
    
    return leaders;
}

// { Driver Code Starts.

int main()
{
   long long t;
   cin >> t;//testcases
   while (t--)
   {
       long long n;
       cin >> n;//total size of array
        
        int a[n];
        
        //inserting elements in the array
        for(long long i =0;i<n;i++){
            cin >> a[i];
        }
        
        //calling leaders() function
        vector<int> v = leaders(a, n);
        
        //printing elements of the vector
        for(auto it = v.begin();it!=v.end();it++){
            cout << *it << " ";
        }
        
        cout << endl;

   }
}
  // } Driver Code Ends