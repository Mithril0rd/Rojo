#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 250007 * 2;

struct SAM {
	int val[MAX_N], fa[MAX_N], c[26][MAX_N];
	int tot, last;
	inline int newNode(int step) {
		val[++tot] = step;
		fa[tot] = 0;
		for (int i = 0; i < 26; ++i) c[i][tot] = 0;
		return tot;
	}
	inline void extend(int k) {
		int p = last;
		int np = newNode(val[last] + 1);
		while (p && !c[k][p]) c[k][p] = np, p = fa[p];
		if (!p) fa[np] = 1;
		else {
			int q = c[k][p];
			if (val[q] == val[p] + 1) fa[np] = q;
			else {
				int nq = newNode(val[p] + 1);
				for (int i = 0; i < 26; ++i) c[i][nq] = c[i][q];
				fa[nq] = fa[q];
				fa[q] = fa[np] = nq;
				while (p && c[k][p] == q) c[k][p] = nq, p = fa[p];
			}
		}
		last = np;
	}
	inline int add(int k) {
		extend(k);
	}
	inline void init() {
		tot = 0;
		last = newNode(0);
	}
} suf;

char s1[MAX_N], s2[MAX_N];

int main() {
	scanf("%s%s", s1, s2);
	suf.init();
	int len1 = (int) strlen(s1), len2 = (int) strlen(s2);
	for (int i = 0; i < len1; ++i) suf.add(s1[i] - 'a');
	int get = 0, ans = 0, j = 1;
	for (int i = 0; i < len2; ++i) {
		if (suf.c[s2[i] - 'a'][j]) {
			++ans;
			j = suf.c[s2[i] - 'a'][j];
		} else {
			while (j && !suf.c[s2[i] - 'a'][j]) j = suf.fa[j];
			if (j) {
				ans = suf.val[j] + 1;
				j = suf.c[s2[i] - 'a'][j];
			} else {
				ans = 0;
				j = 1;
			}
		}
		get = max(ans, get);
	}
	printf("%d\n", get);
	return 0;
}