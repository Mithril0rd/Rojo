#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_N = 21;

struct Node {
	int x, y;
	Node () {
		
	}
	Node (int _x, int _y) {
		x = _x, y = _y;
	}
};

int n;
int sx, sy;
int dp[1 << MAX_N], dis[MAX_N][MAX_N];
int pre[2][1 << MAX_N];
Node p[MAX_N];
vector<int> ans;

int sqr(int x) {
	return x * x;
}

int get(int i, int j) {
	if (i == j) return 2 * (sqr(sx - p[i].x) + sqr(sy - p[i].y));
	return sqr(sx - p[i].x) + sqr(sy - p[i].y) + sqr(p[i].x - p[j].x) + sqr(p[i].y - p[j].y) 
	+ sqr(p[j].x - sx) + sqr(p[j].y - sy);
}

int main() {
	int T;
	scanf("%d", &T);
	int cas = 0;
	while (T-- > 0) {
		scanf("%d%d", &sx, &sy);
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &p[i].x, &p[i].y);
		}
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				dis[i][j] = dis[j][i] = get(i, j);
			}
		}
		memset(dp, 0x3f, sizeof dp);
		memset(pre, 0, sizeof pre);
		dp[0] = 0;
		int limit = 1 << n;
		for (int i = 0; i < limit; ++i) {
			for (int j = 0; j < n; ++j) {
				if (!(i >> j & 1)) {
					for (int k = j; k < n; ++k) {
						if (!(i >> k & 1)) {
							if (dp[i] + dis[j][k] < dp[i | (1 << j) | (1 << k)]) {
								dp[i | (1 << j) | (1 << k)] = dp[i] + dis[j][k];
								pre[0][i | (1 << j) | (1 << k)] = j;
								pre[1][i | (1 << j) | (1 << k)] = k;
							}
						}
					}
					break;
				}
			}
		}
		printf("Case %d:\n%d\n", ++cas, dp[limit - 1]);
		ans.clear();
		--limit;
		while (limit > 0) {
			if (pre[0][limit] != pre[1][limit]) {
				ans.push_back(pre[1][limit]);
				ans.push_back(pre[0][limit]);
				int now = limit;
				limit ^= (1 << pre[1][now]), limit ^= (1 << pre[0][now]);
			} else ans.push_back(pre[0][limit]), limit ^= (1 << pre[0][limit]);
		}
		for (int i = ans.size() - 1; i >= 0; --i) {
			if (i != 0) printf("%d ", ans[i] + 1);
			else printf("%d", ans[i] + 1);
		}
		puts("");
	}
	return 0;
}