#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_N = 10007;
const double eps = 1e-6;

int n;
vector<int> Edge[MAX_N];
double K[MAX_N], E[MAX_N];
double A[MAX_N], B[MAX_N], C[MAX_N];

void Clear() {
	for (int i = 1; i <= n; ++i) Edge[i].clear();
	memset(A, 0, sizeof A);
	memset(B, 0, sizeof B);
	memset(C, 0, sizeof C);
}

bool dfs(int u, int fa) {
	int m = Edge[u].size();
	A[u] = K[u];
	B[u] = (1.0 - K[u] - E[u]) / m;
	C[u] = 1 - K[u] - E[u];
	double now = 0;
	for (int i = 0; i < m; ++i) {
		int v = Edge[u][i];
		if (v == fa) continue;
		if (!dfs(v, u)) return false;	
		A[u] += (1 - K[u] - E[u]) / m * A[v];
		C[u] += (1 - K[u] - E[u]) / m * C[v];
		now += (1 - K[u] - E[u]) / m * B[v];
	}
	if (fabs(now - 1) < eps) return false;
	A[u] /= (1. - now), B[u] /= (1. - now), C[u] /= (1. - now);
	return true;
}

int main() {
	int T;
	scanf("%d", &T);
	int cas = 0;
	while (T-- > 0) {
		scanf("%d", &n);
		Clear();
		for (int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			Edge[u].push_back(v);
			Edge[v].push_back(u);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%lf%lf", &K[i], &E[i]);
			K[i] /= 100, E[i] /= 100;
		}
		bool f = dfs(1, -1);
		printf("Case %d: \n", ++cas);
		if (f && !(fabs(A[1] - 1) < eps)) {
			printf("%.6f\n", C[1] / (1. - A[1]));
		} else puts("impossible");
	}
	return 0;
}