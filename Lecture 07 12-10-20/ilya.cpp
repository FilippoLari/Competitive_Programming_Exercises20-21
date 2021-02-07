#include <iostream>
#include <string>
#include <vector>
 
using namespace std;

/*
	The algorithm computes an array P such that
	P[i] = number of positions 1<=k<=i such that s[k]=s[k+1].
	
	The answer to each query (l,r) is then P[r]-P[l-1].

	Time: O(n) preprocessing, O(1) per query.
	Space: O(n) because of the additional array P. 
*/

int main(void)
{
  string s;
  
  cin >> s;
  
  int n = s.size(), m;
  
  cin >> m;
  
  vector<pair<int,int>> q;
  int i, l, r;
  
  for(i=0; i<m; i++)
  {
      cin >> l >> r;
      q.push_back(make_pair(l,r));
  }
  
  vector<int> p;
  int sum = 0;
  p.reserve(n+1);
  p[0] = 0;
  
  for(i=0; i<n-1; i++)
  {
      if(s[i]==s[i+1])
      {
          sum++;
          p[i+1] = sum;
      }
      else p[i+1] = p[i];
  }
  
  p[n] = p[n-1];
  
  for(i=0; i<m; i++)
      cout << p[q[i].second-1]-p[q[i].first-1] << "\n";
  
  return 0;
}