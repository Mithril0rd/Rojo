#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_V = 60007;
const int MAX_N = 400007;
const int INF = 0x3f3f3f3f;

struct Edge {
    int v, nxt;
    long long cap;
    Edge(int _v = 0, int _nxt = 0, long long _cap = 0) {
        v = _v, nxt = _nxt, cap = _cap;
    }
};

int edgecnt;
int head[MAX_V];
Edge G[MAX_N];
int d[MAX_V], gap[MAX_N];

struct Isap {
	int n, s, t;
	void init(int n, int s, int t) {
		this->n = n, this->s = s, this->t = t;
		edgecnt = 0;
		memset(head, -1, sizeof head);
	}
	void addedge(int u, int v, long long cap) {
		G[edgecnt] = Edge(v, head[u], cap);
		head[u] = edgecnt++;
		G[edgecnt] = Edge(u, head[v], 0);
		head[v] = edgecnt++;
	}
	long long dfs(int u, long long tot) {
		if (u == t) return tot;
		int minh = n - 1;
		long long leave = tot;
		for (int i = head[u]; ~i && leave; i = G[i].nxt) {
			int v = G[i].v;
			if (G[i].cap > 0) {
				if (d[v] + 1 == d[u]) {
					long long c = dfs(v, min(leave, G[i].cap));
					G[i].cap -= c;
					G[i ^ 1].cap += c;
					leave -= c;
					if (d[s] >= n)
						return tot - leave;
				}
				minh = min(minh, d[v]);
			}
		}
		if (leave == tot) {
			--gap[d[u]];
			if (gap[d[u]] == 0) d[s] = n;
			d[u] = minh + 1;
			++gap[d[u]];
		}
		return tot - leave;
	}
	long long maxFlow() {
		long long ret = 0;
		memset(gap, 0, sizeof gap);
		memset(d, 0, sizeof d);
		gap[0] = n;
		while (d[s] < n) {
			ret += dfs(s, INF);
		}
		return ret;
	}
};

int main() {
    int n, m;
    while (2 == scanf("%d%d", &n, &m)) {
        Isap Flow;
        Flow.init(n + m + 2, 0, n + m + 1);
        for (int i = 1; i <= n; ++i) {
            int v;
            scanf("%d", &v);
            Flow.addedge(i, n + m + 1, v);
        }
        int sum = 0;
        for (int i = 1; i <= m; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            Flow.addedge(0, i + n, w);
            Flow.addedge(i + n, u, INF);
            Flow.addedge(i + n, v, INF);
            sum += w;
        }
        int ans = Flow.maxFlow();
        printf("%d\n", sum - ans);
    }
    return 0;
}

