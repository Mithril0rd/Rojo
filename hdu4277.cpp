#include <cstdio>
#include <cstring>
#include <set>  

using namespace std;

int n;
int a[17];
int sum, x, y, z;  
set<int> s;  

void dfs(int i) {  
    if(i == n)   {  
        if(x && x <= y && x <= z && y <= z && x + y > z)
			s.insert(x << 16 | y);  
        return;  
    }  
    x += a[i]; dfs(i + 1); x -= a[i];  
    y += a[i]; dfs(i + 1); y -= a[i];  
    z += a[i]; dfs(i + 1); z -= a[i];  
}  

int main() {  
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &n);
		sum = x = y = z = 0;
		s.clear();
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			sum += a[i];
		}
		dfs(0);
		int ans = (int) s.size();
		printf("%d\n", ans);;  
    }  
    return 0;  
}  