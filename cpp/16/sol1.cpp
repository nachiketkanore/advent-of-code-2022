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

#define int int64_t
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

map<string, vector<string>> adj;
map<string, int> capacity;

map<pair<string, set<string>>, int> dp[31];
int best_so_far = 0;

int dfs(const string& curr, int rem, set<string>& open) {
	if (rem <= 0) {
		return 0;
	}
	if (dp[rem].count(make_pair(curr, open))) {
		return dp[rem][make_pair(curr, open)];
	}
	// see("checking", curr);
	int ans = 0;
	for (const string& nxt : adj[curr]) {
		ans = max(ans, dfs(nxt, rem - 1, open));
	}
	int cap = capacity[curr];
	if (open.count(curr)) {
	} else if (cap > 0) {
		open.insert(curr);
		int get = (rem - 1) * cap + dfs(curr, rem - 1, open);
		open.erase(curr);
		ans = max(ans, get);
		// for (const string& nxt : adj[curr]) {
		// 	ans = max(ans, dfs(nxt, time + 1, open));
		// }
	}

	see(best_so_far);
	best_so_far = max(best_so_far, ans);
	dp[rem][make_pair(curr, open)] = ans;

	return ans;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string s;
	while (getline(cin, s)) {
		vector<string> tokens = parse(s);
		int w = stoll(tokens[1]);
		string u = tokens[0];
		capacity[u] = w;
		for (int i = 2; i < sz(tokens); i++) {
			adj[u].push_back(tokens[i]);
		}
		// see(tokens);
	}

	// for (auto [u, vlist] : adj) {
	// 	see(u, vlist);
	// }

	set<string> open;
	cout << dfs("AA", 30, open) << '\n';

	return 0;
}
