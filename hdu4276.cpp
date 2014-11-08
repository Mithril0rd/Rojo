#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_N = 107;
const int INF = 0x3f3f3f3f;

struct Node {
	int u, v, w, nxt;
	Node () {
		
	}
	Node (int _u, int _v, int _w, int _nxt) {
		u = _u, v = _v, w = _w, nxt = _nxt;
	}
};

int n, T;
int A[MAX_N];
Node E[MAX_N << 1];
int edgecnt, head[MAX_N];

int d[MAX_N], pre[MAX_N];
bool vis[MAX_N];
int dp[MAX_N][MAX_N * 6];

void addedge(int u, int v, int w) {
	E[edgecnt] = Node(u, v, w, head[u]);
	head[u] = edgecnt++;
}

int spfa() {
	memset(d, 0x3f, sizeof d);
	memset(vis, false, sizeof vis);
	memset(pre, 0, sizeof pre);
	queue<int> que;
	que.push(1);
	d[1] = 0;
	vis[1] = true;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		vis[u] = false;
		for (int i = head[u]; ~i; i = E[i].nxt) {
			int v = E[i].v, w = E[i].w;
			if (d[u] + w < d[v]) {
				d[v] = d[u] + w;
				pre[v] = i;
				if (!vis[v]) {
					vis[v] = true;
					que.push(v);
				}
			}
		}
	}
}

void dfs(int u, int fa, int r) {
	for (int i = head[u]; ~i; i = E[i].nxt) {
		int v = E[i].v, w = E[i].w * 2;
		if (v == fa || w > r) continue;
		dfs(v, u, r - w);
		for (int j = r; j >= w; --j) {
			for (int k = 0; k <= j - w; ++k) {
				if (~dp[u][j - w - k] && ~dp[v][k])
					dp[u][j] = max(dp[u][j], dp[u][j - w - k] + dp[v][k]);
			}
		}
	}
}

int main() {
	while (2 == scanf("%d%d", &n, &T)) {
		edgecnt = 0;
		memset(head, -1, sizeof head);
		for (int i = 1; i < n; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addedge(u, v, w);
			addedge(v, u, w);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &A[i]);
		}
		spfa();
		if (d[n] == INF || T < d[n]) puts("Human beings die in pursuit of wealth, and birds die in pursuit of food!");
		else {
			memset(dp, -1, sizeof dp);
			for (int i = 1; i <= n; ++i) dp[i][0] = A[i];
			for (int i = n; i != 1; i = E[pre[i]].u) {
				E[pre[i]].w = E[pre[i] ^ 1].w = 0;
			}
			dfs(1, -1, T - d[n]);
			int ans = 0;
			for (int i = 0; i <= T; ++i) ans = max(ans, dp[1][i]);
			printf("%d\n", ans);
		}
	}
	return 0;
}