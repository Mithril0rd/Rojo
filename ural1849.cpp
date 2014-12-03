#include<cstdio>
#include<cstring>
#include <vector>
#include <queue>
#include<algorithm>

using namespace std;

struct Point {
    int x, y;
    Point (int _x = 0, int _y = 0) {
        x = _x, y = _y;
    }
    int operator *(Point a) { return x * a.x + y * a.y; }
    bool operator < (const Point &b) const {
        if (x == b.x) return y > b.y;
        return x < b.x;
    }
};

int n;
Point p[10007];
vector<Point> v[27][27];

int cal(Point sp, Point vp) {
    vector<Point> &cP = v[vp.x + 10][vp.y + 10];
    int l = -1, r = cP.size();
    if (r == 0) return 0;
    Point nv = Point(vp.y, -vp.x);
    Point np = Point(sp * nv, sp * vp);
    if (np.x < cP[0].x || np.x > cP[r - 1].x) return 0;
    while (l + 1 < r) {
        int mid = (r + l) >> 1;
        if (cP[mid].x < np.x) l = mid;
        else r = mid;
    }
    if (r == cP.size() || np.x < cP[r].x) return 0;
    int cS = r;
    r = cP.size();
    while (l + 1 < r) {
        int mid = (r + l) >> 1;
        if (cP[mid].x > np.x) r = mid;
        else l = mid;
    }
    int cT = l;
    l = cS - 1,r = cT + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (cP[mid].y < np.y) r = mid;
        else l = mid;
    }
    return l - cS + 1;
}


void update(int &r, int &x, int v, int y) {
    if (v > r) r = v, x = -1;
    if (v == r && y > x) x = y;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
    for (int i = -10; i < 11; ++i) {
        for (int j = -10; j < 11; ++j) {
            if (0 == j && i == 0) continue;
            Point slop1 = Point(i, j), slop2 = Point(j, -i);
            vector<Point> &u = v[i + 10][j + 10];
            u.clear();
            for (int k = 0; k < n; ++k) {
                u.push_back(Point(slop2 * p[k], slop1 * p[k]));
            }
            sort(u.begin(), u.end());
        }
    }
    int ax, bx, ay, by, avx, bvx, avy, bvy;
    int x, y, vx, vy;
    int q;
    scanf("%d", &q);
    scanf("%d%d%d%d", &x, &y, &vx, &vy);
    scanf("%d%d%d%d%d%d%d%d", &ax, &bx, &ay, &by, &avx, &bvx, &avy, &bvy);
    int Res = -1, Id = -1;
    update(Res, Id, cal(Point(x, y), Point(vx, vy)), 1);
    for (int i = 2; i <= q; ++i) {
        x = (ax * (x + 10000) + bx) % 20001 - 10000;
        y = (ay * (y + 10000) + by) % 20001 - 10000;
        vx = (avx * (vx + 10) + bvx) % 21 - 10;
        vy = (avy * (vy + 10) + bvy) % 21 - 10;
        update(Res, Id, cal(Point(x, y),Point(vx, vy)), i);
    }
    printf("%d %d\n",Id, Res);
    return 0;
}

