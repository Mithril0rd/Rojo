#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define LL __int64

const int maxn = 500000 + 10;
bool vis[maxn];
int pri[88888], pnum, mu[maxn], cnt[maxn];
LL d[20][maxn];

void Mobius(int n) {
    pnum = 0;
    vis[1] = mu[1] = 1;
    for(int i = 1;i <= n; i++)  mu[i] = 1;
    for(int i = 2;i <= n; i++) {
        if(!vis[i]) {
            for(int j = i;j <= n;j += i) {
                vis[j] = 1;
                mu[j] *= -1;
                if((j/i) % i == 0)  mu[j] = 0;
                int t = j;
                while(t % i == 0) t /= i, cnt[j]++;
            }
        }
    }
}

void init(int n) {
    Mobius(n);
    for(int i = 1;i <= n; i++) {
        for(int j = i;j <= n;j += i)
            d[cnt[i]][j] += mu[j/i];
    }
    for(int i = 1;i <= 18; i++)
        for(int j = 1;j <= n; j++)
            d[i][j] += d[i-1][j];
    for(int i = 0;i <= 18; i++)
        for(int j = 1;j <= n; j++)
            d[i][j] += d[i][j-1];
}

int main() {
    init(500000);
    int t, n, m, P;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &m, &P);
        if(n > m)   swap(n, m);
        P = min(18, P);
        LL ans = 0;
        for(int i = 1;i <= n; i++) {
            int tmp1 = n/i, tmp2 = m/i;
            int next = min(n/tmp1, m/tmp2);
            ans += (LL)(n/i)*(m/i)*(d[P][next] - d[P][i-1]);
            i = next;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
