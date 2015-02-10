#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define lson i<<1
#define rson i<<1|1
#define mid ((l+r)>>1)
typedef __int64 LL;
const int maxn=300005;
const int mod=1e9+9;
int a[maxn],fib[maxn];

struct Node
{
    int f1,f2;//区间第一项和第二项的值
    int sum;
}segtree[maxn<<2];

void init()//斐波那契数列预处理
{
    fib[1]=1;fib[2]=1;
    for(int i=3;i<maxn;i++)
        if((fib[i]=fib[i-1]+fib[i-2])>=mod)
            fib[i]-=mod;
}

int get_fib(int a,int b,int n)
{
    if(n==1) return a;
    if(n==2) return b;
    return ((LL)b*fib[n-1]+(LL)a*fib[n-2])%mod;
}

int get_sum(int a,int b,int n)
{
    int sum=get_fib(a,b,n+2)-b;
    return (sum+mod)%mod;
}
void add_fib(int i,int l,int r,int a,int b)
{
    segtree[i].f1=(segtree[i].f1+a)%mod;
    segtree[i].f2=(segtree[i].f2+b)%mod;
    segtree[i].sum=(segtree[i].sum+get_sum(a,b,r-l+1))%mod;
}

void pushdown(int i,int l,int r)
{
    add_fib(lson,l,mid,segtree[i].f1,segtree[i].f2);
    add_fib(rson,mid+1,r,get_fib(segtree[i].f1,segtree[i].f2,mid+1-l+1)
        ,get_fib(segtree[i].f1,segtree[i].f2,mid-l+3));
    segtree[i].f1=segtree[i].f2=0;
}

void pushup(int i)
{
    segtree[i].sum=(segtree[lson].sum+segtree[rson].sum)%mod;
}

void build(int i,int l,int r)
{
    if(l==r)
    {
        segtree[i].sum=a[l];
        segtree[i].f1=segtree[i].f2=0;
        return ;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(i);
}

void update(int i,int l,int r,int a,int b)
{
    if(a<=l && r<=b)
    {
        add_fib(i,l,r,fib[l-a+1],fib[l-a+2]);
        return ;
    }
    pushdown(i,l,r);
    if(a<=mid) update(lson,l,mid,a,b);
    if(b>mid) update(rson,mid+1,r,a,b);
    pushup(i);
}

int query(int i,int l,int r,int a,int b)
{
    if(a<=l && r<=b) 
        return segtree[i].sum;
    pushdown(i,l,r);
    int ans=0;
    if(a<=mid) ans=(ans+query(lson,l,mid,a,b))%mod;
    if(mid<b) ans=(ans+query(rson,mid+1,r,a,b))%mod;
    return ans;
}

int main()
{
    init();
    int i,n,m,op,l,r;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) scanf("%d",a+i);
    build(1,1,n);
    while(m--)
    {
        scanf("%d%d%d",&op,&l,&r);
        if(op==1) update(1,1,n,l,r);
        if(op==2) printf("%d\n",query(1,1,n,l,r));
    }
    return 0;
}
