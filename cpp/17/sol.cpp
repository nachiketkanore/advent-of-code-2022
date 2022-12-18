/**
 *    Author: Nachiket Kanore
 *    Created: Saturday 17 December 2022 10:27:23 AM IST
 **/
#include "bits/stdc++.h"
#include <random>
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

const int MAX_ROW = 4000;
vector<vector<pair<int, int>>> blocks;
set<pair<int, int>> done;
int up[7];

void init() {
	{
		vector<pair<int, int>> block;
		block.push_back({ 0, 2 });
		block.push_back({ 0, 3 });
		block.push_back({ 0, 4 });
		block.push_back({ 0, 5 });
		blocks.push_back(block);
	}
	{
		vector<pair<int, int>> block;
		block.push_back({ 0, 3 });
		block.push_back({ 1, 2 });
		block.push_back({ 1, 3 });
		block.push_back({ 1, 4 });
		block.push_back({ 2, 3 });
		blocks.push_back(block);
	}
	{
		vector<pair<int, int>> block;
		block.push_back({ 0, 4 });
		block.push_back({ 1, 4 });
		block.push_back({ 2, 2 });
		block.push_back({ 2, 3 });
		block.push_back({ 2, 4 });
		blocks.push_back(block);
	}
	{
		vector<pair<int, int>> block;
		block.push_back({ 0, 2 });
		block.push_back({ 1, 2 });
		block.push_back({ 2, 2 });
		block.push_back({ 3, 2 });
		blocks.push_back(block);
	}
	{
		vector<pair<int, int>> block;
		block.push_back({ 0, 2 });
		block.push_back({ 0, 3 });
		block.push_back({ 1, 2 });
		block.push_back({ 1, 3 });
		blocks.push_back(block);
	}
}

bool possible(vector<pair<int, int>> A, int dx, int dy) {
	bool ok = true;
	for (auto [r, c] : A) {
		int i = r + dx, j = c + dy;
		ok &= 0 <= i && i < MAX_ROW;
		ok &= 0 <= j && j < 7;
		ok &= done.count({ i, j }) == 0;
		ok &= done.count({ r, c }) == 0;
	}
	return ok;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string move;
	cin >> move;
	const int N = move.size();
	see(move);

	init();
	int obj_id = 0;
	int high = MAX_ROW;
	int move_id = 0;
	map<set<pair<int, int>>, int> memo;
	F0R(col, 7) up[col] = MAX_ROW;

	FOR(round, 1, 2022) {
		vector<pair<int, int>> curr = blocks[obj_id];
		while (true) {
			bool ok = true;
			for (auto [r, _] : curr) {
				ok &= (high - r) > 4;
			}
			if (ok) {
				for (auto& [r, _] : curr)
					++r;
			} else
				break;
		}
		set<pair<int, int>> upper;
		F0R(col, 7) {
			upper.insert(make_pair(up[col], col));
		}
		see(round);
		for (auto it : upper) {
			see(it);
		}
		if (memo.count(upper)) {
			see("repeated............................................", round);
		} else {
			memo[upper] = round;
		}

		// see(round, curr);
		// FOR(row, MAX_ROW - 30, MAX_ROW - 1) {
		// 	F0R(col, 7) {
		// 		if (find(ALL(curr), make_pair(row, col)) != curr.end()) {
		// 			cout << '@';
		// 		} else {
		// 			cout << (done.count({ row, col }) ? '#' : '.');
		// 		}
		// 	}
		// 	cout << '\n';
		// }
		// see(string(20, '-'));

		// move_down = max(int(0), move_down - 5);

		while (true) {
			int dx = -1, dy = -1;
			if (move[move_id] == '<') {
				dx = 0, dy = -1;
			} else if (move[move_id] == '>') {
				dx = 0, dy = +1;
			} else {
				assert(false);
			}
			move_id = (move_id + 1) % N;
			if (possible(curr, dx, dy)) {
				for (auto& [r, c] : curr)
					r += dx, c += dy;
				// see("right", curr);
			}
			if (possible(curr, +1, 0)) {
				for (auto& [r, c] : curr)
					r += 1, c += 0;
				// see("down", curr);
			} else {
				break;
			}

			// see(round, curr);
			// FOR(row, MAX_ROW - 30, MAX_ROW - 1) {
			// 	F0R(col, 7) {
			// 		if (find(ALL(curr), make_pair(row, col)) != curr.end()) {
			// 			cout << '@';
			// 		} else {
			// 			cout << (done.count({ row, col }) ? '#' : '.');
			// 		}
			// 	}
			// 	cout << '\n';
			// }
			// see(string(20, '-'));
		}
		for (auto [r, c] : curr) {
			assert(!done.count({ r, c }));
			done.insert({ r, c });
			up[c] = min(up[c], r);
			high = min(high, r);
		}
		// for (auto cell : done) {
		// 	see(cell);
		// }
		// see(string(20, '-'));

		obj_id = (obj_id + 1) % 5;
	}

	const int INF = 1e6;
	int mn = INF, mx = -INF;
	for (auto [r, _] : done) {
		mn = min(mn, r);
		mx = max(mx, r);
	}

	int ans = mx - mn + 1;
	see(mn, mx);
	see(ans);

	return 0;
}
