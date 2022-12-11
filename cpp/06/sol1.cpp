/**
 *    Author: Nachiket Kanore
 *    Created: Tuesday 06 December 2022 10:28:02 AM IST
 **/
#include "bits/stdc++.h"
using namespace std;

#ifdef DEBUG
#include "debug.h"
#else
#define see(...) ;
#endif

#define int int64_t
#define sz(x) (int)(x.size())
#define ALL(x) (x).begin(), (x).end()
#define F0R(i, R) for (int i = (0); i < (R); ++i)
#define FOR(i, L, R) for (int i = (L); i <= (R); ++i)

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string S;
	while (cin >> S) {
		const int N = sz(S);
		for (int i = 3; i < N; i++) {
			set<char> f;
			f.insert(S[i]);
			f.insert(S[i - 1]);
			f.insert(S[i - 2]);
			f.insert(S[i - 3]);
			if (sz(f) == 4) {
				cout << i + 1 << '\n';
				break;
			}
		}
	}

	return 0;
}
