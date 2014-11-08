#include <cstdio>
#include <cstring>

const int MAX_N = 90007 * 2;

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

char str[MAX_N];
int c[MAX_N], sa[MAX_N];
int path[MAX_N];
char ch[MAX_N];

int main() {
	scanf("%s", str);
	suf.init();
	int len = (int) strlen(str);
	for (int i = 0; str[i]; ++i) suf.add(str[i] - 'a');
	for (int i = 1; i <= suf.tot; ++i) ++c[suf.val[i]];
	for (int i = 1; i <= len; ++i) c[i] += c[i - 1];
	for (int i = 1; i <= suf.tot; ++i) sa[c[suf.val[i]]--] = i;
	for (int i = suf.tot; i > 0; --i) {
		int k = 0;
		int p = sa[i];
		for (int j = 0; j < 26; ++j) {
			if (suf.c[j][p]) {
				path[p] += path[suf.c[j][p]] + 1;
				suf.c[k++][p] = suf.c[j][p];
				ch[suf.c[j][p]] = j + 'a';
			}
		}
		suf.c[k][p] = 0;
	}
	int q;
	scanf("%d", &q);
	while (q-- > 0) {
		int k;
		scanf("%d", &k);
		int p = 1;
		while (k > 0) {
			int i = 0;
			while (suf.c[i][p]) {
				int u = suf.c[i][p];
				if (path[u] + 1 >= k) {
					putchar(ch[u]);
					--k, p = u;
					break;
				} else k -= path[u] + 1;
				++i;
			}
		}
		puts("");
	}
	return 0;
}