#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 200007;

struct Node {
	int l, r, id;
	Node () {
		
	}
	Node (int _l, int _r, int _id) {
		l = _l, r = _r, id = _id;
	}
	bool operator < (const Node &rhs) const {
		return l < rhs.l;
	}
};

int n, m;
int a[MAX_N];
int l[MAX_N], r[MAX_N];
int bit[MAX_N], occ[MAX_N], ans[MAX_N];
Node que[MAX_N];
vector<int> vec[MAX_N], nf[MAX_N];

int lowbit(int x) {return x & -x; }

void add(int x, int val) {
	while (x < MAX_N) {
		bit[x] += val;
		x += lowbit(x); 
	}
} 

int sum(int x) {
	int s = 0;
	while (x > 0) {
		s += bit[x];
		x -= lowbit(x);
	}
	return s;
}

void Factor() {
	for (int i = 2; i < MAX_N; ++i) {
		for (int j = i; j < MAX_N; j += i) {
			vec[j].push_back(i);
		}
	} 
}

void Clear() {
	memset(l, 0, sizeof l);
	memset(r, 0, sizeof r);
	memset(bit, 0, sizeof bit);
	memset(ans, 0, sizeof ans);
}

int main() {
	Factor();
	while (2 == scanf("%d%d", &n, &m)) {
		if (0 == n && 0 == m) break;
		Clear();	
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &que[i].l, &que[i].r);
			que[i].id = i;
		}
		sort(que + 1, que + 1 + m);
		memset(occ, 0, sizeof occ);
		for (int i = 1; i <= n; ++i) {
			int pos = 0, sz = (int)vec[a[i]].size();
			for (int j = 0; j < sz; ++j) {
				pos = max(pos, occ[vec[a[i]][j]]);
				occ[vec[a[i]][j]] = i;
			}
			l[i] = pos;
		}
		memset(occ, 0x3f, sizeof occ);
		for (int i = n; i > 0; --i) {
			int pos = n + 1, sz = (int) vec[a[i]].size();
			for (int j = 0; j < sz; ++j) {
				pos = min(pos, occ[vec[a[i]][j]]);
				occ[vec[a[i]][j]] = i;
			}
			r[i] = pos;
		} 
		for (int i = 1; i <= n; ++i) {
			if (l[i]) {
				nf[l[i]].push_back(i);
			} else {
				add(i, 1);
				if (r[i] <= n) add(r[i], -1);
			}
		}
		int k = 1;
		for (int i = 1; i <= n; ++i) {
			while (k <= m && que[k].l == i) {
				ans[que[k].id] = sum(que[k].r) - sum(que[k].l - 1);
				++k;
			}
			if (r[i] <= n) add(r[i], 1);
			for (int j = 0; j < (int) nf[i].size(); ++j) {
				int pos = nf[i][j];
				add(pos, 1);
				if (r[pos] <= n) add(r[pos], -1);
			}
			nf[i].clear();
		}
		for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}