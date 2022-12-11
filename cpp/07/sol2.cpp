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

struct node {
	node* up;
	vector<node*> children;
	string name;
	int val;
	bool is_dir = false;
	node(string _name, int _val, bool _is_dir, node* _up = nullptr) {
		up = _up;
		name = _name;
		val = _val;
		is_dir = _is_dir;
	}
};

int tot = 0;
vector<int> sizes;

int dfs(node* curr) {
	int ans = curr->val;
	for (node* child : curr->children) {
		ans += dfs(child);
	}
	// see(curr->name, ans);
	if (curr->is_dir && ans <= 100000) {
		tot += ans;
	}
	if (curr->is_dir) {
		sizes.push_back(ans);
	}
	return ans;
}

vector<int> g[10000];

int32_t main() {

	string curr;
	node* head = new node("/", 0, true);
	node* start = head;

	string s;
	while (cin >> s) {
		if (s == "$") {
			string cmd;
			cin >> cmd;
			if (cmd == "cd") {
				string dir_name;
				cin >> dir_name;
				if (dir_name == "/") {
					// TODO: only once called?
					continue;
				}
				if (dir_name == "..") {
					head = head->up;
					continue;
				}
				bool found = false;
				for (node* child : head->children) {
					if (child->name == dir_name) {
						head = child;
						found = true;
						break;
					}
				}
				assert(found);
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
				head->children.push_back(new node(file_name, file_size, false));
			} else {
				assert(s == "dir");
				string dir_name;
				cin >> dir_name;
				head->children.push_back(new node(dir_name, 0, true, head));
			}
		}
	}

	int all = dfs(start);

	int unused = 70000000 - all;
	int req = 30000000 - unused;
	see(req);
	int ans = 1e12;

	for (int ss : sizes) {
		see(ss);
		if (ss >= req) {
			ans = min(ans, ss);
		}
	}
	cout << ans << '\n';
	return 0;
}
