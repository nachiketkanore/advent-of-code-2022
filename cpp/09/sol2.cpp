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
int ddx[] = { 1, 1, -1, -1 };
int ddy[] = { -1, 1, -1, 1 };

int DX[] = { 0, 0, 1, -1 };
int DY[] = { 1, -1, 0, 0 };

pair<int, int> perform(int hi, int hj, int ti, int tj) {
	if (ti == hi && tj == hj) {
		return { ti, tj };
	}
	bool ok = false;
	F0R(id, 4) {
		ok |= ti + DX[id] == hi && tj + DY[id] == hj;
		ok |= ti + ddx[id] == hi && tj + ddy[id] == hj;
	}
	if (ok)
		return { ti, tj };
	// same row
	if (ti == hi) {
		if (tj < hj) {
			tj++;
		} else if (tj > hj) {
			tj--;
		}
		return { ti, tj };
	}
	// same column
	else if (tj == hj) {
		if (ti < hi) {
			ti++;
		} else if (ti > hi) {
			ti--;
		}
		return { ti, tj };
	}
	// diagonal
	F0R(id, 4) {
		if (ti + ddx[id] == hi && tj + ddy[id] == hj) {
			// TODO ?
			return { ti, tj };
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
	return { ti, tj };
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	char dir;
	int t;
	vector<pair<int, int>> tail;
	F0R(rep, 10) tail.push_back({ 1000, 1000 });

	map<char, pair<int, int>> move;
	move['R'] = make_pair(0, +1);
	move['L'] = make_pair(0, -1);
	move['D'] = make_pair(+1, 0);
	move['U'] = make_pair(-1, 0);

	vis[tail[0].first][tail[0].second] = true;
	while (cin >> dir >> t) {
		auto [dx, dy] = move[dir];
		while (t--) {
			tail.back().first += dx;
			tail.back().second += dy;
			for (int i = sz(tail) - 2; i >= 0; i--) {
				tail[i] = perform(tail[i + 1].first, tail[i + 1].second,
				tail[i].first, tail[i].second);
			}
			vis[tail[0].first][tail[0].second] = true;
		}
	}
	int ans = 0;
	F0R(i, 2000) F0R(j, 2000) {
		ans += vis[i][j];
	}
	cout << ans << '\n';

	return 0;
}
