/**
 *    Author: Nachiket Kanore
 *    Created: Thursday 01 December 2022 12:54:41 PM IST
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
	int ans1 = 0, curr_sum = 0;
	vector<int> sums;
	while (getline(cin, S)) {
		bool has_digit = false;
		for (char ch : S) {
			has_digit |= ch >= '0' && ch <= '9';
		}
		if (has_digit) {
			int val = stoll(S);
			curr_sum += val;
			ans1 = max(ans1, curr_sum);
		} else {
			sums.push_back(curr_sum);
			curr_sum = 0;
		}
	}

	if (curr_sum > 0) {
		sums.push_back(curr_sum);
	}

	cout << ans1 << '\n';

	sort(ALL(sums));
	reverse(ALL(sums));

	int ans2 = sums[0] + sums[1] + sums[2];

	cout << ans2 << '\n';

	return 0;
}
