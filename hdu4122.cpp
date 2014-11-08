#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

const int MAX_M = 2507;
const int MAX_N = 100007;

const char Mon[13][5] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const int day[13] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Node {
    long long Time, R;
    Node () {}
    Node (long long _Time, long long _R) {
        Time = _Time, R = _R;
    }
};

struct QQ {
    long long cost, Time;
    QQ () {}
    QQ (long long _cost, long long _Time) {
        cost = _cost, Time = _Time;
    }
};

int n, m;
Node ord[MAX_M];
QQ Q[MAX_N * 10];

bool isLeap(int x) {
    return (x % 4 == 0 && x % 100 != 0) || (x % 400 == 0);
}

int get(int y, char *m, int d, int h) {
    int ans = 0;
    for (int i = 2000; i < y; ++i) {
        if (isLeap(i)) ans += 366;
        else ans += 365;
    }
    int now = 0;
    for (int i = 0; i < 12; ++i) {
        if (strcmp(m, Mon[i]) == 0) {
            now = i;
            break;
        }
    }
    for (int i = 0; i < now; ++i) {
        ans += day[i];
    }
    if (isLeap(y) && now >  1) ++ans;
    ans += d - 1;
    return ans * 24 + h;
}

int main() {
    while (2 == scanf("%d%d", &n, &m), n + m) {
        for (int i = 1; i <= n; ++i) {
            char mona[5];
            int day, year, h, R;
            scanf("%s%d%d%d%d", mona, &day, &year, &h, &R);
            ord[i] = Node(get(year, mona, day, h), R);
        }
        memset(Q, 0, sizeof Q);
        int T, S;
        scanf("%d%d", &T, &S);
        int top = 0, tail = 0, p = 1;
        unsigned long long sum = 0;
        for (int i = 0; i < m; ++i) {
            long long Z;
            scanf("%I64d", &Z);
            while (top < tail && Q[tail - 1].cost + (i - Q[tail - 1].Time) * S >= Z) --tail;
            Q[tail++] = QQ(Z, i);
            while (top < tail && Q[top].Time + T < i) ++top;
            while (p <= n && i == ord[p].Time) {
                sum += min (Z, Q[top].cost + S * (i - Q[top].Time)) * ord[p].R;
                p++;
            }
        }
        cout << sum  <<endl;
    }
    return 0;
}

