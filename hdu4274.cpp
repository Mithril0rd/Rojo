#include <cstdio>
#include <cstring>

const int MAX_N = 10007;

struct Node {
	int v, nxt;
	Node () {
		
	}
	Node (int _v, int _nxt) {
		v = _v, nxt = _nxt;
	}
};

int n;
int d[MAX_N];
Node E[MAX_N << 1];
int edgecnt, head[MAX_N];
int cost[MAX_N], deng[MAX_N], xiao[MAX_N], da[MAX_N];
bool f;

void addedge(int u, int v) {
	E[edgecnt] = Node(v, head[u]);
	head[u] = edgecnt++;
}

void dfs(int u, int fa) {
	if (~deng[u] && ~da[u] && deng[u] < da[u] || ~deng[u] && ~xiao[u] && deng[u] > xiao[u] || 
	~xiao[u] && ~da[u] && xiao[u] < da[u]) {
		f = false;
		return ;
	}
	cost[u] = 1;
	for (int i = head[u]; ~i; i = E[i].nxt) {
		int v = E[i].v;
		if (v == fa) continue;
		dfs(v, u);
		cost[u] += cost[v];
	}
	if (~deng[u]) {
		if (cost[u] <= deng[u]) {
			cost[u] = deng[u];
		} else {
			f = false;
			return ;
		}
	} 
	if (~da[u]) {
		if (cost[u] < da[u]) {
			cost[u] = da[u];
		} 
	}
	if (~xiao[u]) {
		if (cost[u] > xiao[u]) {
			f = false;
			return ;
		}
	}
}

int main() {
	while (1 == scanf("%d", &n)) {
		edgecnt = 0;
		memset(head, -1, sizeof head);
		for (int u = 2; u <= n; ++u) {
			int v;
			scanf("%d", &v);
			addedge(u, v);
			addedge(v, u);
		}
		int q;
		memset(deng, -1, sizeof deng);
		memset(xiao, -1, sizeof xiao);
		memset(da, -1, sizeof da);
		memset(cost, 0, sizeof cost);
		scanf("%d", &q);
		for (int i = 0; i < q; ++i) {
			int u, w;
			char str[2];
			scanf("%d%s%d", &u, str, &w);
			if (str[0] == '>') da[u] = w + 1;
			else if (str[0] == '<') xiao[u] = w - 1;
			else deng[u] = w;
		}
		f = true;
		dfs(1, -1);
		if (f) puts("True");
		else puts("Lie");
	}
	return 0;
}