 #include <cstdio>  
#include <cstring>  
#include <algorithm>  

using namespace std;  
 
typedef long long ll;  
  
const int MAX_N = 77;  

int l, r;
int bit[10];
int dp[10][MAX_N << 1][2];

int get(int x) {
	return x & 1 ? -1 : 1;
}

int dfs(int pos, int sum, bool zero, bool limit) {
	if (pos == 0) return dp[pos][sum][zero] = sum == 78;
	if (!limit && ~dp[pos][sum][zero]) return dp[pos][sum][zero];
	int end = limit ? bit[pos] : 9;
	int ans = 0;
	for (int i = 0; i <= end; ++i) {
		ans += dfs(pos - 1, sum + get(pos) * i, zero && i == 0, i == end && limit);
	}
	if (!limit) return dp[pos][sum][zero] = ans;
	return ans;
}

int cal(int x) {
	if (x <= 0) return 0;
	int n = 0;
	while (x > 0) {
		bit[++n] = x % 10;
		x /= 10;
	}
	return dfs(n, MAX_N, 1, 1);
}

int main() {
	int T;
	scanf("%d", &T);
	memset(dp, -1, sizeof dp);
	while (T-- > 0) {
		scanf("%d%d", &l, &r);
		int ans = cal(r) - cal(l - 1);
		printf("%d\n", ans);
	}
	return 0;
}