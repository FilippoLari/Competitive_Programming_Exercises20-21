#include <bits/stdc++.h>
 
using namespace std;
 
const int INF = 2e9;
 
set<int> strong, weak;
long long ans = 0;
set<int> fire;
int lightning;
 
void add_strong(int x) {
	strong.insert(x);
	ans += 2 * x;
}
 
void add_weak(int x) {
	weak.insert(x);
	ans += x;
}
 
void remove_strong(int x) {
	strong.erase(strong.find(x));
	ans -= 2 * x;
}
 
void remove_weak(int x) {
	weak.erase(weak.find(x));
	ans -= x;
}
 
void transfer_from_weak() {
	if (!weak.empty()) {
		int x = *weak.rbegin();
		remove_weak(x);
		add_strong(x);
	}
}
 
void transfer_from_strong() {
	if (!strong.empty()) {
		int x = *strong.begin();
		remove_strong(x);
		add_weak(x);
	}
}
 
int get_first(const set<int>& x) {
	return x.empty() ? INF : *x.begin();
}

/*
    In order to maximize the total damage we should be able
	to maximize the largest k spells, where k is the current number of
	lightning spells.

	The algorithm keeps two sets, the set of the strongest spells, the set
	of the weak spells and the set of fire spells. Each time it reads a new spell
	updates these three sets accordingly, and also updates the number of lightning
	spells if necessary. While updating these sets it also updates the answer, hence
	if a spell is inserted in the strongest spells it adds two times its power to the answer,
	while if it is inserted in the weak spells it adds only the value of its power. If
	a spell is removed from this sets it decreases the answer similarly.

	In order to compute the total damage it rebalances the sets of the weak and strongest spellsin
	such a way that the set of strongest spells contains exactly a number of spells equals to
	the number of lightning spells.

	Finally, in order to compute the damage the algorithm handles two special
	cases:

	- the set of the strongest spells is composed only by lightning spells, hence
	  it can only double k-1 best spells. The answer computed up to now must be
	  corrected by subtracting the value of the strongest spell and adding the
	  value of the best fire spell (if any).

	- otherwise the value of the answer is correct.


	Time: O(nlogn) because for n times it makes a constant number of operations
	      that require O(logn) time in the worst case.

	Space: O(n) because of the two sets. 
*/

int main() 
{	
    int n, i, type, power;

	cin >> n;

	for(i=0; i<n; i++) 
    {
        cin >> type >> power;
		
		if (power > 0) {
			if (power >= get_first(strong)) {
				add_strong(power);
			} else {
				add_weak(power);
			}
			if (type == 1) {
				lightning++;
			} else {
				fire.insert(power);
			}
		}
		if (power < 0) {
			power = -power;
			if (power >= get_first(strong)) {
				remove_strong(power);
			} else {
				remove_weak(power);
			}
			if (type == 1) {
				lightning--;				
			} else {
				fire.erase(fire.find(power));
			}
		}

		while (strong.size() < lightning) {
			transfer_from_weak();
		}
		while (strong.size() > lightning) {
			transfer_from_strong();
		}

		int best_fire = fire.empty() ? 0 : *fire.rbegin();

		if (!strong.empty() && best_fire < *strong.begin()) {
			long long corrected = ans - *strong.begin() + best_fire;
			cout << corrected << "\n";
		} else {
			cout << ans << "\n";
		}
	}	
}