#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 16;
const int inf = 10000000;
char mp[N][N];
int dis[N][N], dep[N][N];
int n, m, cnt, cnt2;
int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
struct point {
    int x, y;
    point (int _x =  0, int _y = 0) {
        x = _x; y = _y;
    }
}pe[N];

void bfs (point s) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m;  ++j) {
            dis[i][j] = inf;
        }
    }
    dis[s.x][s.y] = 0;
    queue<point>q;
    q.push (s);
    while (!q.empty  ()) {
        point u = q.front (); q.pop();
        for (int i = 0; i < 4; ++i) {
            int x = u.x + dx[i];
            int y = u.y + dy[i];
            if (x <0 || y < 0 || x >= n || y >= m || mp[x][y] == 'D') continue;
            if (dis[x][y] > dis[u.x][u.y] + 1) {
                dis[x][y] = dis[u.x][u.y] + 1;
                q.push (point (x,y));
            }
        }
    }
}

int dp[1<<N][N], Max;

int dfs (int s, int pos) {
    if ((s& ( (1<<cnt2) - 1)) ==  ((1<<cnt2) - 1)){
         return dp[s][pos] = 0;
    }
    if (dp[s][pos] >=0) return dp[s][pos];
    dp[s][pos] = inf;
    for (int i = 0; i < cnt; ++i) {
        if (s&(1<<i)) continue;
        int temp = dfs (s|(1<<i), i);
        if(temp  >= inf)  continue;
        if (mp[pe[i].x][pe[i].y] == 'G') {
            dp[s][pos] = min (dp[s][pos], dep[pos][i]);
        }else {
            dp[s][pos] = min (dp[s][pos], dep[pos][i] + temp);
        }
    }
    if (dp[s][pos] > Max) dp[s][pos] = inf;
    return dp[s][pos];
}
int solve () {
    int l = -1, r = 15 * 15 * 20;
    while (l + 1 < r) {
        Max = (l + r) / 2;
        memset (dp, -1, sizeof(dp));
        int ans = dfs (1, 0);
        if (ans  < inf) {
             r = Max;
        }
        else l = Max;
    }
    return r;
}
int main () {
    while (scanf ("%d%d", &n, &m), n + m) {
        cnt = 0;
        int start = -1;
        for (int i = 0; i < n; ++i) {
            scanf ("%s", mp[i]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mp[i][j] == 'F') {
                    pe[cnt++] = point (i, j);
                    start = 0;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mp[i][j] == 'Y') {
                    pe[cnt++] = point (i, j);
                }
            }
        }
        cnt2 = cnt;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mp[i][j] == 'G') {
                    pe[cnt++] = point (i, j);
                }
            }
        }
        int lag = 0;
       // cout << cnt << endl;
        for (int i = 0; i < cnt; ++i) {
            dep[i][i] = 0;
            for (int j = i + 1; j < cnt; ++j) {
                bfs (pe[i]);
                dep[i][j] = dep[j][i] =
                dis[pe[j].x][pe[j].y];
                if (i == 0 && dep[i][j] == inf && mp[pe[j].x][pe[j].y] == 'Y')  lag  = 1;
            }
        }
        if (lag || start < 0) {
            puts ("-1");
            continue;
        }
        int ans = solve ();
        printf ("%d\n", ans);
    }
    return 0;
}

