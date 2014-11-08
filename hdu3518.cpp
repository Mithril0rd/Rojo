#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 1007 * 2;

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
int l[MAX_N], r[MAX_N];

int main() {
	while (1 == scanf("%s", str)) {
		if (str[0] == '#') break;
		int len = (int) strlen(str);
		suf.init();
		for (int i = 0; i < len; ++i) suf.add(str[i] - 'a');
		for (int i = 1; i <= suf.tot; ++i) c[i] = 0, l[i] = len + 1, r[i] = -1;
		for (int i = 1; i <= suf.tot; ++i) ++c[suf.val[i]];
		for (int i = 1; i <= len; ++i) c[i] += c[i - 1];
		for (int i = 1; i <= suf.tot; ++i) sa[c[suf.val[i]]--] = i;
		int j = 1, k = 0;
		while (true) {
			l[j] = r[j] = suf.val[j];
			if (suf.val[j] == len) break;
			j = suf.c[str[k++] - 'a'][j];
		}
		
		for (int i = suf.tot; i > 1; --i) {
			int id = sa[i];
			l[suf.fa[id]] = min(l[suf.fa[id]], l[id]);
			r[suf.fa[id]] = max(r[suf.fa[id]], r[id]);
		} 
		
		int ans = 0;
		for (int i = 2; i <= suf.tot; ++i) {
			if (r[i] - l[i] > suf.val[suf.fa[i]]) {
				ans += min(r[i] - l[i], suf.val[i]) - suf.val[suf.fa[i]];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}