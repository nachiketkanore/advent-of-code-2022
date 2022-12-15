/**
 *    Author: Nachiket Kanore
 *    Created: Thursday 15 December 2022 10:29:30 AM IST
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

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	map<int, vector<pair<int, int>>> y_ranges;

	auto between = [](int x, int l, int r) { return l <= x && x <= r; };

	int sx, sy, bx, by;
	vector<pair<int, int>> given;
	while (cin >> sx >> sy >> bx >> by) {
		given.push_back({ sx, sy });
		given.push_back({ bx, by });
		int dist = abs(sx - bx) + abs(sy - by);
		// if (sx == 8 && sy == 7)
		// 	see(sx, sy);
		if (between(10, sy - dist, sy + dist))
			for (int y : { 10 }) {
				int remove = abs(y - sy);
				int left = sx - dist + remove;
				int right = sx + dist - remove;
				if (sx == 8 && sy == 7)
					see(y, left, right);
				y_ranges[y].push_back({ left, right });
			}
		if (between(2000000, sy - dist, sy + dist))
			for (int y : { 2000000 }) {
				int remove = abs(y - sy);
				int left = sx - dist + remove;
				int right = sx + dist - remove;
				// if (sx == 8 && sy == 7)
				// 	see(y, left, right);
				y_ranges[y].push_back({ left, right });
			}
		// see(dist, sx - dist, sx + dist);
	}
	sort(ALL(given));
	const int INF = 1e9;
	auto solve = [&](int y) {
		auto& ranges = y_ranges[y];
		see(ranges);
		sort(ALL(ranges));
		int minx = 1e9, maxx = -1e9;
		for (auto [l, r] : ranges) {
			minx = min(minx, l);
			maxx = max(maxx, r);
		}
		see(minx, maxx);
		auto exists = [&](int x) {
			/* int id = lower_bound(ALL(ranges), make_pair(x, -INF)) -
			ranges.begin(); if (id >= 0 && id < sz(ranges)) {
				// auto [l, r] = ranges[id];
				// see("searching", x, " found ", l, r);
				// if (l <= x && x <= r)
				// 	return true;
				for (; id < sz(ranges); id++) {
					int l = ranges[id].first;
					int r = ranges[id].second;
					see(x, l, r);
					if (l <= x && x <= r)
						return true;
				}
			} */
			for (auto [l, r] : ranges) {
				if (l <= x && x <= r) {
					return true;
				}
			}
			return false;
		};
		int ans = 0;
		FOR(x, minx, maxx) {
			if (exists(x) && !binary_search(ALL(given), make_pair(x, y))) {
				see("taking", x, y);
				++ans;
			}
		}

		return ans;
	};

	// cout << solve(10) << '\n';
	cout << solve(2000000) << '\n';

	return 0;
}
