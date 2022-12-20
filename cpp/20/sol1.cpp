/**
 *    Author: Nachiket Kanore
 *    Created: Tuesday 20 December 2022 11:58:53 AM IST
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

vector<pair<int, int>> input() {
	int val, idx = 1;
	vector<pair<int, int>> A;
	bool found = false;
	while (cin >> val) {
		if (val == 0) {
			found = true;
		}
		A.push_back({ val, idx++ });
	}
	assert(found);
	return A;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	vector<pair<int, int>> A = input();
	const int N = A.size();

	FOR(id, 1, N) {
		int i = -1;
		F0R(j, N) if (A[j].second == id) {
			i = j;
			break;
		}
		assert(~i);
		// see(A[i].first);
		int cnt = abs(A[i].first);
		while (cnt--) {
			int j = (A[i].first > 0 ? i + 1 : i - 1);
			j = (j + N) % N;
			swap(A[i], A[j]);
			swap(i, j);
		}
		// see(A);
	}

	int zero = -1;
	F0R(i, N) if (A[i].first == 0) {
		zero = i;
		break;
	}
	// zero = (zero + 1) % N;
	assert(~zero);
	int ans = A[(zero + 1000) % N].first + A[(zero + 2000) % N].first +
	A[(zero + 3000) % N].first;
	see(ans);

	return 0;
}
