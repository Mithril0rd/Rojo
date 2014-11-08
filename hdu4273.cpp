#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 310;
const double EPS = 1e-8;
const double PI = acos(-1.0);

struct Point
{
	double x, y, z;
	Point() {}
	Point(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
	Point operator +(const Point p1)
	{
		return Point(x+p1.x,y+p1.y,z+p1.z);
	}
	friend Point operator - (const Point &x, const Point &y)
	{
		return Point(x.x - y.x, x.y - y.y, x.z - y.z);
	}
	Point operator *(double d)
	{
		return Point(x*d, y*d, z*d);
	}
	friend Point operator * (const Point &x, const Point &y)
	{
		return Point(x.y*y.z-x.z*y.y, x.z*y.x-x.x*y.z, x.x*y.y-x.y*y.x);
	}
	Point operator / (double d)
	{
		return Point(x/d, y/d, z/d);
	}
	friend double operator ^ (const Point &x, const Point &y)
	{
		return x.x*y.x+x.y*y.y+x.z*y.z;
	}
};

struct _3DCH
{
	struct fac
	{
		int a, b, c;
		bool ok;
	};
	int n;
	Point P[MAXN];

	int cnt;
	fac F[MAXN*8];

	int to[MAXN][MAXN];

	double vlen(Point a)
	{
		return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
	}
	double area(Point a, Point b, Point c)
	{
		return vlen((b-a)*(c-a));
	}
	double volume(Point a, Point b, Point c, Point d)
	{
		return (b-a)*(c-a)^(d-a);
	}
	double Pointof(Point &p, fac &f)
	{
		Point m = P[f.b]-P[f.a], n = P[f.c]-P[f.a], t = p-P[f.a];
		return (m * n) ^ t;
	}

	void deal(int p, int a, int b)
	{
		int f = to[a][b];
		fac add;
		if (F[f].ok)
		{
			if (Pointof(P[p], F[f]) > EPS)
				dfs(p, f);
			else
			{
				add.a = b, add.b = a, add.c = p, add.ok = 1;
				to[p][b] = to[a][p] = to[b][a] = cnt;
				F[cnt++] = add;
			}
		}
	}
	void dfs(int p, int cur)
	{
		F[cur].ok = 0;
		deal(p, F[cur].b, F[cur].a);
		deal(p, F[cur].c, F[cur].b);
		deal(p, F[cur].a, F[cur].c);
	}

	bool same(int s, int t)
	{
		Point &a = P[F[s].a], &b = P[F[s].b], &c = P[F[s].c];
		return fabs(volume(a, b, c, P[F[t].a])) < EPS && fabs(volume(a, b, c, P[F[t].b])) < EPS && fabs(volume(a, b, c, P[F[t].c])) < EPS;
	}
	void construct()
	{
		cnt = 0;
		for (int i = 1; i < n; i++)
		{
			if (vlen(P[0] - P[i]) > EPS)
			{
				swap(P[1], P[i]);
				break;
			}
		}
		for (int i = 2; i < n; i++)
		{
			if (vlen((P[0] - P[1]) * (P[1] - P[i])) > EPS)
			{
				swap(P[2], P[i]);
				break;
			}
		}
		for (int i = 3; i < n; i++)
		{
			if (fabs((P[0] - P[1]) * (P[1] - P[2]) ^ (P[0] - P[i])) > EPS)
			{
				swap(P[3], P[i]);
				break;
			}
		}
		fac add;
		for (int i = 0; i < 4; i++)
		{
			add.a = (i+1)%4, add.b = (i+2)%4, add.c = (i+3)%4, add.ok = 1;
			if (Pointof(P[i], add) > 0)
				swap(add.b, add.c);
			to[add.a][add.b] = to[add.b][add.c] = to[add.c][add.a] = cnt;
			F[cnt++] = add;
		}

		for (int i = 4; i < n; i++)
		{
			for (int j = 0; j < cnt; j++)
			{
				if (F[j].ok && Pointof(P[i], F[j]) > EPS)
				{
					dfs(i, j);
					break;
				}
			}
		}
		int tmp = cnt;
		cnt = 0;
		for (int i = 0; i < tmp; i++)
		{
			if (F[i].ok)
			{
				F[cnt++] = F[i];
			}
		}
	}
	double area()
	{
		double ret = 0.0;
		for (int i = 0; i < cnt; i++)
		{
			ret += area(P[F[i].a], P[F[i].b], P[F[i].c]);
		}
		return ret / 2.0;
	}
	double volume()
	{
		Point O(0, 0, 0);
		double ret = 0.0;
		for (int i = 0; i < cnt; i++)
		{
			ret += volume(O, P[F[i].a], P[F[i].b], P[F[i].c]);
		}
		return fabs(ret / 6.0);
	}
	int facetCnt_tri()
	{
		return cnt;
	}
	int facetCnt()
	{
		int ans = 0;
		for (int i = 0; i < cnt; i++)
		{
			bool nb = 1;
			for (int j = 0; j < i; j++)
			{
				if (same(i, j))
				{
					nb = 0;
					break;
				}
			}
			ans += nb;
		}
		return ans;
	}
	Point barycenter() //三维凸包重心
	{
		Point ans(0, 0, 0), o(0, 0, 0);
		double all = 0;
		for(int i = 0; i < cnt;  ++i)
		{
			double vol = volume(o, P[F[i].a], P[F[i].b], P[F[i].c]);
			ans = ans + ( o + P[F[i].a] + P[F[i].b] + P[F[i].c])/4.0 * vol;
			all += vol;
		}
		ans = ans/all;
		return ans;
	}
	double ptoface(Point p, int i)//点到面的距离
	{
		return fabs(volume( P[F[i].a], P[F[i].b], P[F[i].c],p)
			/vlen((P[F[i].b] - P[F[i].a])*(P[F[i].c] - P[F[i].a])));
	}
};

int n;
_3DCH hull;

int main() {
	while (1 == scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf%lf", &hull.P[i].x, &hull.P[i].y, &hull.P[i].z);
		}
		hull.n = n;
		hull.construct();
		Point cent = hull.barycenter();
		int m = hull.facetCnt_tri();
		double ans1 = 1000000.0;
	//	printf("%lf %lf %lf\n", cent.x, cent.y, cent.z);
		for (int i = 0; i < m; ++i) {
			ans1 = min(ans1, hull.ptoface(cent, i));
		}
		printf("%.3f\n", ans1);
	}
	return 0;
}