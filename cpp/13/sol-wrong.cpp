/**
 *    Author: Nachiket Kanore
 *    Created: Tuesday 13 December 2022 10:29:52 AM IST
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

bool is_integer(int i, int j, const string& S) {
	bool ok = true;
	FOR(id, i, j) ok &= isdigit(S[id]);
	return ok;
}

bool check_empty(int i, int j, const string& S) {
	assert(S[i] == '[' && S[j] == ']');
	return sz(S) == 2;
}

bool is_list(int i, int j, const string& S) {
	return S[i] == '[' && S[j] == ']';
}

int get_first_value(int i, int j, const string& S) {
	FOR(id, i, j) {
		if (isdigit(S[id]) && id + 1 <= j && isdigit(S[id + 1])) {
			return (S[id] - '0') * 10 + (S[id + 1] - '0');
		}
		if (isdigit(S[id])) {
			return S[id] - '0';
		}
	}
	string temp = S.substr(i, j - i + 1);
	see("**************");
	see(temp);
	see("**************");
	// assert(check_empty(i, j, S));
	return -1;
}
bool ls;

vector<pair<int, int>> get_element_indices(int i, int j, const string& S) {
	vector<pair<int, int>> ret;
	int si = -1, ei = -1;
	int bal = 0;
	for (int id = i + 1; id < j; id++) {
		if (S[id] == '[') {
			if (si == -1)
				si = id;
			bal += 1;
		} else if (S[id] == ']') {
			ei = id;
			bal -= 1;
		}
		if (bal == 0 && ~si && ~ei) {
			ret.push_back({ si, ei });
			si = ei = -1;
		}
		// see(bal, S[id]);
		if (bal == 0 && isdigit(S[id])) {
			// handle '10' in S, there can be 10 in list
			if (S[id] == '1' && id + 1 < j && S[id + 1] == '0') {
				ret.push_back({ id, id + 1 });
				id++;
			} else {
				ret.push_back({ id, id });
			}
		}
	}
	return ret;
}

int solve(int si, int sj, int ti, int tj, const string& S, const string& T) {
	if (si > sj || ti > tj)
		return false;
	const int N = S.size();
	const int M = T.size();
	vector<pair<int, int>> indS = get_element_indices(si, sj, S);
	vector<pair<int, int>> indT = get_element_indices(ti, tj, T);
	// see(S, indS);
	// see(T, indT);
	// return 0;
	bool greater_found = false;
	F0R(i, sz(indS)) {
		if (i >= sz(indT)) {
			greater_found = true;
			break;
		}
		auto [xi, xj] = indS[i];
		auto [yi, yj] = indT[i];

		if (is_integer(xi, xj, S) && is_integer(yi, yj, T)) {
			int A = stoll(S.substr(xi, xj - xi + 1));
			int B = stoll(T.substr(yi, yj - yi + 1));
			// see(S, T);
			// see("HERE", S.substr(xi, xj - xi + 1), T.substr(yi, yj - yi +
			// 1)); see("checking", A, B);
			greater_found |= A > B;
			ls |= A < B;
		} else if (is_list(xi, xj, S) && is_list(yi, yj, T)) {
			// see("HERE", S.substr(xi, xj - xi + 1), T.substr(yi, yj - yi + 1));
			bool eS = check_empty(xi, xj, S);
			bool eT = check_empty(yi, yj, T);
			if (eS && eT)
				continue;
			if (eS && !eT)
				continue;
			if (!eS && eT) {
				greater_found = true;
				continue;
			}

			greater_found |= solve(xi, xj, yi, yj, S, T);
		} else {
			// need to be compared with first value in other
			if (is_integer(xi, xj, S)) {
				int A = stoll(S.substr(xi, xj - xi + 1));
				int B = get_first_value(yi, yj, T);
				// if (A == 10 || B == 10) {
				// 	see("found");
				// }
				if (~B) {
					ls |= A < B;
					greater_found |= A > B;
				} else {
					greater_found = true;
				}
				// see("comparing", A, B);
			} else if (is_integer(yi, yj, T)) {
				int A = get_first_value(xi, xj, S);
				int B = stoll(T.substr(yi, yj - yi + 1));
				if (A == 10 || B == 10) {
					see("found");
				}
				if (~A) {
					ls |= A < B;
					greater_found |= A > B;
				} else {
					ls |= 1;
					// nothing?
				}
				// see("comparing", A, B);
			}
		}
	}
	return greater_found;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	// auto x = get_element_indices(0, 5, "[[[]]]");
	// see(x);
	// return 0;

	string S, T;
	int ans = 0, idx = 1;
	while (cin >> S >> T) {
		::ls = false;
		bool ok = !solve(0, sz(S) - 1, 0, sz(T) - 1, S, T);
		if (::ls) {
			see(S, T);
			ans += idx;
		}
		idx += 1;
	}
	cout << ans << '\n';
	// Observations:
	// every [ denotes starting of some list

	// [[1],[2,3,4]], [[1],4]
	// [1], [1]
	// [2,3,4], 4
	// [2,3,4], [4]
	// 2, 4 <- good
	// 3, null
	// 4, null
	// [[],5,[0]],[7],[[2,7,[7]],[[8,3],[8,9,8],6,[]],[1,3,[0,4,10],[6,1,9]],8],[[3,0]]
	// [5,[],10]
	// [[],5,[0]]
	// [5]
	// [], 5
	// [], [5]
	//
	return 0;
}
