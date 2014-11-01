 #include <cstdio>  
#include <cstring>  
#include <algorithm>  

using namespace std;  
 
typedef long long ll;  
  
const int MAX_N = 47;  
  
ll dp[MAX_N][MAX_N][2];   
char bit[MAX_N], num[MAX_N];  
int rec[MAX_N], len;  

ll dfs (int start, int cur, bool ismir, bool limit) {  
    if (cur < 0)  return ismir;  
    if (!limit && dp[start][cur][ismir] != -1)  
        return dp[start][cur][ismir];  
    int end = limit ? bit[cur] - '0' : 9;  
    ll ret = 0;  
    for (int i = 0; i <= end; ++i) {  
        if (i == 0 || i == 1 || i == 8) {  
            rec[cur] = i;  
            if (start == cur && i == 0) {               
                ret += dfs(start - 1, cur - 1, ismir, (limit && (i == end)));  
            } else if (ismir && cur < (start + 1) / 2) { 
                ret += dfs(start, cur - 1, (i == rec[start - cur]), (limit && (i == end)));  
            } else {  
                ret += dfs(start, cur - 1, ismir, (limit && (i == end)));  
            }  
        }  
    }  
    return limit ? ret : dp[start][cur][ismir] = ret;  
}  

bool check() {  
    for (int i = 0; i <= len / 2; ++i) {  
        if (bit[i] != '0' && bit[i] != '1' && bit[i] != '8')  
            return false;  
        if  (bit[i] != bit[len - 1 - i])  
            return false;  
    }  
    return true;  
}  
  
int main() {  
    memset(dp, -1, sizeof(dp)); 
    int T;
    scanf("%d", &T);  
    while (T-- > 0) { 
	    ll ans1, ans2;  
	    scanf("%s", num);  
	    len = strlen(num);  
	    for (int i = 0; i < len; ++i)
	        bit[i] = num[len - 1 - i];  
	    bit[len] = 0;  
	    ans1 = dfs(len - 1, len - 1, 1, 1) - check();  
	    
	    scanf("%s", num);  
	    len = strlen(num);  
	    for (int i = 0; i < len; ++i)
	        bit[i] = num[len - 1 - i];  
	    bit[len] = 0;  
	    ans2 = dfs(len - 1, len - 1, 1, 1); 
	    printf("%lld\n", ans2 - ans1);
    }  
    return 0;  
}  