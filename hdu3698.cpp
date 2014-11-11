#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define lson id << 1
#define rson lson | 1

const int MAX_N = 5007;
const int INF = 0x7fffffff;

struct Node {
    int l, r, mi, laz;
    Node () {}
    Node (int _l, int _r, int _mi, int _laz) {
        l = _l, r = _r, mi = _mi, laz = _laz;
    }
};

int n, m;
int a[107][MAX_N], f[107][MAX_N];
int dp[107][MAX_N];
Node T[MAX_N << 2];

struct Segment {
    void up(int id) {
        T[id].mi = min(T[lson].mi, T[rson].mi);
    }
    void down(int id) {
        if (T[id].laz != INF) {
            T[lson].mi = min(T[lson].mi, T[id].laz);
            T[rson].mi = min(T[rson].mi, T[id].laz);
            T[lson].laz = min(T[lson].laz, T[id].laz);
            T[rson].laz = min(T[rson].laz, T[id].laz);
            T[id].laz = INF;
        }
    }
    void build(int id, int l, int r) {
        T[id] = Node(l, r, INF, INF);
        if (l == r) return ;
        int mid = (l + r) >> 1;
        build(lson, l, mid), build(rson, mid + 1, r);
        up(id);
    }
    void update(int id, int l, int r, int v) {
        if (l <= T[id].l && T[id].r <= r) {
            T[id].mi = min(T[id].mi, v);
            T[id].laz = min(T[id].laz, v);
            return ;
        }
        int mid =(T[id].l + T[id].r) >> 1;
        down(id);
        if (r <= mid) update(lson, l, r, v);
        else if (l > mid) update(rson, l, r, v);
        else update(lson, l, mid, v), update(rson, mid + 1, r, v);
        up(id);
    }
    int query(int id, int l, int r) {
        if (l <= T[id].l && T[id].r <= r) return T[id].mi;
        int mid = (T[id].l + T[id].r) >> 1;
        down(id);
        if (r <= mid) return query(lson, l, r);
        else if (l > mid) return query(rson, l, r);
        else return min(query(lson, l, mid), query(rson, mid + 1, r));
    }
};

Segment S;

int main() {
    while (2 == scanf("%d%d", &n, &m)) {
        if (0 == n && 0 == m) break;
        memset(T, 0, sizeof T);
        memset(dp, 0, sizeof dp);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &a[i][j]);
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &f[i][j]);
            }
        }
        for (int i = 1; i <= m; ++i) dp[1][i] = a[1][i];
        for (int i = 2; i <= n; ++i) {
            S.build(1, 1, m);
            for (int j = 1; j <= m; ++j)
                S.update(1, max(1, j - f[i - 1][j]), min(m, j + f[i - 1][j]), dp[i - 1][j]);
            for (int j = 1; j <= m; ++j)
                dp[i][j] = S.query(1, max(1, j - f[i][j]), min(m, j + f[i][j])) + a[i][j];
        }

        int ans = INF;
        for (int i = 1; i <= m; ++i) ans = min(ans, dp[n][i]);
        printf("%d\n", ans);

    }
    return 0;
}

