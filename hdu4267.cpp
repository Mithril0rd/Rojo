#include <cstdio>
#include <cstring>

const int MAX_N = 50007;
const int MAX_M = 11;

int n;
int v[MAX_N];
int bit[MAX_N][MAX_M][MAX_M];

void add(int i, int j, int k, int v) {
	while (i > 0) {
		bit[i][j][k] += v;
		i -= i & -i;
	}
}

int sum(int i, int j) {
	int s = 0;
	while (i < MAX_N) {
		for (int k = 1; k <= 10; ++k) s += bit[i][k][j % k];
		i += i & -i;
	} 
	return s;
}

int main() {
	while (1 == scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &v[i]);
		}
		memset(bit, 0, sizeof bit);
		int q;
		scanf("%d", &q);
		while (q-- > 0) {
			int typ;
			scanf("%d", &typ);
			if (1 == typ) {
				int a, b, k, c;
				scanf("%d%d%d%d", &a, &b, &k, &c);
				add(b, k, a % k, c);
				add(a - 1, k, a % k, -c);
			} else {
				int a;
				scanf("%d", &a);
				int ans = sum(a, a);
				printf("%d\n", ans + v[a]);
			}
		}
	}
	return 0;
}