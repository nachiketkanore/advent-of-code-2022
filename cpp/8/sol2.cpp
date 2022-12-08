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
				continue;
			}
			int sc = 1;
			int get = 0;
			FOR(id, j + 1, M - 1) {
				if (mat[i][id] >= mat[i][j]) {
					++get;
					break;
				}
				++get;
			}
			sc *= get;
			get = 0;
			for (int id = j - 1; id >= 0; id--) {
				if (mat[i][id] >= mat[i][j]) {
					++get;
					break;
				}
				++get;
			}
			sc *= get;
			get = 0;
			for (int id = i - 1; id >= 0; id--) {
				if (mat[id][j] >= mat[i][j]) {
					++get;
					break;
				}
				++get;
			}
			sc *= get;
			get = 0;
			FOR(id, i + 1, N - 1) {
				if (mat[id][j] >= mat[i][j]) {
					++get;
					break;
				}
				++get;
			}
			sc *= get;
			ans = max(ans, sc);
		}
	}

	cout << ans << '\n';

	return 0;
}
