/**
 *    Author: Nachiket Kanore
 *    Created: Sunday 11 December 2022 10:23:25 AM IST
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

const int MX = 20;
vector<int> items[MX];
int ok[MX], notok[MX], divi[MX], cnt[MX];
pair<char, string> operation[MX];

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int id;
	int N;
	while (cin >> id) {
		int cnt;
		cin >> cnt;
		N = max(N, id + 1);
		F0R(i, cnt) {
			int s;
			cin >> s;
			items[id].push_back(s);
		}
		string one, op, two;
		cin >> one >> op >> two;
		assert(one == "old");
		operation[id] = make_pair(op[0], two);
		cin >> divi[id] >> ok[id] >> notok[id];
	}

	auto perform = [](char op, string two, int old) {
		if (op == '+') {
			if (two == "old") {
				return 1ll * old + old;
			}
			return old + stoll(two);
		} else if (op == '*') {
			if (two == "old") {
				return 1ll * old * old;
			}
			return old * stoll(two);
		}
		assert(false);
		return -1ll;
	};

	FOR(round, 1, 20) {
		F0R(id, N) {
			for (int item : items[id]) {
				cnt[id]++;
				item = perform(operation[id].first, operation[id].second, item) / 3;
				if (item % divi[id] == 0) {
					items[ok[id]].push_back(item);
				} else {
					items[notok[id]].push_back(item);
				}
			}
			items[id].clear();
		}
	}
	sort(cnt, cnt + MX);
	reverse(cnt, cnt + MX);
	cout << cnt[0] * cnt[1] << '\n';

	return 0;
}
