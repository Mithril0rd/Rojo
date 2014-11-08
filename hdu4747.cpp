#include <cstdio>
#include <cstring> 
#include <map>
#include <algorithm>

using namespace std;

const int MAX_N = 200007;
 
map<int, int >mp;
int g[MAX_N];

struct qs {
    __int64 l, r, sum, add;
    int mx;
} tree[MAX_N << 2];

void pushup(int root) {
    if (tree[root].l == tree[root].r)return;
    tree[root].sum = tree[root << 1].sum + tree[root << 1 | 1].sum;
    tree[root].mx = max(tree[root << 1].mx, tree[root << 1 | 1].mx);
    return;
}

void pushdown(int root) {
    if (tree[root].l == tree[root].r)return;
    if (tree[root].add == -1)return;
    tree[root << 1].add = tree[root << 1 | 1].add = tree[root].add;
    tree[root << 1].mx = tree[root << 1 | 1].mx = tree[root].add;
    tree[root].add = -1;
    tree[root << 1].sum = (tree[root << 1].r - tree[root << 1].l + 1) * tree[root << 1].add;
    tree[root << 1 | 1].sum = (tree[root << 1 | 1].r - tree[root << 1 | 1].l + 1) * tree[root << 1 | 1].add;
    return;
}

void build(int l, int r, int root) {
    tree[root].l = l;
    tree[root].r = r;
    tree[root].sum = 0;
    tree[root].add = -1;
    tree[root].mx = -1;
    if (l == r) {
        tree[root].sum = g[l];
        tree[root].mx = g[l];
        return;
    }
    int mid = l + r >> 1;
    build(l, mid, root << 1);
    build(mid + 1, r, root << 1 | 1);
    pushup(root);
    return;
}

void update(int l, int r, __int64 v, int root) {
    if (tree[root].l >= l && tree[root].r <= r) {
        tree[root].sum = (tree[root].r - tree[root].l + 1) * v;
        tree[root].add = v;
        tree[root].mx = v;
        return;
    }
    pushdown(root);
    int mid = tree[root].l + tree[root].r >> 1;
    if (r <= mid)update(l, r, v, root << 1);
    else if (l > mid)update(l, r, v, root << 1 | 1);
    else {
        update(l, mid, v, root << 1);
        update(mid + 1, r, v, root << 1 | 1);
    }
    pushup(root);
}

int get(int v, int root) {
    if (tree[root].l == tree[root].r) {
        return tree[root].l;
    }
    if (tree[root << 1].mx > v)return get(v, root << 1);
    else return get(v, root << 1 | 1);
}

int i, n, j, tmp, l, r, mid;
int a[MAX_N], f[MAX_N];
__int64 ans;

int main() {
    while (scanf("%d", &n), n) {
        for (i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        mp.clear();
        tmp = 0;
        for (i = 1; i <= n; i++) {
            mp[a[i]] = 1;
            while (mp.find(tmp) != mp.end())tmp++;
            g[i] = tmp;
        }
       
        mp.clear();
        for (i = n; i >= 1; i--) {
            if (mp.find(a[i]) == mp.end())f[i] = n + 1;
            else f[i] = mp[a[i]];
            mp[a[i]] = i;
        }
        
        build(1, n, 1);
        ans = tree[1].sum;
        for (i = 2; i <= n; i++) {
            if (tree[1].mx <= a[i - 1]) l = n + 1;
            else l = get(a[i - 1], 1);
            if (l < f[i - 1] && l <= n)update(l, f[i - 1] - 1, a[i - 1], 1);
            update(1, i - 1, 0, 1);
            ans += tree[1].sum;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}