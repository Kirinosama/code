#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<set>
#include<map>
#include<vector>
#define inf 1000000000
#define mod 19940417
#define ine 3323403
#define ll long long
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
ll n,m,ans;
ll sum(ll a,ll b)
{
	return (b-a+1)*(a+b)/2%mod;
}
ll sum2(ll x)
{
    return x*(x+1)%mod*(2*x+1)%mod*ine%mod;
}
ll cal(ll n)
{
	ll tmp=0;
	for(ll i=1,j;i<=n;i=j+1)
	{
		j=n/(n/i);
		tmp=(tmp+n*(j-i+1)%mod-sum(i,j)*(n/i))%mod;
	}
	return (tmp+mod)%mod;
}
int main()
{
	freopen("bzoj2956.in","r",stdin);
	n=read();m=read();
    ans=cal(n)*cal(m)%mod;
	if(n>m)swap(n,m);
	ll s1,s2,s3;
	for(int i=1,j;i<=n;i=j+1)
	{
		j=min(n/(n/i),m/(m/i));
		s1=n*m%mod*(j-i+1)%mod;
		s2=(n/i)*(m/i)%mod*(sum2(j)-sum2(i-1)+mod)%mod;
		s3=(n/i*m+m/i*n)%mod*sum(i,j)%mod;
		ans=(ans-(s1+s2-s3)%mod+mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}