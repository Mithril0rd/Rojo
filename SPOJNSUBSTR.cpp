#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 250007 * 2;

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
int dp[MAX_N], C[MAX_N], id[MAX_N], cnt[MAX_N];

int main() {
	scanf("%s", str);
	int len = (int)strlen(str);
	suf.init();
	for (int i = 0; i < len; ++i) 
		suf.add(str[i] - 'a');
	for (int i = 1; i <= suf.tot; ++i) ++C[suf.val[i]];
	for (int i = 1; i <= len; ++i) C[i] += C[i - 1];
	for (int i = 1; i <= suf.tot; ++i) id[C[suf.val[i]]--] = i;
	int j = 1;
	for (int i = 0; i < len; ++i) {
		++cnt[suf.c[str[i] - 'a'][j]];
		j = suf.c[str[i] - 'a'][j];
	}
	for (int i = suf.tot; i > 0; --i) {
		int d = id[i];
		dp[suf.val[d]] = max(dp[suf.val[d]], cnt[d]);
		cnt[suf.fa[d]] += cnt[d];
	}
	for (int i = len - 1; i > 0; --i) 
		dp[i] = max(dp[i], dp[i + 1]);
	for (int i = 1; i <= len; ++i) printf("%d\n", dp[i]);
	return 0;
}