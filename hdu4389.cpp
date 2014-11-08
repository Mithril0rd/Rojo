#include <cstdio>
#include <cstring>

int l, r, z;
int digit[11];
int dp[11][90][90][90];

int dfs(int pos, int Ds, int x, int mod, bool limit) {
	if (pos == 0) return dp[pos][Ds][x][mod] = (x == Ds) && (mod == 0);
	if (!limit && ~dp[pos][Ds][x][mod]) return dp[pos][Ds][x][mod];
	int end = limit ? digit[pos] : 9;
	int ans = 0;
	for (int i = 0; i <= end; ++i) {
		ans += dfs(pos - 1, Ds + i, x, (mod * 10 + i) % x, limit && i == end);
	}
	if (!limit) return dp[pos][Ds][x][mod] = ans;
	return ans;
}

int cal(int x) {
	int n = 0;
	z = 0;
	while (x > 0) {
		digit[++n] = x % 10;
		z += x % 10;
		x /= 10;
	}
	int ans = 0;
	for (int i = 1; i < 82; ++i) {
		ans += dfs(n, 0, i, 0, 1);
	}
	return ans;
} 

int main() {
	memset(dp, -1, sizeof dp);
	int T;
	int Cas = 0;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d%d", &l, &r);
		int ans = cal(r) - cal(l - 1);
		printf("Case %d: %d\n", ++Cas, ans);
	}
	return 0;
}