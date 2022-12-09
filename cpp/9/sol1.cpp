/**
 *    Author: Nachiket Kanore
 *    Created: Friday 09 December 2022 10:27:35 AM IST
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

const int MX = 2000;
bool vis[MX][MX];
int hi = 1000, hj = 1000;
int ti = hi, tj = hj;
int ddx[] = { 1, 1, -1, -1 };
int ddy[] = { -1, 1, -1, 1 };

int DX[] = { 0, 0, 1, -1 };
int DY[] = { 1, -1, 0, 0 };

void perform() {
	if (ti == hi && tj == hj) {
		return;
	}
	bool ok = false;
	F0R(id, 4) {
		ok |= ti + DX[id] == hi && tj + DY[id] == hj;
	}
	if (ok)
		return;
	// same row
	if (ti == hi) {
		if (tj < hj) {
			tj++;
		} else if (tj > hj) {
			tj--;
		}
		return;
	}
	// same column
	else if (tj == hj) {
		if (ti < hi) {
			ti++;
		} else if (ti > hi) {
			ti--;
		}
		return;
	}
	// diagonal
	F0R(id, 4) {
		if (ti + ddx[id] == hi && tj + ddy[id] == hj) {
			// TODO ?
			return;
		}
	}
	// which quadrant
	if (hi < ti && hj < tj) {
		ti--, tj--;
	} else if (hi < ti && hj > tj) {
		ti--, tj++;
	} else if (hi > ti && hj > tj) {
		ti++, tj++;
	} else if (hi > ti && hj < tj) {
		ti++, tj--;
	}
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	char dir;
	int t;

	map<char, pair<int, int>> move;
	move['R'] = make_pair(0, +1);
	move['L'] = make_pair(0, -1);
	move['D'] = make_pair(+1, 0);
	move['U'] = make_pair(-1, 0);

	vis[ti][tj] = true;
	while (cin >> dir >> t) {
		auto [dx, dy] = move[dir];
		while (t--) {
			hi += dx, hj += dy;
			perform();
			vis[ti][tj] = true;
		}
	}

	int ans = 0;
	F0R(i, 2000) F0R(j, 2000) {
		ans += vis[i][j];
	}
	cout << ans << '\n';

	return 0;
}
