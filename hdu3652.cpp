#include <cstdio>
#include <cstring>

const int MAX_N = 17;

int n;	
int bit[MAX_N];
int dp[MAX_N][MAX_N][3];

int dfs(int pos, int mod, int sta, bool limit) {
	if (pos == -1) return mod == 0 && sta == 2;
	if (!limit && ~dp[pos][mod][sta]) return dp[pos][mod][sta];
	int end = limit ? bit[pos] : 9, ans = 0;
	for (int i = 0; i <= end; ++i) {
		int Sta = sta;
		if (sta != 2 && i != 1) Sta = 0;
		if (sta != 2 && i == 1) Sta = 1;
		if (sta == 1 && i == 3) Sta = 2;
		ans += dfs(pos - 1, (mod * 10 + i) % 13, Sta, limit && i == end);
	}
	if (!limit) return dp[pos][mod][sta] = ans;
	return ans;
}

int main() {
	while (1 == scanf("%d", &n)) {
		int pos = 0;
		while (n > 0) {
			bit[pos++] = n % 10;
			n /= 10;
		}
		memset(dp, -1, sizeof dp);
		int ans = dfs(pos - 1, 0, 0, 1);
		printf("%d\n", ans);
	}
	return 0;
}