/**
 *    Author: Nachiket Kanore
 *    Created: Wednesday 07 December 2022 10:27:12 AM IST
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

map<string, int> sizes;
set<string> files;

struct node {
	bool leaf;
	string name;
	int size;
	node(string namee, int sizee, bool leaff) {
		this->name = namee;
		this->size = sizee;
		this->leaf = leaff;
		sizes[name] = sizee;
		if (leaff) {
			files.insert(name);
		}
	}
};

map<string, vector<node>> adj;
map<string, string> parent;

set<string> vis;

void dfs(string curr) {
	// int ans = sizes[curr];
	if (vis.count(curr))
		return;
	vis.insert(curr);
	for (node v : adj[curr]) {
		if (v.name != curr) {
			dfs(v.name);
			sizes[curr] += sizes[v.name];
		}
	}
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string curr = "root";
	adj[curr].push_back(node("/", 0, false));
	parent[curr] = curr;
	parent["/"] = "/";
	string S;
	while (cin >> S) {
		if (S[0] == '$') {
			string cmd;
			cin >> cmd;
			if (cmd == "ls") {
				// see(S, cmd);
			} else if (cmd == "cd") {
				string loc;
				cin >> loc;
				if (loc == "..") {
					// assert(parent.count(loc));
					curr = parent[loc];
				} else {
					curr = loc;
				}
				// see(S, cmd, loc);
			} else
				throw;
		} else {
			if ('0' <= S[0] && S[0] <= '9') {
				for (char ch : S) {
					assert(ch >= '0' && ch <= '9');
				}
				int ss = stoll(S);
				string file_name;
				cin >> file_name;
				adj[curr].push_back(node(file_name, ss, true));
				parent[file_name] = curr;
			} else if (S == "dir") {
				string dir_name;
				cin >> dir_name;
				adj[curr].push_back(node(dir_name, 0, false));
				parent[dir_name] = curr;
			} else
				throw;
		}
	}
	//
	// for (auto [node, x] : adj) {
	// 	see(node);
	// 	for (auto y : x) {
	// 		see(y.name);
	// 	}
	// }
	//
	dfs("/");

	int ans = 0;
	for (auto [u, s] : sizes) {
		// see(u, s);
		if (!files.count(u)) {
			if (s < 100000) {
				see(u, s);
				ans += s;
			}
		}
	}

	cout << ans << '\n';

	return 0;
}
