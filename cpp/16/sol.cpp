/**
 *    Author: Nachiket Kanore
 *    Created: Friday 16 December 2022 10:27:53 AM IST
 **/
#include "bits/stdc++.h"
using namespace std;

#ifdef DEBUG
#include "debug.h"
#else
#define see(...) ;
#endif

#define sz(x) (int)(x.size())
#define ALL(x) (x).begin(), (x).end()
#define F0R(i, R) for (int i = (0); i < (R); ++i)
#define FOR(i, L, R) for (int i = (L); i <= (R); ++i)

vector<string> parse(const string& S) {
	const int N = S.size();
	vector<string> ret;
	string curr;
	for (char ch : S) {
		if (ch == ' ') {
			if (sz(curr) > 0) {
				ret.push_back(curr);
			}
			curr.clear();
		} else {
			curr.push_back(ch);
		}
	}
	if (sz(curr) > 0) {
		ret.push_back(curr);
	}
	return ret;
}

const int INF = 1e7;
map<string, vector<string>> neigh;
vector<int> adj[60];
int w[60], dist[60][60];
map<string, int> capacity;
vector<int> special;

vector<string> nodes;

int get_id(const string& node) {
	int id = lower_bound(ALL(nodes), node) - nodes.begin();
	assert(id >= 0 && id < sz(nodes));
	return id;
}

int get_special_id(int node) {
	F0R(i, sz(special)) if (special[i] == node) return i;
	assert(false);
}

int go(int one, int two, int rem, int special_mask) {
	if (rem < 0)
		return -INF;
	if (rem == 0)
		return 0;

	see(one, two, rem);

	// one -> none, some special node unset in special_mask
	// two -> tone, some special node unset in special_mask

	// time req = dist[one][none]
	// time req = dist[one][tone]

	int one_id = get_special_id(one);
	int two_id = get_special_id(two);
	// int here = (rem - 1) * (w[one] + (one == two ? 0 : w[two]));
	int ans = 0;

	F0R(i, sz(special)) if (special[i] != one) {
		F0R(j, sz(special)) if (special[j] != two) {
			int ni = special[i], nj = special[j];
			int treq = max(dist[one][ni], dist[two][nj]);
			if (rem - treq < 0 || treq == 0)
				continue;
			int get = 0;
			if ((special_mask >> i & 1) == 0) {
				int val = (rem - dist[one][ni] - 1) * w[ni];
				see("taking", w[ni], val);
				get += val;
			}
			if ((special_mask >> j & 1) == 0) {
				int val = (rem - dist[two][nj] - 1) * w[nj];
				see("taking", w[nj], val);
				get += val;
			}
			get += go(ni, nj, rem - treq, special_mask | (1 << i) | (1 << j));
			ans = max(ans, get);
		}
	}

	see(one, two, ans);

	return ans;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string s;
	int n = 0;
	while (getline(cin, s)) {
		vector<string> tokens = parse(s);
		int w = stoll(tokens[1]);
		string u = tokens[0];
		capacity[u] = w;
		for (int i = 2; i < sz(tokens); i++) {
			neigh[u].push_back(tokens[i]);
		}
		nodes.push_back(u);
	}
	sort(ALL(nodes));

	F0R(i, 60) F0R(j, 60) dist[i][j] = (i != j ? INF : 0);
	for (auto [u, vlist] : neigh) {
		int uid = get_id(u);
		n = max(n, uid + 1);
		w[uid] = capacity[u];
		if (w[uid] > 0) {
			special.push_back(uid);
		}
		for (auto v : vlist) {
			int vid = get_id(v);
			n = max(n, vid + 1);
			dist[uid][vid] = 1;
			adj[uid].push_back(vid);
		}
	}
	special.push_back(0);
	sort(ALL(special));
	for (int spl : special) {
		see(spl, w[spl]);
	}
	n = 60;
	F0R(k, n)
	F0R(u, n) F0R(v, n) dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
	see(dist[get_id("AA")][get_id("HH")]);
	// return 0;

	assert(get_id("AA") == 0);
	// we always jump from one special node to other
	int ans = go(0, 0, 26, 1 << 0);
	cout << ans << '\n';

	/* for (auto [u, vlist] : adj) {
		vector<int> nei;
		for (auto v : vlist) {
			nei.push_back(get_id(v));
		}
	} */

	return 0;
}
