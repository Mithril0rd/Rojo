#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <map>

using namespace std;

const int MAX_N = 30007;

typedef pair<int,int> pii;

#define lson idx << 1
#define rson lson | 1

struct Node {
	int v, w, nxt;
	Node() {
		
	}
	Node (int _v, int _w, int _nxt) {
		v = _v, w = _w, nxt = _nxt;
	}
}; 

struct Node2 {
	int l, r, v, laz;
	Node2 () {
		
	}
	Node2(int _l, int _r, int _v, int _laz) {
		l = _l, r = _r, v = _v, laz = _laz;
	}
};

int n;
map<string,int> id;
Node E[MAX_N << 1];
int cnt, edgecnt, head[MAX_N];
pii Edge[MAX_N];
bool vis[MAX_N];
int val[MAX_N], in[MAX_N], out[MAX_N];
Node2 T[MAX_N << 2];

void Clear() {
	edgecnt = 0;
	memset(head, -1, sizeof head);
	memset(T, 0, sizeof T);
	memset(val, 0, sizeof val);
	memset(in, 0, sizeof in);
	memset(out, 0, sizeof out);
	memset(vis, false, sizeof vis);
	id.clear();
}

void addedge(int u, int v, int w) {
	E[edgecnt] = Node(v, w, head[u]);
	head[u] = edgecnt++;
}

void dfs(int u, int v) {
	vis[u] = true;
	val[++cnt] = v, in[u] = cnt;
	for (int i = head[u]; ~i; i = E[i].nxt) {
		int vv = E[i].v;
		if (!vis[vv]) {
			dfs(vv, v ^ E[i].w);
		}
	}
	out[u] = cnt;
}

struct Segment {
	void up(int idx) {
		T[idx].v = T[lson].v + T[rson].v;
	}
	void down(int idx) {
		if (T[idx].laz) {
			T[lson].laz ^= 1;
			T[rson].laz ^= 1;
			T[lson].v = T[lson].r - T[lson].l + 1 - T[lson].v;
			T[rson].v = T[rson].r - T[rson].l + 1 - T[rson].v;
			T[idx].laz = 0;
		}
	}
	void build(int l, int r, int idx) {
		T[idx] = Node2(l, r, 0, 0);
		if (l == r) {
			T[idx].v = val[l];
			return ;
		}
		int mid = (l + r) >> 1;
		build(l, mid, lson), build(mid + 1, r, rson);
		up(idx);
	}
	void update(int l, int r, int idx) {
		if (l == T[idx].l && r == T[idx].r) {
			T[idx].laz ^= 1;
			T[idx].v = r - l + 1 - T[idx].v;
			return ;
		}
		int mid = (T[idx].l + T[idx].r) >> 1;
		down(idx);
		if (r <= mid) update(l, r, lson);
		else if (l > mid) update(l, r, rson);
		else update(l, mid, lson), update(mid + 1, r, rson);
		up(idx);
	}
};

Segment seg;

int main() {
	int TT;
	scanf("%d", &TT);
	int cas = 0;
	while (TT-- > 0) {
		scanf("%d", &n);
		Clear();
		char str[11];
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str);
			id[string(str)] = i;
		}
		char u[11], v[11];
		int w;
		for (int i = 1; i < n; ++i) {
			scanf("%s%s%d", u, v, &w);
			addedge(id[u], id[v], w);
			addedge(id[v], id[u], w);
			Edge[i] = make_pair(id[u], id[v]);
		}
		cnt = 0;
		dfs(1, 0);
		seg.build(1, n, 1);
		printf("Case #%d:\n", ++cas);
		int q;  
		scanf("%d", &q);
		while (q-- > 0) {
			char typ[4];
			scanf("%s", typ);
			if (typ[0] == 'M') {
				int x;
				scanf("%d", &x);
				int u = Edge[x].first, v = Edge[x].second;
				if (in[u] > in[v]) swap(u, v);
				seg.update(in[v], out[v], 1);
			} else { 
				int ans = T[1].v * (n - T[1].v) * 2;
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}