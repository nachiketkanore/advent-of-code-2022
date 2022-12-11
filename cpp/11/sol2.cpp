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

struct Item {
	int val;
	int valmod[24];
	Item(int val) : val(val) {
		FOR(i, 1, 24) valmod[i] = val % i;
	}
	void multilply(int with) {
		FOR(i, 1, 24) valmod[i] = (valmod[i] * with) % i;
	}
	void add(int with) {
		FOR(i, 1, 24) valmod[i] = (valmod[i] + with) % i;
	}
	void selfadd() {
		FOR(i, 1, 24) valmod[i] = (valmod[i] + valmod[i]) % i;
	}
	void selfmultipy() {
		FOR(i, 1, 24) valmod[i] = (valmod[i] * valmod[i]) % i;
	}
	int get_mod_with(int mod) {
		assert(mod < 24);
		return valmod[mod];
	}
};

const int MX = 20;
vector<Item> items[MX];
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
			items[id].push_back(Item(s));
		}
		string one, op, two;
		cin >> one >> op >> two;
		assert(one == "old");
		operation[id] = make_pair(op[0], two);
		cin >> divi[id] >> ok[id] >> notok[id];
	}

	auto perform = [](char op, string two, Item& old) {
		if (op == '+') {
			if (two == "old") {
				old.selfadd();
				return;
			}
			old.add(stoll(two));
			return;
		} else if (op == '*') {
			if (two == "old") {
				old.selfmultipy();
				return;
			}
			old.multilply(stoll(two));
			return;
		}
		assert(false);
	};

	FOR(round, 1, 10000) {
		F0R(id, N) {
			for (Item& item : items[id]) {
				cnt[id]++;
				perform(operation[id].first, operation[id].second, item);
				if (item.get_mod_with(divi[id]) == 0) {
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
