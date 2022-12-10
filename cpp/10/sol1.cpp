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

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string s;
	int X = 1, cycle = 0;
	int ans = 0;

	auto perform = [&](int cnt, int add = 0) {
		while (cnt--) {
			++cycle;
			if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 ||
			cycle == 180 || cycle == 220) {
				ans += cycle * X;
			}
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

	cout << ans << '\n';

	return 0;
}
