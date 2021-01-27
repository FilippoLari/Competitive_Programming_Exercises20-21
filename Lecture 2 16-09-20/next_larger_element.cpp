#include <iostream>
#include <deque>
#include <vector>
using namespace std;

/*
    Using the same analysis as for Sliding window maximum,
    for each test case:
    
    Time: O(n)
    Space: O(n)  
*/

int main() {
	
	int t, n, a, i;
	
	//Q ia deque of indexes
	deque<int> Q;
	
	cin >> t;
	
	while(t--)
	{
	    cin >> n;
	  
	    vector<long long> A;
        A.reserve(n);
	
    	for(i=0; i<n; ++i)
    	{
    	    cin >> A[i];
    	    
    	    /*
    	        updates all the position in A
    	        for which the current element is bigger than
    	        the ones found at positions given by Q.
    	    */
    	    
    	    while((!Q.empty()) && A[i] > A[Q.back()] )
    	    {
    	        A[Q.back()] = A[i];
    	        Q.pop_back();
    	    }
    	    
    	    Q.push_back(i);
    	}
    	
    	/*
            the remaining elements of the array with 
            indices in the queue do not have a next larger element.
    	*/
    	while(!Q.empty())
    	{
    	    A[Q.back()] = -1;
    	    Q.pop_back();
    	}
    	
    	for(i=0; i<n; i++)
    	    cout << A[i] << " ";
    	    
    	cout << "\n";
    }
	
	return 0;
}