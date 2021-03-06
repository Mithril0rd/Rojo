#include <cstdio>
#include <cstring>

const int MAX_N = 200007;

unsigned a[32][MAX_N / 32], b[32][MAX_N / 32];
char aa[MAX_N], bb[MAX_N];
int n, m, h[1 << 16];
int l, r, q, len;

inline int H(const unsigned &x) {
	return h[x >> 16] + h[x & ((1 << 16) - 1)];
}

int main() {
	gets(aa); gets(bb);
	n = strlen(aa); m = strlen(bb);
	for(int i = 0; i < 32; ++i)
		for(int j = 0; i + j < n; ++j)
			if(aa[i + j] == '1')
				a[i][j >> 5] |= (1U << (j & 31));
		
	for(int i = 0; i < 32; ++i)
		for(int j = 0; i + j < m; ++j)
			if(bb[i + j] == '1')
				b[i][j >> 5] |= (1U << (j & 31));
	
	for(int i = 1; i < 1 << 16; ++i)
		h[i] = h[i >> 1] + (i & 1);
	scanf("%d", &q);
	while(q --> 0) {
		scanf("%d%d%d", &l, &r, &len);
		int ans = 0;
		unsigned * lb = a[l & 31], * rb = b[r & 31];
		lb += l >> 5; rb += r >> 5;
		while(len >= 32) {
			ans += H(*lb++ ^ *rb++);
			len -= 32;
		}
		ans += H((*lb ^ *rb) & ((1U << len) - 1));
		printf("%d\n", ans);
	}
	return 0;
}