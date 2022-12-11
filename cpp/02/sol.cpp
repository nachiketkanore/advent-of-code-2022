/**
 *    Author: Nachiket Kanore
 *    Created: Friday 02 December 2022 10:51:20 AM IST
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

int solve_part1(const char A, const char B) {
	int ret = B - 'X' + 1;
	int a = A - 'A', b = B - 'X';

	if (a == b)
		ret += 3;
	else {
		// r p s
		// r p s
		if ((b == 0 && a == 2) || (b == 1 && a == 0) || (b == 2 && a == 1))
			ret += 6;
	}

	return ret;
}

int solve_part2(const char A, const char B) {
	int ret = 0;
	int a = A - 'A', b = B - 'X';
	// r p s
	// r p s

	// draw
	if (B == 'Y') {
		ret += 3;
		ret += a + 1;
	}
	// lose
	else if (B == 'X') {
		ret += 0;
		if (a == 0)
			ret += 3;
		if (a == 1)
			ret += 1;
		if (a == 2)
			ret += 2;
	}
	// win
	else if (B == 'Z') {
		ret += 6;
		if (a == 0)
			ret += 2;
		if (a == 1)
			ret += 3;
		if (a == 2)
			ret += 1;
	}

	return ret;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int ans1 = 0, ans2 = 0;
	string S;
	while (getline(cin, S)) {
		ans1 += solve_part1(S[0], S[2]);
		ans2 += solve_part2(S[0], S[2]);
	}
	cout << ans1 << '\n';
	cout << ans2 << '\n';

	return 0;
}
