// { Driver Code Starts
#include <bits/stdc++.h>

using namespace std;

int maxMeetings(int *, int *, int);

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int start[n], end[n];
        for (int i = 0; i < n; i++) cin >> start[i];

        for (int i = 0; i < n; i++) cin >> end[i];

        int ans = maxMeetings(start, end, n);
        cout << ans << endl;
    }
    return 0;
}// } Driver Code Ends

/*
    The algorithm uses a greedy strategy.
    First of all stores the starting and ending
    points of the meeting in an array of pairs. Then
    sorts the array by the ending points and ..
    After this selects all the activities that satisfy
    th eproblem's constraints starting from
    the first one.
    
    Time: O(nlogn) because of sorting.
    Space: O(n) because of the additional array.
*/

int cmp(pair<int,int> p1, pair<int,int> p2)
{
    if(p1.second==p2.second) 
        return ((p1.second-p1.first+1)<(p2.second-p2.first+1));
    else return p1.second < p2.second;
}

int maxMeetings(int start[], int end[], int n) {
    
    vector<pair<int,int>> s(n);
    pair<int,int> m;
    int i, ans;
    
    for(i=0; i<n; i++)
    {
        s[i].first  = start[i];
        s[i].second = end[i];
    }
    
    sort(s.begin(), s.end(), cmp);
    
    m   = s[0];
    ans = 1;
    
    for(i=1; i<n; i++)
    {
        if(m.second<s[i].first) {ans++; m = s[i];}
    }
    
    return ans;
}