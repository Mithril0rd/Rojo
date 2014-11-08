#include <cstdio>
#include <cstring>

const int MAX_N = 1007;
const int MAX_M = 32;

int M, T, N;
double dp[MAX_N][MAX_M][MAX_M];
double p[MAX_N][MAX_M], s[MAX_N][MAX_M];

int main() {
	while(3 == scanf("%d%d%d", &M, &T, &N)) {
		if(!M && !T && !N)
			break;
		for (int i = 1; i <= T; ++i) {
			for (int j = 1; j <= M; ++j) {
				scanf("%lf", &p[i][j]);
			}
		}
		memset(dp, 0, sizeof dp);
		memset(s, 0, sizeof s);
		for (int i = 1; i <= T; ++i) {
			dp[i][0][0] = 1.0;
			for (int j = 1; j <= M; ++j) {
				dp[i][j][0] = dp[i][j - 1][0] * (1 - p[i][j]);
				for (int k = 1; k <= j; ++k) {
					dp[i][j][k] = dp[i][j - 1][k - 1] * p[i][j] + dp[i][j - 1][k] * (1 - p[i][j]);
				}
			}
			s[i][0] = dp[i][M][0];
			for (int j = 1; j <= M; ++j) 
				s[i][j] = s[i][j - 1] + dp[i][M][j];
		}
		double p1 = 1., p2 = 1.;
		for (int i = 1; i <= T; ++i) p1 *= (s[i][M] - s[i][0]), p2 *= (s[i][N - 1] - s[i][0]);
		printf("%.3f\n", p1 - p2);
	}
	return 0;
}