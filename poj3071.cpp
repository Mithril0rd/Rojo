#include <cstdio>
#include <cstring>

const int MAX_N = 1 << 8;

int n;
double p[MAX_N][MAX_N];
double dp[8][MAX_N];

int main() {
	while (1 == scanf("%d", &n)) {
		if (-1 == n) break;
		int limit = 1 << n;
		for (int i = 0; i < limit; ++i) {
			for (int j = 0; j < limit; ++j) {
				scanf("%lf", &p[i][j]);
			}
		}
		memset(dp, 0, sizeof dp);
		for (int i = 0; i < limit; ++i) dp[0][i] = 1.;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < limit; ++j) {
				for (int k = 0; k < limit; ++k) {
					if ((j >> (i - 1) ^ 1) == (k >> (i - 1))) {
						dp[i][j] += dp[i - 1][j] * dp[i - 1][k] * p[j][k];					
					}
				}
			}
		}
		double ans = 0;
		int id = 0;
		for (int i = 0; i < limit; ++i) {
			if (ans < dp[n][i]) {
				ans = dp[n][i];
				id = i;
			}
		}
		printf("%d\n", id + 1);
	}
	return 0;
}