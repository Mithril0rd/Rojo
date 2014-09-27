#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N =13;
const int MAX_M = 1007;
const int MAX_S = 1 << 11;

int n, m;
double a[MAX_N][MAX_M];
double dp[MAX_M][MAX_S];

int main() {
    int T;
    scanf("%d", &T);
    int cas = 0;
    while (T-- > 0) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%lf", &a[i][j]);
            } 
        }
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j < 1 << n; ++j) {
                dp[i][j] = -1.;
            }
        }
        dp[0][0] = 0;
        for (int i = 1; i <= m; ++i) {
            for (int s = 0; s < (1 << n); ++s) {
                if (dp[i - 1][s] == -1) continue;
                int now = s;  
                if (now + 1 == (1 << n)) now = 0;
                for (int j = 0; j < n; ++j) {
                    if ((now >> j & 1) == 0) {
                        dp[i][now | (1 << j)] = max(dp[i][now | (1 << j)], dp[i - 1][s] + a[j + 1][i]);
                    }
                }
            }
        }
        
        double ans = 0;
        for (int i = 0; i < 1 << n; ++i) {
            ans = max(ans, dp[m][i]);
        }
        printf("Case #%d: %.5lf\n", ++cas, ans);
    }
    return 0;
}