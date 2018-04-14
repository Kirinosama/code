#include<cmath>  
#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
using namespace std;  
#define ll long long  
const int N=300050;  
ll n,m,cnt,cn,lim;  
ll root[N],w[N*35],son[N*35][2],sum[N*35],to[N];  
struct pp {ll pos,v;}e[N*2];  
bool cmp(pp u,pp v) {return u.pos<v.pos;}  
void pushup(ll x)  
{  
    w[x]=w[son[x][0]]+w[son[x][1]];  
    sum[x]=sum[son[x][0]]+sum[son[x][1]];  
}  
void addnew(ll x,ll &y,ll l,ll r,ll v)  
{  
    y=++cn;  
    if(l==r)  
    {  
        if(v>0) w[y]=w[x]+1;  
        else w[y]=w[x]-1;  
        sum[y]=sum[x]+v;  
        return;  
    }  
    son[y][0]=son[x][0];  
    son[y][1]=son[x][1];  
    ll mid=(l+r)>>1;  
    if(abs(v)<=mid) addnew(son[x][0],son[y][0],l,mid,v);  
    else addnew(son[x][1],son[y][1],mid+1,r,v);  
    pushup(y);  
}  
ll check(ll R,ll k)  
{  
    ll x=root[R],l=1,r=lim,ans=0;  
    if(w[x]<=k)  
    {  
        ans+=sum[x];  
        return ans;  
    }  
    while(l<r)  
    {  
        ll mid=(l+r)>>1;  
        if(w[son[x][0]]>=k)  
        {  
            r=mid;  
            x=son[x][0];  
        }  
        else  
        {  
            l=mid+1;  
            k-=w[son[x][0]];  
            ans+=sum[son[x][0]];  
            x=son[x][1];  
        }  
    }  
    if(k) ans+=l*k;  
    return ans;  
}  
int main()  
{  
    scanf("%lld%lld",&n,&m);  
    ll x,y,p,a,b,c;  
    for(ll i=1;i<=n;i++)  
    {  
        scanf("%lld%lld%lld",&x,&y,&p);  
        e[++cnt].pos=x,e[cnt].v=p;  
        e[++cnt].pos=y+1,e[cnt].v=-p;  
        lim=max(lim,p);  
    }  
    sort(e+1,e+cnt+1,cmp);  
    ll now,pre=1;  
    for(ll i=1;i<=cnt;i++) addnew(root[i-1],root[i],1,lim,e[i].v);  
    for(ll i=cnt;i>=1;i--)  
    if(e[i].pos!=e[i+1].pos) to[e[i].pos]=i;  
    for(ll i=1;i<=n;i++)  
    if(!to[i]) to[i]=to[i-1];  
    for(ll i=1;i<=m;i++)  
    {  
        scanf("%lld%lld%lld%lld",&x,&a,&b,&c);  
        a=(a*pre+b)%c+1;  
        pre=check(to[x],a);  
        printf("%lld\n",pre);  
    }  
}  
