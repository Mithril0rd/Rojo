#include <iostream>

using namespace std;

const int MAXM = 20;
const int MAXN = 60;

long double dp[1 << MAXM];
int cnt[1 << MAXM];
bool marked[1 << MAXM];
string s[MAXN];
long long coef[MAXM + 10][MAXM + 10];

int main() {
	int n;
	cin >> n;
	if (n == 1) {
		cout << 0 << endl;
		return 0;
	}
	for (int i = 0; i < n; i++)
		cin >> s[i];
	int m = s[0].length();
	int mMask = 1 << m;
	long double ans = 0;
	for (int j = mMask - 2; j >= 0; j--)
		cnt[j] = __builtin_popcount(j);
	coef[0][0] = 1;
	for (int i = 1; i <= m; i++) {
		coef[i][0] = coef[i][i] = 1;
		for (int j = 1; j < i; j++)
			coef[i][j] = coef[i - 1][j] + coef[i - 1][j - 1];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < mMask - 1; j++)
			marked[j] = false;
		for (int j = 0; j < n; j++) {
			if (i == j)
				continue;
			int tmp = 0;
			for (int k = 0; k < m; k++)
				if (s[i][k] == s[j][k])
					tmp |= 1 << k;
			marked[tmp] = true;
		}
		marked[0] = true;
		for (int t = 0; t < m; t++)
			for (int j = 0; j < mMask; j++)
				marked[j] |= marked[j | (1 << t)];
		ans += m;
		for (int i = 0; i < mMask - 1; i++)
			if (!marked[i])
				ans -= 1.0 / coef[m][cnt[i]];
	}
	ans /= n;
	cout.precision(12);
	cout << fixed << ans << endl;
	return 0;
}