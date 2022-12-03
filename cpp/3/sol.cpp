/**
 *    Author: Nachiket Kanore
 *    Created: Saturday 03 December 2022 10:29:21 AM IST
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

int score(char ch) {
	if (ch >= 'a' && ch <= 'z') {
		return ch - 'a' + 1;
	}
	return ch - 'A' + 1 + 26;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int ans1 = 0;
	string S;
	vector<string> A;
	while (cin >> S) {
		A.push_back(S);
		map<char, int> fa;
		const int N = S.size();
		F0R(i, sz(S)) {
			if (i < N / 2) {
				fa[S[i]]++;
			} else {
				if (fa[S[i]] > 0) {
					fa[S[i]] = 0;
					ans1 += score(S[i]);
				}
			}
		}
	}
	cout << ans1 << '\n';

	int ans2 = 0;
	for (int i = 0; i < sz(A); i += 3) {
		sort(ALL(A[i]));
		sort(ALL(A[i + 1]));
		sort(ALL(A[i + 2]));
		FOR(ch, 'a', 'z') {
			if (binary_search(ALL(A[i]), ch) && binary_search(ALL(A[i + 1]), ch) &&
			binary_search(ALL(A[i + 2]), ch)) {
				ans2 += score(ch);
			}
		}
		FOR(ch, 'A', 'Z') {
			if (binary_search(ALL(A[i]), ch) && binary_search(ALL(A[i + 1]), ch) &&
			binary_search(ALL(A[i + 2]), ch)) {
				ans2 += score(ch);
			}
		}
	}
	cout << ans2 << '\n';

	return 0;
}
