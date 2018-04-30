#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 100005
using namespace std;
typedef long long LL;
int n,m,k,tot=0,c[MAXN];
int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';c=getchar();
    }
    return x*f;
}
struct Node
{
    int r,a,f;
    Node(int r=0,int a=0,int f=0):r(r),a(a),f(f){}
    bool operator < (const Node& x) const
    {return a<x.a;}
}data[400005];
int lowbit(int x){return x&-x;}
void add(int pos,int x)
{
    while(pos<=MAXN)
    {
        c[pos]+=x;
        pos+=lowbit(pos);
    }
}
int solve(int sum)
{
    int x=0,now=0;
    for(int i=(1<<20);i;i>>=1)
    if(x+i<=MAXN&&now+c[x+i]<sum)
    now+=c[x+i],x+=i;
    return x+1;
}
int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++)
    {
        int r=read(),a1=read(),a2=read();
        data[++tot]=Node(r,a1,1);
        data[++tot]=Node(r,a2,-1);
        if(a1>a2)
        {
            data[++tot]=Node(r,-m,1);
            data[++tot]=Node(r,m,-1);
        }
    }
    sort(data+1,data+1+tot);
    LL ans=0;int cnt=0;
    for(int i=1;i<tot;i++)
    {
        add(data[i].r,data[i].f);
        cnt+=data[i].f;
        if(cnt-k+1<=0)continue;
        int t=solve(cnt-k+1);
        ans+=1LL*t*t*(data[i+1].a-data[i].a);
    }
    printf("%lld\n",ans);
    return 0;
}
