/**
 *    Author: Nachiket Kanore
 *    Created: Monday 05 December 2022 10:26:55 AM IST
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

	int N;
	cin >> N;
	vector<string> A(N + 1);
	FOR(i, 1, N) {
		cin >> A[i];
	}
	// see(A);
	string ch;
	int cnt, from, to;
	while (cin >> ch >> cnt >> ch >> from >> ch >> to) {
		string put;
		while (cnt--) {
			char get = A[from].back();
			A[from].pop_back();
			// A[to].push_back(get);
			put.push_back(get);
		}
		reverse(ALL(put));
		for (char c : put) {
			A[to].push_back(c);
		}
		// see(A);
	}
	FOR(i, 1, N) {
		cout << A[i].back();
	}
	cout << '\n';

	return 0;
}
