#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 10010
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define p 3
#define mod 1000000007 
using namespace std;
typedef long long ll;
ll Hash[N<<2],Hash2[N<<2];
ll pow[N];
int a[N];
int n,t;
void pushup(int rt,int m)
{
    ll tmp=m>>1;
    Hash[rt]=(Hash[rt<<1]*pow[tmp]+Hash[rt<<1|1])%mod;
    Hash2[rt]=(Hash2[rt<<1|1]*pow[m-tmp]+Hash2[rt<<1])%mod;
}
void update(int pt,int l,int r,int rt)
{
    if(l==r)
    {
        Hash[rt]=Hash2[rt]=1;
        return;
    }
    int mid=(l+r)>>1;
    if(pt<=mid)update(pt,lson);
    else update(pt,rson);
    pushup(rt,r-l+1);
}
ll query(int L,int R,int l,int r,int rt)
{
    if(L>R)return 0;
    int ans=0;
    if(L==l&&r==R)
    {
        return Hash[rt];
    }
    int mid=(l+r)>>1;
    if(R<=mid)return query(L,R,lson);
    else if(L>mid)return query(L,R,rson);
    else return (query(L,mid,lson)*pow[R-mid]+query(mid+1,R,rson))%mod;
}
ll query2(int L,int R,int l,int r,int rt)
{
    if(L>R)return 0;
    if(L==l&&r==R)
    {
        return Hash2[rt];
    }
    int mid=(l+r)>>1;
    if(R<=mid)return query2(L,R,lson);
    else if(L>mid)return query2(L,R,rson);
    else return (query2(L,mid,lson)+query2(mid+1,R,rson)*pow[mid-L+1])%mod;
}
int main()
{
    freopen("bzoj2124.in","r",stdin);
    scanf("%d",&t);
    pow[1]=p;
    for(int i=2;i<=10000;i++)pow[i]=(pow[i-1]*p)%mod;
    while(t--)
    {
        memset(Hash,0,sizeof(Hash));
        memset(Hash2,0,sizeof(Hash2));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        int flag=0;
        for(int i=1;i<=n;i++)
        {
            ll len=min(a[i]-1,n-a[i]);
            ll tmp1=query(a[i]-len,a[i]-1,1,n,1);
            ll tmp2=query2(a[i]+1,a[i]+len,1,n,1);
            if(tmp1!=tmp2)
            {
                flag=1;break;
            }
            update(a[i],1,n,1);
        }
        if(flag)printf("Y\n");
        else printf("N\n");
    }
}
