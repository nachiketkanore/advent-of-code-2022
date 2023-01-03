/**
 *    Author: Nachiket Kanore
 *    Created: Tuesday 03 January 2023 06:55:17 PM IST
 **/
#include "bits/stdc++.h"
#include <cctype>
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

int get_total() {
	int tot = 0;
	string s;
	while (cin >> s) {
		reverse(ALL(s));
		int five = 1;
		for (char ch : s) {
			if (isdigit(ch)) {
				tot += (ch - '0') * five;
			} else {
				if (ch == '=') {
					tot += (-2) * five;
				} else if (ch == '-') {
					tot += (-1) * five;
				} else {
					assert(false);
				}
			}
			five *= 5;
		}
	}
	return tot;
}
int N, MAX;
const int INF = 5e16;

char decode(int c) {
	if (c >= 0 && c <= 2)
		return c + '0';
	if (c == -1)
		return '-';
	if (c == -2)
		return '=';
	assert(0);
}

unordered_map<int, bool> dp[25];

bool go(int five, int val, string c, int fid = 0) {
	if (val == N) {
		// reverse(ALL(c));
		see(c);
		exit(0);
		return true;
	}
	see(val);
	if (dp[fid].count(val))
		return dp[fid][val];
	if (val < -MAX || val > MAX)
		return false;
	if (five > INF || five == 0)
		return false;
	bool found = false;
	for (int coeff : { 1, 2, 0, -1, -2 }) {
		found |= go(five / 5, val - coeff * five, c + decode(coeff), fid + 1);
		if (found)
			break;
	}
	dp[fid][val] = found;
	return found;
}

string ans;

/* void trace(int five, int val) {
	if (val == 0)
		return;
	if (val < -MAX)
		assert(false);
	if (val > MAX)
		assert(false);
	if (five > INF)
		return;
	for (int coeff : { 1, 2, 0, -1, -2 }) {
		if (go(five * 5, val + coeff * five)) {
			if (coeff == 0 || coeff == 1 || coeff == 2)
				ans += (char)(coeff + '0');
			else if (coeff == -1)
				ans += '-';
			else if (coeff == -2)
				ans += '=';

			return trace(five * 5, val + coeff * five);
		}
	}
	assert(0);
} */

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	/*
	 * 0*5^0 + -2*5^1 + 1*5^2 + -1*5^3 + -2*5^4 + 2*5^5
	 * 2=-1=0
	 *
	 * */

	N = get_total();
	MAX = 25 * N;
	see(N);
	string c;
	int five = 1;
	while (five < N)
		five *= 5;
	go(five, 0, c);

	return 0;
}
