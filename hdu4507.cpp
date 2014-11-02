#include <cstdio>
#include <cstring>

const int MAX_N = 21;
const int MOD = (int)1e9 + 7;

typedef long long ll;

struct Node {
	ll n, sum, power;
	Node () {
		
	}
	Node (ll _n, ll _s, ll _p) {
		n = _n, sum = _s, power = _p;
	}
};

ll l, r;
int digit[MAX_N];
ll p[MAX_N];
Node dp[MAX_N][8][8];

Node dfs(int pos, int Dr, int Sr, bool limit) {
	if (pos == 0) return dp[pos][Dr][Sr] = Node(Dr && Sr, 0, 0);
	if (!limit && ~dp[pos][Dr][Sr].n) return dp[pos][Dr][Sr]; 
	int end = limit ? digit[pos] : 9;
	Node now(0, 0, 0);
	for (int i = 0; i <= end; ++i) {
		if (i == 7) continue;
		Node pre = dfs(pos - 1, (Dr + i) % 7, (Sr * 10 + i) % 7, limit && i == end);
		now.n = (now.n + pre.n) % MOD;
		now.sum = ((now.sum + i * p[pos - 1] % MOD * pre.n % MOD) % MOD + pre.sum) % MOD;
		now.power = (((now.power + i * i % MOD * p[pos - 1] % MOD * p[pos - 1] % MOD * pre.n % MOD) % MOD + 2 * i % MOD * p[pos - 1] % MOD * pre.sum % MOD) % MOD + pre.power) % MOD;
	}
	if (!limit) return dp[pos][Dr][Sr] = now;
	return now;
}

ll cal(ll x) {
	int n = 0;
	while (x > 0) {
		digit[++n] = x % 10;
		x /= 10;
	}
	return dfs(n, 0, 0, 1).power;
} 

int main() {
	p[0] = 1;
	for (int i = 1; i < MAX_N; ++i) 
		p[i] = (p[i - 1] * 10) % MOD;
	int T;
	scanf("%d", &T);
	memset(dp, -1, sizeof dp);
	while (T-- > 0) {
		scanf("%I64d%I64d", &l, &r);
		ll ans = (cal(r) - cal(l - 1) + MOD) % MOD;
		printf("%I64d\n", ans);
	}
	return 0;
}