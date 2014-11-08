#include <cstdio>
#include <cstring>

const int MAX_N = 2007;
const double eps = 1e-8;

int n, m, k;
double p1, p2, p3, p4, p21, p31, p41;
double dp[MAX_N][MAX_N], c[MAX_N];

inline double dcmp(const double &d) {
    return d < -eps ? -1 : d > eps;
}

int main() {
    while(~scanf("%d%d%d%lf%lf%lf%lf",&n,&m,&k,&p1,&p2,&p3,&p4)) {
        if(dcmp(p3 - 1) == 0 || dcmp(p4) == 0) {
            puts("0.00000");
            continue;
        }
        dp[1][1] = p4 / (1 - p1 - p2);
        c[1] = dp[1][1];
        p21 = p2 / (1 - p1);
        p31 = p3 / (1 - p1);
        p41 = p4 / (1 - p1);
        for(int i = 2 ; i <= n ; ++i) {
            double pp = 1;
            double tt = 0;
            for(int j = 2; j <= k && j <= i; ++j) {
                pp *= p21;
                tt *= p21;
                tt += c[j - 1] * p31 + p41;
            }
            for(int j = k + 1; j <= i; ++j) {
                pp *= p21;
                tt *= p21;
                tt += c[j - 1] * p31 ;
            }
            dp[i][i] = (pp * p41 + tt) / (1 - p21 * pp);
            dp[i][1] = p21 * dp[i][i] + p41;
            c[i] = dp[i][i];
            for(int j = 2; j <= k && j < i; ++j) {
                dp[i][j] = dp[i][j - 1] * p21 + c[j - 1] * p31 + p41;
                c[j - 1] = dp[i][j - 1];
            }
            for(int j = k + 1; j < i; ++j) {
                dp[i][j] = dp[i][j - 1] * p21 + c[j - 1] * p31;
                c[j - 1] = dp[i][j - 1];
            }
            c[i - 1] = dp[i][i - 1];
        }
        printf("%.5f\n",dp[n][m]);
    }
    return 0;
}