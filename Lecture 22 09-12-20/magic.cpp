#include <bits/stdc++.h>

using namespace std;

/*
    If a number is magic the following holds:

    -first digit is a 1.

    -all the digits are 1 or 4.
    
    -there are at most 2 consecutives 4. Because
     combining 1, 14 and 144 it's impossible to
     achive that.

    The algorithm just check this properties.

    Time: O(n) because of the scan and the call to .find()
          which in the worst case could be implemented as
          a linear scan.

    Space: O(n)
*/

int main(void)
{
    bool magic = true;
    string n;
    int i;

    cin >> n;

    if(n[0]!='1') magic=false;

    if(n.find("444")!=n.npos) magic=false;

    for(i=1; i<n.size() && magic; i++)
    {
        if(n[i]!='1' && n[i]!='4')
            magic=false;
    }

    if(magic) cout << "YES\n";
    else cout << "NO\n";

    return 0;
}