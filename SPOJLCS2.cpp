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

char s[MAX_N];
int dp[11][MAX_N];

int main() {
	scanf("%s", s);
	suf.init();
	int len2 = (int) strlen(s), id = 0, get = 0;
	for (int i = 0; i < len2; ++i) suf.add(s[i] - 'a');
	for (int i = 1; i <= suf.tot; ++i) dp[0][i] = suf.val[i];
	while (1 == scanf("%s", s)) {
		++id;
		int len = (int) strlen(s);
		int j = 1, ans = 0;
		for (int i = 0; i < len; ++i) {
			int ch = s[i] - 'a';
			while (suf.fa[j] && !suf.c[ch][j]) j = suf.fa[j], ans = suf.val[j];
			if (suf.c[ch][j]) {
				j = suf.c[ch][j];
				++ans;
				dp[id][j] = max(dp[id][j], min(dp[id - 1][j], ans));
				for (int k = suf.fa[j]; suf.fa[k]; k = suf.fa[k]) {
					if (dp[id][k] >= dp[id - 1][k]) break;
					dp[id][k] = dp[id - 1][k];
				}
			}
		}
		int now = 0;
		for (int i = 1; i <= suf.tot; ++i) now = max(now, dp[id][i]);
		get = now;
	}
	printf("%d\n", get);
	return 0;
}