/**
 *    Author: Nachiket Kanore
 *    Created: Sunday 18 December 2022 10:29:36 AM IST
 **/
#include "bits/stdc++.h"
#include <algorithm>
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

const int dx[] = { 1, -1, 0, 0, 0, 0 };
const int dy[] = { 0, 0, -1, 1, 0, 0 };
const int dz[] = { 0, 0, 0, 0, 1, -1 };

const int MX = 100;
vector<array<int, 3>> A;
int vis[MX][MX][MX];

bool inside(int i, int j, int k) {
	return 0 <= i && i < MX && 0 <= j && j < MX && 0 <= k && k < MX;
}

void dfs(int i, int j, int k) {
	if (inside(i, j, k)) {
		if (binary_search(ALL(A), array<int, 3>{ i, j, k })) {
			return;
		}
		if (vis[i][j][k] == 0) {
			vis[i][j][k] = -1;
			F0R(id, 6) {
				int ni = i + dx[id], nj = j + dy[id], nk = k + dz[id];
				dfs(ni, nj, nk);
			}
		}
	}
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int x, y, z;
	char ch;
	while (cin >> x >> ch >> y >> ch >> z) {
		A.push_back({ x, y, z });
	}

	sort(ALL(A));
	see(A);
	int ans = 0;

	dfs(0, 0, 0);

	for (array<int, 3> a : A) {
		F0R(id, 6) {
			a[0] += dx[id];
			a[1] += dy[id];
			a[2] += dz[id];
			if (vis[a[0]][a[1]][a[2]] == -1) {
				++ans;
			}
		}
	}
	ans *= 2;
	cout << ans << '\n';

	return 0;
}
