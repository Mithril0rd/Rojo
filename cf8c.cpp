#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_N = 25;
const int MAX_S = 1<<25;

int n;
int x[MAX_N], y[MAX_N];
int d[MAX_N][MAX_N];
int dp[MAX_S], pre[MAX_S];
vector<int> ans;

int dis(int i, int j) {
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

int main() {
	int q1, q2;
	scanf("%d%d", &q1, &q2);
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &x[i], &y[i]);
	}
	x[n] = q1, y[n] = q2;
	for (int i = 0; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			d[i][j] = d[j][i] = dis(i, j);
		} 
	}
	memset(dp, -1, sizeof dp);
	dp[0] = 0;
	int limit = 1 << n;
	for (int s = 0; s < limit; ++s) {
		if (~dp[s]) {
			for (int i = 0; i < n; ++i) {
				if ((s >> i & 1) == 0) {
					int cost = dp[s] + 2 * d[i][n];
					if (dp[s | (1 << i)] == -1 || cost < dp[s | (1 << i)]) {
						dp[s | (1 << i)] = cost;
						pre[s | (1 << i)] = s;
					}
					for (int j = 0; j < n; ++j) {
						if (j != i && (s >> j & 1) == 0) {
							int cost2 = dp[s] + d[n][i] + d[i][j] + d[j][n];
							if (dp[s | (1 << i) | (1 << j)] == -1 || cost2 < dp[s | (1 << i) | (1 << j)]) {
								dp[s | (1 << i) | (1 << j)] = cost2;
								pre[s | (1 << i) | (1 << j)] = s;
							}
						}
					}
					break;
				}
			}
		}
	}
	printf("%d\n", dp[limit - 1]);
	int state = limit - 1;
	while (state) {
		int now = pre[state], get = now ^ state;
		state = now;
		int a = 0, b = 0;
		for (int i = 0; i < n; ++i) {
			if (get >> i & 1) {
				b = a, a = i + 1;
			}
		}
		ans.push_back(0), ans.push_back(a);
		if (b) ans.push_back(b);
	}
	ans.push_back(0);
	for (int i = ans.size() - 1; i >= 0; --i) printf("%d ", ans[i]);
	return 0;
}