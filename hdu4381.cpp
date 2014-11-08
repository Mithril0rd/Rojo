#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 1007;

struct Node {
	int a, x;
	Node () {
		
	}
	Node (int _a, int _x) {
		a = _a, x = _x;
	}
	bool operator < (const Node &rhs) const {
		return a < rhs.a;
	}
};

int n, m;
Node z1[MAX_N], z2[MAX_N];
int dp[2][MAX_N];

bool cmp2(Node a, Node b) {
	return a.a > b.a;
}

int main() {
	int T;
	scanf("%d", &T);
	int cas = 0;
	while (T-- > 0) {
		scanf("%d%d", &n, &m);
		memset(dp, -1, sizeof dp);
		int n1 = 0, n2 = 0;
		for (int i = 1; i <= m; ++i) {
			int typ;
			scanf("%d", &typ);
			if (typ == 1) {
				scanf("%d%d", &z1[n1].a, &z1[n1].x), ++n1;
			} else scanf("%d%d", &z2[n2].a, &z2[n2].x), ++n2;
		}	
		sort(z1, z1 + n1);
		sort(z2, z2 + n2, cmp2);
		dp[0][0] = dp[1][0] = 0;
		for (int i = 0; i < n1; ++i) {
			for (int j = z1[i].a; j >= z1[i].x; --j) {
				if (~dp[0][j - z1[i].x]) {
					if (~dp[0][j]) dp[0][j] = min(dp[0][j], dp[0][j - z1[i].x] + 1);
					else dp[0][j] = dp[0][j - z1[i].x] + 1;
				}
			}
		}
		for (int i = 0; i < n2; ++i) {
			for (int j = n + 1 - z2[i].a; j >= z2[i].x; --j) {
				if (~dp[1][j - z2[i].x]) {
					if (~dp[1][j]) dp[1][j] = min(dp[1][j], dp[1][j - z2[i].x] + 1);
					else dp[1][j] = dp[1][j - z2[i].x] + 1;
				}
			}
		}

		int ans1 = 0, ans2 = 0x3f3f3f3f;
		for (int i = 0; i <= n; ++i) {
			for (int j = i + 1; j <= n + 1; ++j) {
				if (~dp[0][i] && ~dp[1][n - j + 1]) {
					if (i + n - j + 1 == ans1) ans2 = min(ans2, dp[0][i] + dp[1][n - j + 1]);
					else if (i + n - j + 1 > ans1) ans1 = i + n - j + 1, ans2 = dp[0][i] + dp[1][n - j + 1];
				}
			}
		}
		if (ans2 == 0x3f3f3f3f) ans2 = 0;
		printf("Case %d: %d %d\n", ++cas, ans1, ans2);
	}
	return 0;
}