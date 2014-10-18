#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 10007 * 2;

struct SAM {
	int id[MAX_N];
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
		id[np] = val[last] + 1;
		while (p && !c[k][p]) c[k][p] = np, p = fa[p];
		if (!p) fa[np] = 1;
		else {
			int q = c[k][p];
			if (val[q] == val[p] + 1) fa[np] = q;
			else {
				int nq = newNode(val[p] + 1);
				for (int i = 0; i < 26; ++i) c[i][nq] = c[i][q];
				fa[nq] = fa[q]; id[nq] = id[np];
				fa[q] = fa[np] = nq;
				while (p && c[k][p] == q) c[k][p] = nq, p = fa[p];
			}
		}
		last = np;
	}
	inline int add(int k) {
		extend(k);
		return 0;
	}
	inline void init() {
		tot = 0;
		last = newNode(0);
	}
} suf;

int n;
char str[MAX_N];

int main() {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%s", str);
		int len = (int) strlen(str);
		for (int i = 0; i < len; ++i) str[i + len] = str[i];
		suf.init();
		for (int i = 0; i < len * 2; ++i) suf.add(str[i] - 'a');
		int j = 1;
		for (int i = 0; i < len; ++i) {
			for (int k = 0; k < 26; ++k) {
				if (suf.c[k][j]) {
					j = suf.c[k][j];
					break;
				}
			}
		} 
		printf("%d\n", suf.val[j] - len + 1);
	}
	return 0;
}