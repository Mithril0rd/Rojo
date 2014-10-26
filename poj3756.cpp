#include <cstdio>
#include <cstring>
#include <cmath>

const int MAX_N = 107;
const double eps = 1e-8;

int n;
int go[MAX_N];
bool stop[MAX_N];
double dp[MAX_N * MAX_N][MAX_N];

void Clear() {
	memset(dp, 0, sizeof dp);
	memset(stop, 0, sizeof stop);
	memset(go, 0, sizeof go);
}

int main() {
	while (1 == scanf("%d", &n)) {
		Clear();
		int m;
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) {
			int a, b;
			scanf("%d%d", &a, &b);
			go[a] = b;
		}
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) {
			int a, b;
			scanf("%d%d", &a, &b);
			go[a] = -b;
		}
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) {
			int a;
			scanf("%d", &a);
			stop[a] = true;
		}
		dp[0][0] = 1.0;
		int limit = MAX_N * MAX_N;
		for (int i = 1; i < limit; ++i) {
			for (int j = 0; j < n; ++j) {
				if (fabs(dp[i - 1][j]) < eps) continue;
				for (int k = 1; k <= 6; ++k) {
					int now = j + k;
					if (now > n) now = 2 * n - now;
					if (stop[now]) {
						dp[i + 1][now] += 1.0 / 6 * dp[i - 1][j];
					} else {
						now += go[now];
						if (now > n) now = 2 * n - now;
						else if (now < 0) now = -now;
						dp[i][now] += 1.0 / 6 * dp[i - 1][j];
					}
				}
			}
		}
		double ans = 0;
		for (int i = 1; i < limit; ++i) ans += i * dp[i][n];
		if (fabs(ans) < eps) puts("Impossible");
		else printf("%.2f\n", ans);
	}
	return 0;
}