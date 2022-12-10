/**
 *    Author: Nachiket Kanore
 *    Created: Saturday 10 December 2022 10:40:32 AM IST
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

char mat[100][100];

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	F0R(i, 100) F0R(j, 100) mat[i][j] = '?';

	string s;
	int X = 1, cycle = 0;
	int ans = 0;
	int pos = 0;

	auto perform = [&](int cnt, int add = 0) {
		while (cnt--) {
			int row = cycle / 40;
			if (pos == X - 1 || pos == X || pos == X + 1) {
				mat[row][pos] = '#';
			} else {
				mat[row][pos] = '.';
			}
			++cycle;
			pos = (pos + 1) % 40;
		}
		X += add;
	};

	while (cin >> s) {
		if (s == "addx") {
			int add;
			cin >> add;
			perform(2, add);
		} else if (s == "noop") {
			perform(1);
		} else {
			assert(false);
		}
	}

	F0R(i, 6) {
		F0R(j, 40) {
			cout << mat[i][j];
		}
		cout << '\n';
	}

	return 0;
}
