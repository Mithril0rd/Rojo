#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

const int MAX_N = 200007;

struct Card {
	int h, w, t;
	Card () {
		
	}
	Card(int _h, int _w, int _t) {
		h = _h, w = _w, t = _t;
	}
	bool operator < (const Card &rhs) const {
		return h < rhs.h || h == rhs.h && w < rhs.w || h == rhs.h && w == rhs.w && t > rhs.t;
	}
};

int n;
Card a[MAX_N];
multiset<int> s;

void Clear() {
	s.clear();
	memset(a, 0, sizeof a);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		Clear();
		scanf("%d", &n);
		for (int i = 0; i < n << 1; ++i) {
			a[i].t = 1;
			if (i < n) a[i].t = 0;
			scanf("%d%d", &a[i].h, &a[i].w);
		}
		sort(a, a + n * 2);
		int ans = 0;
		for (int i = 0; i < n << 1; ++i) {
			if (a[i].t) s.insert(a[i].w);
			else {
				multiset<int>::iterator it = s.upper_bound(a[i].w);
				if (it != s.begin()) {
					++ans;
					s.erase(--it);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}