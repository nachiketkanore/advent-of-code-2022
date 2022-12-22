/**
 *    Author: Nachiket Kanore
 *    Created: Wednesday 21 December 2022 11:53:52 AM IST
 **/
#include "bits/stdc++.h"
#include <type_traits>
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

map<string, vector<string>> A;

bool is_number(const string& S) {
	bool ok = true;
	assert(sz(S));
	for (char ch : S) {
		ok &= ch >= '0' && ch <= '9';
	}
	return ok;
}

int dfs(const string& S) {
	vector<string> V = A[S];
	if (sz(V) == 1) {
		string val = V[0];
		assert(is_number(val));
		return stoll(val);
	}
	string L = V[0], R = V[2];
	char op = V[1][0];
	int left = dfs(L), right = dfs(R);
	if (op == '+') {
		return left + right;
	} else if (op == '-') {
		return left - right;
	} else if (op == '*') {
		return left * right;
	} else if (op == '/') {
		return left / right;
	}
	assert(false);
	return -1;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string u;
	while (cin >> u) {
		u.pop_back();
		string one;
		cin >> one;

		if (is_number(one)) {
			A[u].push_back(one);
			see(u, one);
		} else {
			string op, two;
			cin >> op >> two;
			A[u].push_back(one);
			A[u].push_back(op);
			A[u].push_back(two);
			see(u, one, op, two);
		}
	}
	cout << dfs("root") << '\n';
	return 0;
}
