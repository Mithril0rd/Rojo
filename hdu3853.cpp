#include <cstdio>
#include <cstring>
#include <cmath>

const int MAX_N = 1007;
const double eps = 1e-8;

int n, m;
double r[MAX_N][MAX_N], d[MAX_N][MAX_N], t[MAX_N][MAX_N];
double dp[MAX_N][MAX_N];

double dfs(int x, int y) {
	if (x > n || y > m) return 0;
	if (x == n && y == m) return dp[x][y] = 0;
	if (fabs(t[x][y] - 1.) < eps) return 0;
	if (!(fabs(dp[x][y]) < eps)) return dp[x][y];
	dp[x][y] = (2. + d[x][y] * dfs(x + 1, y ) + r[x][y] * dfs(x, y + 1)) / (1 - t[x][y]);
	return dp[x][y];
}

int main() {
	while (2 == scanf("%d%d", &n, &m)) {
		memset(dp, 0, sizeof dp);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%lf%lf%lf", &t[i][j], &r[i][j], &d[i][j]);
			}
		}
		double ans = dfs(1, 1);
		printf("%.3f\n", ans);
	}
	return 0;
}