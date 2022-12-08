/**
 *    Author: Nachiket Kanore
 *    Created: Thursday 08 December 2022 10:27:59 AM IST
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

	vector<string> mat;
	string S;
	while (cin >> S) {
		mat.push_back(S);
	}

	const int N = mat.size();
	const int M = mat[0].size();

	int ans = 0;
	F0R(i, N) {
		F0R(j, M) {
			if (i == 0 || j == 0 || i == N - 1 || j == M - 1) {
				++ans;
				continue;
			}
			int mx = -1;
			int val = mat[i][j] - '0';
			bool ok = false;
			FOR(id, j + 1, M - 1) mx = max(mx, int(mat[i][id] - '0'));
			ok |= mx < val;
			mx = -1;
			FOR(id, 0, j - 1) mx = max(mx, int(mat[i][id] - '0'));
			ok |= mx < val;
			mx = -1;
			FOR(id, 0, i - 1) mx = max(mx, int(mat[id][j] - '0'));
			ok |= mx < val;
			mx = -1;
			FOR(id, i + 1, N - 1) mx = max(mx, int(mat[id][j] - '0'));
			ok |= mx < val;
			if (ok) {
				++ans;
			}
		}
	}

	cout << ans << '\n';

	return 0;
}
