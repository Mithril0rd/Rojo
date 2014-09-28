#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 5007;
const long long INF = 1LL<<61;

int n;
int a[MAX_N], b[MAX_N];
long long dp[2][MAX_N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		b[i] = a[i];
		dp[0][i] = 0;
	}
	sort(b + 1, b + 1 + n);
	for (int i = 1; i <= n; ++i) {
		fill(dp[i & 1], dp[i & 1] + n + 1, INF);
		for (int j = 1; j <= n; ++j) {
			dp[i&1][j] =min(dp[i&1][j - 1], dp[i&1^1][j] + abs(a[i] - b[j]));
		}
	}
	long long ans = INF;
	for (int i = 1; i <= n; ++i) {
		ans = min(ans, dp[n&1][i]);
	}
	printf("%I64d\n", ans);
	return 0;
}