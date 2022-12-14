/**
 *    Author: Nachiket Kanore
 *    Created: Wednesday 14 December 2022 10:28:19 AM IST
 **/
#include "bits/stdc++.h"
#include <cctype>
#include <cwchar>
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

const int MX = 1000;
int block[MX][MX];

void draw(int cr, int cc, int pr, int pc) {
	assert(cr == pr || cc == pc);
	if (cr == pr) {
		if (cc > pc)
			swap(cc, pc);
		FOR(col, cc, pc) block[cr][col] = true;
		return;
	}
	if (cc == pc) {
		if (cr > pr)
			swap(cr, pr);
		FOR(row, cr, pr) block[row][cc] = true;
		return;
	}
	assert(0);
}

int dx[] = { 1, 1, 1 };
int dy[] = { 0, -1, 1 };

bool inside(int i, int j) {
	return i >= 0 && i < MX && j >= 0 && j < MX;
}

bool comes_to_rest(int si, int sj) {
	while (inside(si, sj)) {
		bool allblocked = true;
		F0R(id, 3) {
			int ni = si + dx[id], nj = sj + dy[id];
			if (!inside(ni, nj))
				continue;
			if (block[ni][nj])
				continue;
			allblocked = false;
			si = ni, sj = nj;
			break;
		}
		if (allblocked) {
			block[si][sj] = -1;
			return true;
		}
		if (si == MX - 1 || sj == 0 || sj == MX - 1)
			return false;
	}
	assert(false);
	return false;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string s;
	int maxrow = 0;
	while (getline(cin, s)) {
		int val = 0;
		bool start = false;
		vector<int> vals;
		F0R(i, sz(s)) {
			if (isdigit(s[i])) {
				val = val * 10 + (s[i] - '0');
				start = true;
			} else {
				if (start) {
					vals.push_back(val);
				}
				val = 0;
				start = false;
			}
		}
		if (start) {
			vals.push_back(val);
		}
		const int N = sz(vals);
		assert(N % 2 == 0);
		for (int i = 3; i < N; i += 2) {
			int cr = vals[i], cc = vals[i - 1];
			int pr = vals[i - 2], pc = vals[i - 3];
			maxrow = max(maxrow, cr);
			maxrow = max(maxrow, pr);
			draw(cr, cc, pr, pc);
		}
	}
	draw(maxrow + 2, 0, maxrow + 2, MX - 1);

	/* FOR(row, 0, 10) {
		FOR(col, 490, 505) {
			if (row == 0 && col == 500) {
				cout << "+";
			} else {
				cout << (block[row][col] ? '#' : '.');
			}
		}
		cout << '\n';
	} */

	int si = 0, sj = 500;
	int ans = 0;
	while (!block[si][sj] && comes_to_rest(si, sj)) {
		++ans;
	}

	int check = 0;
	F0R(i, MX) F0R(j, MX) if (block[i][j] == -1) {
		check += 1;
	}
	see(check, ans);
	cout << ans << '\n';

	return 0;
}
