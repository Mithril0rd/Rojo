#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 35;

int l, r;
int C[MAX_N][MAX_N];
int digit[MAX_N];

int cal(int x) {
	int n = 0;
	while (x > 0) {
		digit[++n] = x % 2;
		x >>= 1;
	}
	int ans = 0;
	for (int i = 1; i < n; ++i) {
		for (int j = (i + 1) / 2; j < i; ++j) {
			ans += C[i - 1][j];
		}
	}
	int zero = 0;
	for (int i = n - 1; i > 0; --i) {
		if (digit[i] == 1) {
			++zero;
			for (int j = max(0, (n + 1) / 2 - zero); j < i; ++j) 
				ans += C[i - 1][j];
			--zero;
			
		} else ++zero;
	}
	return ans;
}

int main() {
	C[0][0] = 1;
	for (int i = 1; i < MAX_N; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
	while (2 == scanf("%d%d", &l, &r)) {
		int ans = cal(r + 1) - cal(l);
		printf("%d\n", ans);
	}	
	return 0;
}