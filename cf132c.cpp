#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_N = 107;
const int MAX_M = 207;

int n, len;
char str[MAX_N];
int dp[MAX_M][MAX_N][57][3];



int dfs(int dep, int dis, int r, int d) {
	if (r < 0) return 0;
	if (dep == len) return r > 0 ? 0 : abs(dis);
	int &res = dp[dis + 100][dep][r][d + 1]; 
	if (~res) return res;
	res = max(dfs(dep + 1, dis + d, r - (str[dep] != 'F'), d), dfs(dep + 1, dis, r - (str[dep] != 'T'), -1 * d));
	return res;
}

int main() {
	scanf("%s%d", str, &n);
	len = (int) strlen(str);
	memset(dp, -1, sizeof dp);
	int ans = 0;
	while (n >= 0) {
		ans = max(ans, dfs(0, 0, n, 1));
		n -= 2;
	}
	printf("%d\n", ans);
	return 0;
}