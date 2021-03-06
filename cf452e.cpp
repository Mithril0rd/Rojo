#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 300007 * 2;
const int MOD = 1000000007;

struct SAM {
	int val[MAX_N], fa[MAX_N], c[30][MAX_N];
	int tot, last;
	inline int newNode(int step) {
		val[++tot] = step;
		fa[tot] = 0;
		for (int i = 0; i < 30; ++i) c[i][tot] = 0;
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
				for (int i = 0; i < 30; ++i) c[i][nq] = c[i][q];
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

int n;
char str[MAX_N], ans[MAX_N];
int c[MAX_N], sa[MAX_N];
long long dp[MAX_N][3];
long long num[MAX_N];
bool vis[MAX_N];

void dfs(int u) {
	if (vis[u]) return ;
	vis[u] = true;
	for (int i = 26; i < 29; ++i) if (suf.c[i][u]) ++dp[u][i - 26];
	for (int i = 0; i < 26; ++i) {
		if (suf.c[i][u]) { 
			dfs(suf.c[i][u]);
			for (int j = 0; j < 3; ++j) dp[u][j] = (dp[u][j] + dp[suf.c[i][u]][j]) % MOD;
		}
	} 
}

int main() {
	suf.init();
	scanf("%s", str);
	n = (int)strlen(str);
	int l = 0;
	for (int i = 0; str[i]; ++i) suf.add(str[i] - 'a'), ans[l++] = str[i];
	suf.add(26), ans[l++] = 26 + 'a';
	scanf("%s", str);
	n = min(n, (int) strlen(str));
	for (int i = 0; str[i]; ++i) suf.add(str[i] - 'a'), ans[l++] = str[i];
	suf.add(27), ans[l++] = 27 + 'a';
	scanf("%s", str);
	n = min(n, (int) strlen(str));
	for (int i = 0; str[i]; ++i) suf.add(str[i] - 'a'), ans[l++] = str[i];
	suf.add(28), ans[l++] = 28 + 'a';
	dfs(1);
	for (int i = 1; i <= suf.tot; ++i) {
		long long now = ((dp[i][0] * dp[i][1]) % MOD * dp[i][2]) % MOD;
		num[suf.val[i]] = (num[suf.val[i]] + now) % MOD;
		num[suf.val[suf.fa[i]]] = ((num[suf.val[suf.fa[i]]] - now) % MOD + MOD) % MOD;
	}
	for (int i = suf.tot; i > 0; --i) num[i] = (num[i] + num[i + 1]) % MOD;
	for (int i = 1; i <= n; ++i) printf("%I64d\n", num[i]);
	return 0;
}