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

map<string, vector<string>> adj;
map<string, int> capacity;

map<pair<pair<string, string>, int64_t>, int> dp[27][27];
int best_so_far = 0;
vector<string> nodes;

int get_id(const string& node) {
	int id = lower_bound(ALL(nodes), node) - nodes.begin();
	assert(id >= 0 && id < sz(nodes));
	return id;
}

int dfs(const string& one, const string& two, int rem_one, int rem_two, int64_t mask) {
	if (rem_one <= 0 && rem_two <= 0) {
		return 0;
	}
	if (dp[rem_one][rem_two].count(make_pair(make_pair(one, two), mask))) {
		return dp[rem_one][rem_two][make_pair(make_pair(one, two), mask)];
	}
	see("checking", one, two, best_so_far);
	int ans = 0;
	int one_cap = capacity[one];
	int one_id = get_id(one);
	bool count_one = mask >> one_id & 1;
	if (!count_one && rem_one - 1 > 0 && one_cap > 0) {
		// open.insert(one);
		int get = (rem_one - 1) * one_cap +
		dfs(one, two, rem_one - 1, rem_two, mask | (1 << one_id));
		ans = max(ans, get);
		// open.erase(one);
	}
	int two_cap = capacity[two];
	int two_id = get_id(two);
	bool count_two = mask >> two_id & 1;
	if (!count_two && rem_two - 1 > 0 && two_cap > 0) {
		// open.insert(two);
		int get = (rem_two - 1) * two_cap +
		dfs(one, two, rem_one, rem_two - 1, mask | (1 << two_id));
		ans = max(ans, get);
		// open.erase(two);
	}
	for (const string& two_nxt : adj[two]) {
		for (const string& one_nxt : adj[one]) {
			if (rem_one - 1 > 0 && rem_two - 1 > 0)
				ans = max(ans, dfs(one_nxt, two_nxt, rem_one - 1, rem_two - 1, mask));
		}
	}

	// int you_cap = capacity[you];
	// int ele_cap = capacity[ele];
	// int open_you = open.count(you) > 0;
	// int open_ele = open.count(ele) > 0;
	// if (!open_you || !open_ele) {
	// 	if (!open_you && you_cap > 0) {
	// 		open.insert(you);
	// 		int get = (rem - 1) * you_cap + dfs(you, ele, rem - 1, open);
	// 		ans = max(ans, get);
	// 		open.erase(you);
	// 	}
	// 	if (!open_ele && ele_cap > 0) {
	// 		open.insert(ele);
	// 		int get = (rem - 1) * ele_cap + dfs(you, ele, rem - 1, open);
	// 		ans = max(ans, get);
	// 		open.erase(ele);
	// 	}
	// } else if (you_cap > 0 || ele_cap > 0) {
	// 	// } else if (true) {
	// 	open.insert(you);
	// 	open.insert(ele);
	// 	int get = (rem - 1) * you_cap + (rem - 1) * ele_cap + dfs(you, ele, rem
	// - 1, open); 	ans = max(ans, get); 	open.erase(you); 	open.erase(ele);
	// 	// open.insert(curr);
	// 	// int get = (rem - 1) * cap + dfs(curr, rem - 1, open);
	// 	// open.erase(curr);
	// 	// ans = max(ans, get);
	// 	// for (const string& nxt : adj[curr]) {
	// 	// 	ans = max(ans, dfs(nxt, time + 1, open));
	// 	// }
	// }

	best_so_far = max(best_so_far, ans);
	see(best_so_far);
	dp[rem_one][rem_two][make_pair(make_pair(one, two), mask)] = ans;

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
		nodes.push_back(u);
		// see(tokens);
	}
	sort(ALL(nodes));

	// for (auto [u, vlist] : adj) {
	// 	see(u, vlist);
	// }

	cout << dfs("AA", "AA", 26, 26, int64_t(0)) << '\n';

	return 0;
}
