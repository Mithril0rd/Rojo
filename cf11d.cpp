#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 20;
const int MAX_S = 1 << MAX_N;

int n, m;
bool Edge[MAX_N][MAX_N];
long long dp[MAX_S][MAX_N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		Edge[u - 1][v - 1] = Edge[v - 1][u - 1] = true;
	}
	
	for (int i = 0; i < n; ++i) dp[1 << i][i] = 1;
	long long ans = 0;
	for (int s = 0; s < 1 << n; ++s) {
		int id = 0;
		for (int i = 0; i < n; ++i) {
			if (s >> i & 1) {
				id = i;
				break;
			}
		}
		for (int i = 0; i < n; ++i) {
			if ((s >> i & 1) && dp[s][i]) {
				for (int j = id; j < n; ++j) {
					if (i == j) continue;
					if (Edge[i][j]) {
						if (s >> j & 1) {
							if ((s ^ (1 << i)) == (1 << j)) continue;
							if (j == id) ans += dp[s][i];
						} else 
							dp[s | (1 << j)][j] += dp[s][i];
					}
				}
			}
		}
	}
	printf("%I64d\n", ans / 2);
	return 0;
}