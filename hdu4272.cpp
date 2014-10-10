#include<cstdio>  
#include<cstring>  

const int MAX_N = 1027;

int n;
int a[MAX_N];
int dp[MAX_N][MAX_N];

void Clear() {
	memset(dp, -1, sizeof dp);
}

bool dfs(int dep, int sta) {
	if (dep == n) return true;
	if (~dp[dep][sta]) return dp[dep][sta];
	if (sta & 1) return dp[dep][sta] = dfs(dep + 1, sta >> 1);
	for (int j = 1; j <= 9 && dep + j < n; ++j) {
		if (!(sta >> j & 1) && a[dep] == a[dep + j]) {
			if (dfs(dep + 1, sta >> 1 | (1 << (j - 1))))
				return dp[dep][sta] = true;
		}
	}
	return dp[dep][sta] = false; 
}

int main() {
	while (1 == scanf("%d", &n)) {
		for (int i = n - 1; i >= 0; --i) {
			scanf("%d", &a[i]);
		}
		Clear();
		int ans = dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}