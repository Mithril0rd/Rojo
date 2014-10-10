#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_N = 100027;
const int MAX_M = 11;

typedef pair<int,string> pii;

int n;
char str[MAX_N], a[MAX_M][MAX_M];
int len[MAX_M], dp[MAX_N][MAX_M];
pii ans[MAX_M];

void Clear() {
	memset(dp, 0, sizeof dp);
	for (int i = 0; i < MAX_M; ++i) ans[i] = make_pair(0,"");
}

int get(char *s1, char *s2, int l1, int l2) {
	for (int i = 1; i <= l2; ++i) dp[0][i] = i;
	for (int i = 1; i <= l1; ++i) {
		for (int j = 1; j <= l2; ++j) {
			dp[i][j] = min(dp[i - 1][j] + 1, min(dp[i - 1][j - 1] + !(s1[i - 1] == s2[j - 1]), dp[i][j - 1] + 1));
		}
	}
	int now = (int)1e5;
	for (int i = 0; i <= l1; ++i) now = min(now, dp[i][l2]);
	return now;
}

int main() {
	while (1 == scanf("%s", str)) {
		Clear();
		int Len = (int)strlen(str), add = min(Len, 11);
		for (int i = 0; i < add; ++i) str[i + Len] = str[i];
		str[add + Len] = '\0';
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%s", a[i]);
			len[i] = (int) strlen(a[i]);
		}
		if (Len < 11) {
			for (int i = 0; i < n; ++i) {
				int now = (int)1e5;
				for (int j = 0; j < Len; ++j) {
					now = min(now, get(str + j, a[i], Len, len[i]));
				}
				ans[i] = make_pair(now, a[i]);
			}
		} else {
			for (int i = 0; i < n; ++i) {
				ans[i] = make_pair(get(str, a[i], Len + add, len[i]), a[i]);
			}
		}
		sort(ans, ans + n);
		printf("%s %d\n", ans[0].second.c_str(), ans[0].first);
	}
	return 0;
}