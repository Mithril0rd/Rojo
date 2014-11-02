#include <cstdio>
#include <cstring>

int l, r, K;
int C[33][33];

int get(int x, int k) {
	int ans = 0, one = 0;
	for (int i = 32; i > 0; --i) {
		if ((x >> (i - 1) & 1) && k - one >= 0) 
			ans += C[i - 1][k - one], ++one;
	}
	return ans;
}

int solve() {
	int sum = 0, last = 0, id = 1;
	for (int i = 0; i < 32; ++i) {
		last = sum;
		sum += get(r + 1, i) - get(l, i);
		if (sum >= K) {id = i; break; }
	}
	K -= last;
	int L = get(l, id);
	--l; // (l, r]
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if (get(mid + 1, id) - L >= K) r = mid;
		else l = mid;
	}
	return r;
}

int main() {
	C[0][0] = 1;
	for (int i = 1; i < 33; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d%d%d", &l, &r, &K);
		if (l == 0) ++l, --K;
		if (r == 0) --r, --K;
		printf("%d\n", solve());
	}
	return 0;
}