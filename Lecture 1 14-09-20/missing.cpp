// { Driver Code Starts
// Initial template for C++

#include <bits/stdc++.h>
using namespace std;

int MissingNumber(vector<int>& array, int n);

// Position this line where user code will be pasted.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> array(n - 1);
        for (int i = 0; i < n - 1; ++i) cin >> array[i];

        cout << MissingNumber(array, n) << "\n";
    }
    return 0;
}// } Driver Code Ends


/*
   The sum of the first n integers is given by n*(n+1)/2.
   Hence the answer is given by the subtraction from the above value the sum 
   of the elements of the array.
   
   Time: O(n) for computing the sum.
   Space: O(1)
*/

int MissingNumber(vector<int>& array, int n) {
    
    int gsum = n*(n+1)/2, sum = 0;
    
    for(auto a : array)
        sum += a;
    
    return gsum-sum;
}