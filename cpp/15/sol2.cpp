/**
 *    Author: Nachiket Kanore
 *    Created: Thursday 15 December 2022 10:29:30 AM IST
 **/
#include "bits/stdc++.h"
#include <algorithm>
#include <ios>
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

vector<vector<int>> merge(vector<vector<int>>& intervals) {
	sort(intervals.begin(), intervals.end());

	vector<vector<int>> merged;
	for (auto interval : intervals) {
		// if the list of merged intervals is empty or if the current
		// interval does not overlap with the previous, simply append it.
		if (merged.empty() || merged.back()[1] < interval[0]) {
			merged.push_back(interval);
		}
		// otherwise, there is overlap, so we merge the current and previous
		// intervals.
		else {
			merged.back()[1] = max(merged.back()[1], interval[1]);
		}
	}
	return merged;
}

const int MAX = 4000000;
vector<pair<int, int>> y_ranges[MAX + 1];

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	auto between = [](int x, int l, int r) { return l <= x && x <= r; };

	int sx, sy, bx, by;
	int idx = 0;
	vector<pair<int, int>> given;
	while (cin >> sx >> sy >> bx >> by) {
		given.push_back({ sx, sy });
		given.push_back({ bx, by });
		int dist = abs(sx - bx) + abs(sy - by);
		int L = max(int(0), sy - dist);
		int R = min(int(MAX), sy + dist);
		FOR(y, L, R) {
			int remove = abs(y - sy);
			int left = sx - dist + remove;
			int right = sx + dist - remove;
			left = max(int(0), left);
			right = min(MAX, right);
			// if (sx == 8 && sy == 7)
			// 	see(y, left, right);
			y_ranges[y].push_back({ left, right });
		}

		idx += 1;
		see("insertions done", idx);
	}

	see("insertions done");

	FOR(y, 0, MAX) {
		see("checking", y);
		const auto& ranges = y_ranges[y];
		vector<vector<int>> list;
		for (auto [l, r] : ranges) {
			vector<int> add;
			add.push_back(l);
			add.push_back(r);
			list.push_back(add);
		}
		auto intersection = merge(list);
		const int N = sz(intersection);
		for (int i = 1; i < N; i++) {
			int l1 = intersection[i - 1][0], r1 = intersection[i - 1][1];
			int l2 = intersection[i][0], r2 = intersection[i][1];
			if (r1 + 2 == l2) {
				int x = r1 + 1;
				see(x, y);
				int ans = x * 4000000 + y;
				cout << ans << '\n';
				return 0;
			}
		}
	}

	// cout << solve(10) << '\n';
	// cout << solve(2000000) << '\n';

	return 0;
}
