#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 1507 * 2;

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

char str[MAX_N], typ[MAX_N];
int c[MAX_N], sa[MAX_N], dp[MAX_N][MAX_N];

int main() {
	scanf("%s%s", str, typ);
	int k;
	scanf("%d", &k);
	int len = (int) strlen(str);
	suf.init();
	for (int i = 0; i < len; ++i) {
		suf.add(str[i] - 'a');
	}
	for (int i = 1; i <= suf.tot; ++i) ++c[suf.val[i]];
	for (int i = 1; i <= len; ++i) c[i] += c[i - 1];
	for (int i = 1; i <= suf.tot; ++i) sa[c[suf.val[i]]--] = i;
	for (int i = 2; i <= suf.tot; ++i) dp[i][0] = 1;
	for (int i = suf.tot; i > 0; --i) {
		int id = sa[i];
		for (int j = 0; j < 26; ++j) {
			if (suf.c[j][id]) {
				for (int l = 0; l <= k; ++l) {
					if (typ[j] == '1') dp[id][l] += dp[suf.c[j][id]][l];
					else {
						if (l > 0) dp[id][l] += dp[suf.c[j][id]][l - 1];
					}
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= k; ++i) ans += dp[1][i];
	printf("%d\n", ans);
	return 0;
}