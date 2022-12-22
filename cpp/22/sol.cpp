/**
 *    Author: Nachiket Kanore
 *    Created: Thursday 22 December 2022 11:47:43 AM IST
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

vector<string> mat;
string instructions;
int N, M;

void init() {
	string s;
	while (getline(cin, s)) {
		if (sz(s)) {
			mat.push_back(s);
		}
	}

	instructions = mat.back();
	mat.pop_back();
	N = sz(mat);

	for (string row : mat) {
		M = max(M, sz(row));
	}
	for (string& row : mat) {
		while (sz(row) != M) {
			row.push_back(' ');
		}
	}
	for (const string& row : mat) {
		assert(sz(row) == M);
	}
	see(instructions);
	see(N, M);
}

pair<int, int> get_starting_position() {
	F0R(j, M) {
		if (mat[0][j] == '.') {
			return make_pair(0, j);
		} else if (mat[0][j] == '#') {
			assert(false);
		}
	}
	assert(false);
}

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	init();

	pair<int, int> start = get_starting_position();
	int ci = start.first, cj = start.second;
	int dir_id = 0;

	auto inside = [&](
				  int i, int j) { return i >= 0 && i < N && j >= 0 && j < M; };

	auto proceed_forward = [&]() {
		assert(mat[ci][cj] == '.');
		int ni = ci, nj = cj;
		while (true) {
			ni = (ni + dx[dir_id] + N) % N;
			nj = (nj + dy[dir_id] + M) % M;
			assert(inside(ni, nj));
			if (mat[ni][nj] == '.') {
				ci = ni, cj = nj;
				break;
			}
			if (mat[ni][nj] == '#') {
				break;
			}
		}
		/* if (inside(ni, nj)) {
			if (mat[ni][nj] == '.') {
				ci = ni, cj = nj;
			} else if (mat[ni][nj] == ' ') {

			}
		} */
	};

	int move_iter = 0;
	for (char ch : instructions) {
		assert(mat[ci][cj] == '.');
		if (isdigit(ch)) {
			move_iter = move_iter * 10 + (ch - '0');
		} else {
			F0R(rep, move_iter) {
				proceed_forward();
				assert(mat[ci][cj] == '.');
			}
			move_iter = 0;
			if (ch == 'L') {
				dir_id = (dir_id - 1 + 4) % 4;
			} else if (ch == 'R') {
				dir_id = (dir_id + 1) % 4;
			} else {
				assert(false);
			}
		}
	}

	F0R(rep, move_iter) {
		proceed_forward();
		assert(mat[ci][cj] == '.');
	}

	ci++, cj++;
	see(ci, cj, dir_id);
	int ans = 1000 * ci + 4 * cj + dir_id;
	see(ans);

	return 0;
}
