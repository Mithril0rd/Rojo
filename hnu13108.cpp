#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAX_N = 1000000;

struct Trie {
       int next[MAX_N][26], fail[MAX_N], end[MAX_N];
       int L, root;
       int id[MAX_N];
       int newnode() {
              for(int i = 0; i < 26; ++i)
                     next[L][i] = -1;
              id[L] = 0;
              end[L++] = 0;
              return L - 1;
       }
       void init() {
              L = 0;
              root = newnode();
       }
       void insert(char buf[], int val, int ID) {
              int len = strlen(buf);
              int now = root;
              for(int i = 0; i < len; ++i) {
                     if(next[now][buf[i]-'a'] == -1)
					   next[now][buf[i]-'a'] = newnode();
                     now = next[now][buf[i]-'a'];
              }
              end[now] = max(val, end[now]), id[now] = ID;
       }
       void build() {
              queue<int> q;
              fail[root] = root;
              for(int i = 0;i < 26; ++i) {
                     if(next[root][i] == -1)
						next[root][i] = root;
                     else {
                            fail[next[root][i]] = root;
                            q.push(next[root][i]);
                     }
              }
              while(!q.empty()) {
                     int now=q.front();
                     q.pop();
                     for(int i=0;i<26;i++) {
                            if(next[now][i]==-1)
                                   next[now][i]=next[fail[now]][i];
                            else {
								fail[next[now][i]]=next[fail[now]][i];
                                   q.push(next[now][i]);
                            }
                     }
              }
       }
};

int n;
Trie T;
int Len[1007];
long long dp[100007];
char str[100007], temp[307];

void query(char buf[]) {
      int len=strlen(buf);
      int now=T.root;
      dp[0] = 0;
      for(int i=0;i<len;i++) {
             now=T.next[now][buf[i]-'a'];
             int temp=now;
             while(temp!=T.root) {
                if (T.end[temp] != -1) {
                    if (i - Len[T.id[temp]] + 1 >= 0 && ~dp[i - Len[T.id[temp]] + 1])
                        dp[i + 1] = max(dp[i + 1], dp[i - Len[T.id[temp]] + 1] + T.end[temp]);
                 }
                 temp=T.fail[temp];
             }
      }
}

int main() {
    while (1 == scanf("%s", str)) {
        T.init();
        scanf("%d", &n);
        memset(Len, 0, sizeof Len);
        for (int i = 1; i <= n; ++i) {
            int val;
            scanf("%s%d", temp, &val);
            Len[i] = strlen(temp);
            T.insert(temp, val, i);
        }
        T.build();
        memset(dp, -1, sizeof dp);
        query(str);
      //  for (int i = 0; i <= strlen(str); ++i) printf("%d %lld\n", i, dp[i]);
        if (dp[strlen(str)] == -1) puts("0");
        else printf("%lld\n", dp[strlen(str)]);
    }
    return 0;
}

