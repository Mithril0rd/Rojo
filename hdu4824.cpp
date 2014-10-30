#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 1007;

struct Node {
    int t, s;
    Node () {
        
    }
    Node (int _t, int _s) {
        t = _t, s = _s;
    }
};

int n;
int d[MAX_N][MAX_N], dp[MAX_N][MAX_N];
Node a[MAX_N];

int dis(int i, int j) {
    return min(abs(a[i].s - a[j].s), 360 - abs(a[i].s - a[j].s));
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &n);
        a[1] = Node(0, 0);
        for (int i = 2; i <= n + 1; ++i) {
            scanf("%d%d", &a[i].t, &a[i].s);
        }
        for (int i = 1; i <= n + 1; ++i) {
            d[i][i] = 0;
            for (int j = 1; j < i; ++j) {
                d[i][j] = d[j][i] = dis(i, j);
            }
        }
        dp[2][1] = d[2][1];
        for (int i = 3; i <= n + 1; ++i) {
            dp[i][i - 1] = 0x3f3f3f3f;
            for (int j = 1; j < i - 1; ++j) {
                dp[i][i - 1] = min(dp[i][i - 1], dp[i - 1][j] + d[j][i]);
                dp[i][j] = dp[i - 1][j] + d[i][i - 1];
            }
        }
        int ans = 0x3f3f3f3f;
        for (int i = 1; i <= n; ++i) {
            ans = min(ans, dp[n + 1][i] + d[n + 1][i]);
        }
        printf("%d\n", ans + 10 * n + 800 * a[n + 1].t);
    }
    return 0;
}