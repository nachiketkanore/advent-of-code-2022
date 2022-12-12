/**
 *    Author: Nachiket Kanore
 *    Created: Monday 12 December 2022 10:28:46 AM IST
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

vector<pair<int, int>> g[100000];

void dijkstra(int s, vector<int>& d) {

	d[s] = 0;
	using pii = pair<int, int>;
	priority_queue<pii, vector<pii>, greater<pii>> q;
	q.push({ 0, s });
	while (!q.empty()) {
		int v = q.top().second;
		int d_v = q.top().first;
		q.pop();
		if (d_v != d[v])
			continue;

		for (auto edge : g[v]) {
			int to = edge.first;
			int len = edge.second;

			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				q.push({ d[to], to });
			}
		}
	}
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	vector<string> mat;
	string s;
	int row = 0;
	int si = -1, sj = -1, ei = -1, ej = -1;
	while (cin >> s) {
		mat.push_back(s);
		F0R(j, sz(s)) {
			if (s[j] == 'S') {
				si = row;
				sj = j;
			} else if (s[j] == 'E') {
				ei = row;
				ej = j;
			}
		}
		row++;
	}
	const int N = mat.size();
	const int M = mat[0].size();

	auto node = [&](int i, int j) {
		i++, j++;
		return (i - 1) * M + j;
	};

	mat[si][sj] = 'a';
	mat[ei][ej] = 'z';
	const int dx[] = { 0, 0, 1, -1 };
	const int dy[] = { 1, -1, 0, 0 };
	F0R(i, N) {
		F0R(j, M) {
			F0R(id, 4) {
				int ni = i + dx[id], nj = j + dy[id];
				if (ni >= 0 && ni < N && nj >= 0 && nj < M) {
					int diff = mat[ni][nj] - mat[i][j];
					if (diff <= 1) {
						g[node(i, j)].push_back({ node(ni, nj), 1 });
					}
				}
			}
		}
	}

	vector<int> dist(N * M + 100, 1e9);
	dijkstra(node(si, sj), dist);
	cout << dist[node(ei, ej)] << '\n';

	// Right solution :( messed up the condition
	// int dist[N][M];
	// bool vis[N][M];
	// memset(vis, false, sizeof(vis));
	// F0R(i, N) F0R(j, M) {
	// 	dist[i][j] = 1e9;
	// 	vis[i][j] = false;
	// }
	// dist[si][sj] = 0;
	// mat[si][sj] = 'a';
	// mat[ei][ej] = 'z';
	//
	// const int dx[] = { 0, 0, 1, -1 };
	// const int dy[] = { 1, -1, 0, 0 };
	//
	// queue<pair<int, int>> Q;
	// Q.push({ si, sj });
	// while (!Q.empty()) {
	// 	auto [i, j] = Q.front();
	// 	Q.pop();
	// 	if (vis[i][j])
	// 		continue;
	// 	vis[i][j] = true;
	// 	// see(i, j, mat[i][j]);
	// 	F0R(id, 4) {
	// 		int ni = i + dx[id], nj = j + dy[id];
	// 		if (ni < 0 || ni >= N || nj < 0 || nj >= M)
	// 			continue;
	// 		if (vis[ni][nj])
	// 			continue;
	//
	// 		int diff = mat[ni][nj] - mat[i][j];
	// 		if (0 <= diff && diff <= 1) {
	// 			see(mat[i][j], mat[ni][nj]);
	// 			if (dist[i][j] + 1 <= dist[ni][nj]) {
	// 				dist[ni][nj] = dist[i][j] + 1;
	// 				Q.push({ ni, nj });
	// 			}
	// 		}
	// 	}
	// }
	//
	// // F0R(i, N)
	// // F0R(j, M) cout << (dist[i][j] < 1e9 ? 'x' : '.') << " \n"[j == M - 1];
	//
	// cout << dist[ei][ej] << '\n';
	//
	return 0;
}
