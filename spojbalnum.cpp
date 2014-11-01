#include <cstdio>
#include <cstring>

const int MAX_N = 22;
const int MAX_M = 59057;

typedef long long ll;

ll l, r;
int bit[MAX_N], cnt;
int digit[MAX_N];
ll dp[MAX_N][MAX_M][2];

int _3to10() {
	int s = 0, base = 1;
	for (int i = 0; i < 10; ++i) {
		s += base * digit[i];
		base *= 3;
	}
	return s;
}

void _10to3(int x) {
	for (int i = 0; i < 10; ++i) {
		digit[i] = x % 3;
		x /= 3;
	}
}

int nxt(int s, int k) {
	_10to3(s);
	if (digit[k] == 0) digit[k] = 1;
	else if (digit[k] == 1) digit[k] = 2;
	else digit[k] = 1;
	return _3to10();
}

bool check(int s) {
	_10to3(s);
	for (int i = 0; i < 10; ++i) {
		if (i & 1) { if (digit[i] == 1) return false;}
		else if (digit[i] == 2) return false;
	}
	return true;
}

ll dfs(int pos, int sum, int one, bool limit) {
	if (pos == 0) return dp[pos][sum][one] = check(sum);
	if (!limit && ~dp[pos][sum][one]) return dp[pos][sum][one];
	int end = limit ? bit[pos] : 9;
	ll ans = 0;
	for (int i = 0; i <= end; ++i) {
		ans += dfs(pos - 1, one || i ? nxt(sum, i) : sum, one || i, limit && i == end);
	}
	if (!limit) return dp[pos][sum][one] = ans;
	return ans;
}

ll cal(ll x) {
	if (x == 0) return 1;
	cnt = 0;
	while (x > 0) {
		bit[++cnt] = x % 10;
		x /= 10;
	}
	return dfs(cnt, 0, 0, 1);
}

int main() {
	int T;
	scanf("%d", &T);
	memset(dp, -1, sizeof dp);
	while (T-- > 0) {
		scanf("%lld%lld", &l, &r);
		ll ans = cal(r) - cal(l - 1);
		printf("%lld\n", ans);
	}
	return 0;
}