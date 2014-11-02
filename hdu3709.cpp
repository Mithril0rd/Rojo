#include <cstdio>
#include <cstring>

typedef long long ll;

ll l, r;
int digit[21];
ll dp[21][2007][21];

ll dfs(int pos, int sum, int o, bool limit) {
	if (sum < 0) return 0;
	if (pos == 0) return dp[pos][sum][o] = (sum == 0);
	if (!limit && ~dp[pos][sum][o]) return dp[pos][sum][o];
	int end = limit ? digit[pos] : 9;
	ll ans = 0;
	for (int i = 0; i <= end; ++i) {
		ans += dfs(pos - 1, sum + (pos - o) * i, o, limit && i == end);
	}
	if (!limit) return dp[pos][sum][o] = ans;
	return ans;
}

ll cal(ll x) {
	if (x < 0) return -1;
	int n = 0;
	while (x > 0) {
		digit[++n] = x % 10;
		x /= 10;
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += dfs(n, 0, i, 1);
	}
	return ans - n;
}

int main() {
	int T;
	scanf("%d", &T);
	memset(dp, -1, sizeof dp);
	while (T-- > 0) {
		scanf("%I64d%I64d", &l, &r);
		ll ans = cal(r) - cal(l - 1);
		printf("%I64d\n", ans);
	}
	return 0;
}