#include <cstdio>
#include <cstring>

const int MAX_N = 4607;

int l, r;
int digit[11];
int dp[11][MAX_N];

int F(int x) {
	int ans = 0, base = 1;
	while (x > 0) {
		ans += x % 10 * base;
		base <<= 1;
		x /= 10;
	}
	return ans;
}

int dfs(int pos, int sum, bool limit) {
	if (pos == 0) return dp[pos][sum] = sum >= 0;
	if (!limit && ~dp[pos][sum]) return dp[pos][sum];
	int end = limit ? digit[pos] : 9;
	int ans = 0;
	for (int i = 0; i <= end; ++i) {
		if (sum - i * (1 << (pos - 1)) < 0) break;
		ans += dfs(pos - 1, sum - i * (1 << (pos - 1)), limit && i == end);
	}
	if (!limit) return dp[pos][sum] = ans;
	return ans;
}

int cal(int x) {
	int n = 0;
	while (x > 0) {
		digit[++n] = x % 10;
		x /= 10;
	}
	return dfs(n, F(l), 1);
}

int main() {
	int T;
	int cas = 0;
	scanf("%d", &T);
	memset(dp, -1, sizeof dp);
	while (T-- > 0) {
		scanf("%d%d", &l, &r);
		int ans = cal(r);
		printf("Case #%d: %d\n", ++cas, ans);
	}
	return 0;
}