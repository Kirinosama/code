#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<cstdio>

#define N 200007
#define ll long long
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if (ch=='-') f=-1;ch=getchar();}
    while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*f;
}

int n;
ll a[N],h[N],S,L,mx;

bool check(ll day)
{
    ll ans=0;
    ll now;
    for(int i=1;i<=n;i++)
    {
        now = a[i]*day+h[i];
        if(now>=L) ans+=now;
        if(ans>=S) return true;
    }
    return false;
}
int main()
{
    cin>>n>>S>>L;
    for(int i=1;i<=n;i++) cin>>h[i];
    for(int i=1;i<=n;i++) cin>>a[i],mx=max(mx,max(L,S)/a[i]);
    ll l=0,r=mx,ans=0;
    while(l<=r)
    {
        ll mid=(l+r)>>1;
        if(check(mid)) r=mid-1;
        else l=mid+1;
    }
    printf("%lld",l);
}