#include<cstdio>  
#include<cstring>  
const int N=200020;  
struct Nod  
{  
    int fail,nxt[27],deep;  
    int s,pos;  
    void clear()  
    {  
        memset(nxt,0,sizeof(nxt));  
        deep=fail=s=0;  
    }  
}node[N*2];  
  
int size,end;  
bool dlt[N*2];  
int id[N];  
int tot,len;  
  
void init()  
{  
    memset(dlt,0,sizeof(dlt));  
    for(int i=0;i<27;i++) node[0].nxt[i]=1;  
    node[0].deep=-1;  
    node[1].clear();  
    tot=len=end=1;size=2;id[0]=1;  
}  
bool isDlt(int x)  
{  
    return x==0||dlt[node[x].s];  
}  
void addNode(int c,int s)  
{  
    int p=size++;node[p].clear();  
    node[p].s=s;id[len]=p;  
    node[p].deep=node[end].deep+1;  
    node[p].pos=len++;  
    for(;isDlt(node[end].nxt[c]);end=node[end].fail) node[end].nxt[c]=p;  
    int p1=node[end].nxt[c];  
    if(node[p1].deep==node[end].deep+1) node[p].fail=p1;  
    else  
    {  
        int p2=size++;node[p2]=node[p1];node[p1].fail=node[p].fail=p2;  
        node[p2].deep=node[end].deep+1;  
        for(;node[end].nxt[c]==p1;end=node[end].fail) node[end].nxt[c]=p2;  
    }  
    end=p;  
}  
void addString(char *s)  
{  
    for(int i=0;s[i];i++) addNode(s[i]-96,tot++);  
}  
void dltString(int k)  
{  
    for(int i=1;i<=k;i++) dlt[node[id[len-i]].s]=1;  
    end=id[len-1-k];len-=k;  
}  
bool first;  
int dfs(int x,int &l)  
{  
    if(l==0) return node[x].pos;  
    for(int i=0;i<27;i++)  
    {  
        if(i==0&&first){first=0;continue;}  
        if(isDlt(node[x].nxt[i])) continue;  
        l--;  
        return dfs(node[x].nxt[i],l);  
    }  
    return node[x].pos;  
}  
int query(int l)  
{  
    first=1;  
    addNode(0,tot++);  
    int tl=l;  
    int id=dfs(1,tl);  
    dltString(1);  
    l-=tl;  
    return id-l+1;  
}  
char s[N];  
int main()  
{  
    while(scanf("%s",s)!=EOF)  
    {  
        init();  
        addString(s);  
        int n,x,l;  
        scanf("%d",&n);  
        while(n--)  
        {  
            scanf("%d",&x);  
            switch(x)  
            {  
                case 1:scanf("%s",s);addString(s);break;  
                case 2:scanf("%d",&l);printf("%d\n",query(l));break;  
                case 3:scanf("%d",&l);dltString(l);break;  
            }  
        }  
    }  
    return 0;  
}  