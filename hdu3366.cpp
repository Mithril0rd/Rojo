#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 1007;

struct Node {
	double p, q;
	Node () {
		
	}
	Node (double _p, double _q) {
		p = _p, q = _q;
	}
	bool operator < (const Node &rhs) const {
		return p * rhs.q > q * rhs.p;
	}
};

int n, m;
Node a[MAX_N];
double dp[MAX_N][17];

int main() {
	int T;
	scanf("%d", &T);
	int cas = 0;
	while (T-- > 0) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) scanf("%lf%lf", &a[i].p, &a[i].q);
		sort(a + 1, a + 1 + n);
		memset(dp, 0, sizeof dp);
		for (int i = 0; i <= m; ++i) dp[n][i] = a[n].p;
		for (int i = n - 1; i > 0; --i) {
			dp[i][0] = a[i].p + dp[i + 1][0] * (1 - a[i].p - a[i].q);
			for (int j = 1; j <= m; ++j) {
				dp[i][j] = a[i].p + dp[i + 1][j - 1] * a[i].q + dp[i + 1][j] * (1 - a[i].q - a[i].p);
			}
		}
		printf("Case %d: %.5f\n",++cas, dp[1][m]);
	}
	return 0;
}
