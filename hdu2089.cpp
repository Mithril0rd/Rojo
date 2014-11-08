#include <cstdio>
#include <cstring>

int l, r;
int digit[8];
int dp[8][3];

int dfs(int pos, int hav, bool limit) {
	if (pos == 0) return dp[pos][hav] = (hav != 2);
	if (!limit && ~dp[pos][hav]) return dp[pos][hav];
	int end = limit ? digit[pos] : 9;
	int ans = 0;
	for (int i = 0; i <= end; ++i) {
		if (i == 4 || hav == 2) continue;
		int Nhav = hav;
		if (hav == 0 && i == 6) Nhav = 1;
		if (hav == 1 && i != 6) Nhav = 0;
		if (hav == 1 && i == 2) Nhav = 2;
		ans += dfs(pos - 1, Nhav, limit && i == end);
	}
	if (!limit) return dp[pos][hav] = ans;
	return ans;
}

int cal(int x) {
	int n = 0;
	while (x > 0) {
		digit[++n] = x % 10;
		x /= 10;
	}
	return dfs(n, 0, 1);
} 

int main() {
	memset(dp, -1, sizeof dp);
	while (2 == scanf("%d%d", &l, &r)) {
		if (0 == l && 0 == r) break;
		int ans = cal(r) - cal(l - 1);
		printf("%d\n", ans);
	}
	return 0;
}