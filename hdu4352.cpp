#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 21;

typedef long long ll;

ll l, r;
int K;
int digit[MAX_N];
ll dp[MAX_N][1 << 11][12];

ll dfs(int pos, int sta, int one, bool limit) {
	if (pos == 0) return __builtin_popcount(sta) == K;
	if (!limit && ~dp[pos][sta][K]) return dp[pos][sta][K];
	int end = limit ? digit[pos] : 9;
	ll ans = 0;
	for (int i = 0; i <= end; ++i) {
		int Sta = sta;
		for (int j = i; j < 10; ++j) if (sta >> j & 1) {
			Sta = (sta ^ (1 << j)) | (1 << i); 
			break;
		}
		if (Sta == sta) Sta = sta | (1 << i);
		ans += dfs(pos - 1, (one && (i == 0)) ? 0 : Sta, one && (i == 0), limit && i == end);
	}
	if (!limit) return dp[pos][sta][K] = ans;
	return ans;
}

ll cal(ll x) {
	int n = 0;
	while (x > 0) {
		digit[++n] = x % 10;
		x /= 10;
	}
	return dfs(n, 0, 1, 1);
}

int main() {
	int T;
	scanf("%d", &T);
	memset(dp, -1, sizeof dp);
	int cas = 0;
	while (T-- > 0) {
		scanf("%I64d%I64d%d", &l, &r, &K);
		ll ans = cal(r) - cal(l - 1);
		printf("Case #%d: %I64d\n", ++cas, ans);
	}
	return 0;
}