#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

const int MAX_N = 10007;
const int MAX_Q = 10007;

struct sam {
    int val[MAX_N], fa[MAX_N], c[26][MAX_N];
    int tot, last;
    inline int new_node (int step) {
        val[++tot] = step;
        fa[tot] = 0;
        for (int i = 0; i < 26; i ++) c[i][tot] = 0;
        return tot;
    }
    inline void extend (int k) {
        int p = last;
        int np = new_node(val[last] + 1);
        while (p && !c[k][p]) c[k][p] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else {
            int q = c[k][p];
            if (val[q] == val[p] + 1) fa[np] = q;
            else {
                int nq = new_node(val[p] + 1);
                for (int i = 0; i < 26; i++) c[i][nq] = c[i][q];
                fa[nq] = fa[q]; 
                fa[q] = fa[np] = nq;
                while (c[k][p] == q && p) c[k][p] = nq, p = fa[p]; 
            }
        }
        last = np;
    }
    int add (int k) {
        extend (k);
        return val[last] - val[fa[last]];
    }
    int build (char *s , int len) {
        int ret = 0;
        tot = 0;
        last = new_node (0);
        for (int i = 0; i < len; i++) ret += add(s[i] - 'a');
        return ret;
    }
} suf;

struct query {
    int l, r, ans;
} q[MAX_Q];

int pos[MAX_N];

bool cmp (int i, int j) {
    if (q[i].l == q[j].l) return q[i].r < q[j].r;
    return q[i].l < q[j].l;
}

char s[MAX_N] , s1[MAX_N];

int main () {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%s", s);
		int m;
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) {
			pos[i] = i;
			scanf("%d%d", &q[i].l, &q[i].r);
			--q[i].l, --q[i].r;
		}
		sort(pos + 1, pos + m + 1, cmp);
        int last = 0;
        for (int i = 1; i <= m; i++) {
            int cnt = 0;
            if ( i == 1) {
                int len = 0;
                for (int j = q[pos[i]].l; j <= q[pos[i]].r; j++)
                    s1[len++] = s[j];
                s1[len] = 0;
                cnt = suf.build(s1, len);
            }
            else {
                if (q[pos[i]].l == q[pos[i-1]].l && q[pos[i]].r >= q[pos[i-1]].r) {
                    for (int j = q[pos[i-1]].r + 1; j <= q[pos[i]].r; j++)
                        cnt += suf.add(s[j] - 'a');
                    cnt += last;
                }
                else {
                    int len = 0;
                    for (int j = q[pos[i]].l; j <= q[pos[i]].r; j++)
                        s1[len++] = s[j];
                    s1[len] = 0;
                    cnt = suf.build(s1 , len);
                }
            }
            last = q[pos[i]].ans = cnt;
        }
        for (int i = 1; i <= m; i++) 
			printf ("%d\n", q[i].ans);
    }
    return 0;
}