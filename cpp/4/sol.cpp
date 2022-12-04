/**
 *    Author: Nachiket Kanore
 *    Created: Sunday 04 December 2022 10:27:48 AM IST
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

	int l1, r1, l2, r2;
	char ch;
	int ans1 = 0, ans2 = 0;
	while (cin >> l1 >> ch >> r1 >> ch >> l2 >> ch >> r2) {
		if (l1 <= l2 && r2 <= r1)
			++ans1;
		else if (l2 <= l1 && r1 <= r2)
			++ans1;

		if (l1 <= l2 && l2 <= r1)
			++ans2;
		else if (l1 <= r2 && r2 <= r1)
			++ans2;
		else if (l2 <= l1 && l1 <= r2)
			++ans2;
		else if (l2 <= r1 && r1 <= r2)
			++ans2;
	}
	cout << ans1 << '\n';
	cout << ans2 << '\n';

	return 0;
}
