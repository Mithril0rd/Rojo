#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 100007 * 2;

struct SAM {
	int val[MAX_N], fa[MAX_N], c[26][MAX_N];
	int tot, last;
	inline int newNode(int step) {
		val[++tot] = step;
		fa[tot] = 0;
		for (int i = 0; i < 26; ++i) c[i][tot] = 0;
		return tot;
	}
	inline void extend(int k) {
		int p = last;
		int np = newNode(val[last] + 1);
		while (p && !c[k][p]) c[k][p] = np, p = fa[p];
		if (!p) fa[np] = 1;
		else {
			int q = c[k][p];
			if (val[q] == val[p] + 1) fa[np] = q;
			else {
				int nq = newNode(val[p] + 1);
				for (int i = 0; i < 26; ++i) c[i][nq] = c[i][q];
				fa[nq] = fa[q];
				fa[q] = fa[np] = nq;
				while (p && c[k][p] == q) c[k][p] = nq, p = fa[p];
			}
		}
		last = np;
	}
	inline int add(int k) {
		extend(k);
	}
	inline void init() {
		tot = 0;
		last = newNode(0);
	}
} suf;

int c[MAX_N], sa[MAX_N], match[MAX_N];
char str[MAX_N], s[MAX_N];

int main() {
	int T;
	scanf("%d", &T);
	int cas = 0;
	while (T-- > 0) {
		int n;
		scanf("%d", &n);
		scanf("%s", str);
		int len = (int) strlen(str);
		suf.init();
		memset(match, 0, sizeof match);
		memset(c, 0, sizeof c);
		memset(sa, 0, sizeof sa);
		for (int i = 0; i < len; ++i) suf.add(str[i] - 'a');
		while (n-- > 0) {
			scanf("%s", s);
			int len2 = (int) strlen(s), j = 1;
			int ans = 0;
			for (int i = 0; i < len2; ++i) {
				int id = s[i] - 'a';
				if (suf.c[id][j]) {
					j = suf.c[id][j];
					match[j] = max(match[j], ++ans);
				} else {
					while (j && !suf.c[id][j]) j =  suf.fa[j];
					if (!j) ans = 0, j = 1;
					else {
						ans = suf.val[j] + 1;
						j = suf.c[id][j];
						match[j] = max(match[j], ans);
					}
				}
			}
		} 
		for (int i = 1; i <= suf.tot; ++i) ++c[suf.val[i]];
		for (int i = 1; i <= len; ++i) c[i] += c[i - 1];
		for (int i = 1; i <= suf.tot; ++i) sa[c[suf.val[i]]--] = i;
		long long ans = 0;
		for (int i = suf.tot; i > 0; --i) {
			int id = sa[i];
			if (match[id]) {
				match[suf.fa[id]] = max(match[suf.fa[id]], match[id]);
				if (match[id] < suf.val[id]) ans += suf.val[id] - match[id];
			} else ans += suf.val[id] - suf.val[suf.fa[id]];
		}
		printf("Case %d: %I64d\n", ++cas, ans);
	}
	return 0;
}