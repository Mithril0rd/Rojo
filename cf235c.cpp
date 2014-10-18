#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 1000007 * 2;

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

char str[MAX_N], s[MAX_N];
int c[MAX_N], sa[MAX_N], num[MAX_N];
int Time, vis[MAX_N];

int cal() {
	++Time;
	int ans = 0, j = 1, len = 0;
	int len2 = (int) strlen(s); 
	for (int i = 0; i < len2; ++i) {
		while (j && !suf.c[s[i] - 'a'][j]) j = suf.fa[j];
		if (!j) j = 1, len = 0;
		else {
			len = min(len, suf.val[j]) + 1;
			j = suf.c[s[i] - 'a'][j];
		}
		while (suf.val[suf.fa[j]] >= len2 / 2) len = suf.val[j = suf.fa[j]];
		if (len >= len2 / 2 && vis[j] != Time) {
			vis[j] = Time;
			ans += num[j];
		}
	}
	return ans;
}

int main() {
	scanf("%s", str);
	int len = (int) strlen(str);
	suf.init();
	for (int i = 0; i < len; ++i) suf.add(str[i] - 'a');
	for (int i = 1; i <= suf.tot; ++i) ++c[suf.val[i]];
	for (int i = 1; i <= len; ++i) c[i] += c[i - 1];
	for (int i = 1; i <= suf.tot; ++i) sa[c[suf.val[i]]--] = i;
	int j = 1, k = 0;
	while (true) {
		++num[j];
		if (suf.val[j] == len) break;
		j = suf.c[str[k++] - 'a'][j]; 
	}
	for (int i = suf.tot; i > 0; --i) {
		int id = sa[i];
		num[suf.fa[id]] += num[id];
	} 
	int n;
	scanf("%d", &n);
	while (n-- > 0) {
		scanf("%s", s);
		int len2 = (int) strlen(s);
		for (int i = 0; i < len2; ++i) s[i + len2] = s[i];
		s[2 * len2] = 0;
		int ans = cal();
		printf("%d\n", ans);
	}
	return 0;
}