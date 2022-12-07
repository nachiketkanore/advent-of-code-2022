#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define sz(x) (int)(x.size())
#define ALL(x) (x).begin(), (x).end()
#define F0R(i, R) for (int i = (0); i < (R); ++i)
#define FOR(i, L, R) for (int i = (L); i <= (R); ++i)

map<string, set<string>> dirs, files;
map<string, string> parent;
map<string, int> sizes, dp;
set<string> vis;

int dfs(string curr) {
	if (vis.count(curr)) {
		return dp[curr];
	}
	int ans = 0;
	for (string f : files[curr]) {
		ans += sizes[f];
	}
	for (string dir : dirs[curr]) {
		ans += dfs(dir);
	}

	dp[curr] = ans;
	return ans;
}

int32_t main() {

	string curr = "/";
	set<string> alldirs;
	alldirs.insert("/");

	cout << "OK\n";

	string s;
	while (cin >> s) {
		if (s == "$") {
			string cmd;
			cin >> cmd;
			if (cmd == "cd") {
				string dir_name;
				cin >> dir_name;
				if (dir_name == "/")
					continue;
				if (dir_name == "..") {
					curr = parent[curr];
					continue;
				}
				dirs[curr].insert(dir_name);
				parent[dir_name] = curr;
				curr = dir_name;
			} else if (cmd == "ls") {
				// do nothing?
			} else {
				assert(false);
			}
		} else {
			bool is_num = true;
			for (char ch : s) {
				is_num &= ch >= '0' && ch <= '9';
			}
			if (is_num) {
				int file_size = stoll(s);
				string file_name;
				cin >> file_name;
				files[curr].insert(file_name);
				sizes[file_name] = file_size;
			} else {
				assert(s == "dir");
				string dir_name;
				cin >> dir_name;
				dirs[curr].insert(dir_name);
				alldirs.insert(dir_name);
			}
		}
	}
	//
	// for (auto [dir, fls] : files) {
	// 	cout << dir << " : \n";
	// 	for (string fl : fls) {
	// 		cout << "file -> ";
	// 		cout << "HERE\n";
	// 		cout << fl << " " << sizes[fl] << '\n';
	// 		cout << "HEREnachiket\n";
	// 	}
	// 	for (string dr : dirs[dir]) {
	// 		cout << "dir -> ";
	// 		cout << dr << '\n';
	// 	}
	// }
	//
	cout << "bad..\n";

	dfs("/");

	cout << "good..\n";

	int ans = 0;
	for (string d : alldirs) {
		cout << d << " : size = " << dp[d] << '\n';
		if (dp[d] <= 100000) {
			ans += dp[d];
		}
	}

	cout << ans << '\n';

	return 0;
}
