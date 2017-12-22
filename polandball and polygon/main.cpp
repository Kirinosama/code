#include <cstdlib>
#include <cstdio>
#include <iostream>
//755D

#define MAXN 1000010 

int n,k,ll,rr;
long long c[MAXN];
long long ans;

int lowbit(int x)
{
	return x&-x;
}

long long getsum(int x)
{
	long long sum=0;
	while(x)
	{
		sum+=c[x];
		x-=lowbit(x);
	}
	return sum;
}

void add(int x,int k)
{
	while(x<=n)
	{
		c[x]+=k;
		x+=lowbit(x);
	}
}

void solve(int ll,int rr)
{
	if(ll<rr)
		ans+=getsum(rr-1)-getsum(ll)+1;
	else
		ans+=getsum(rr-1)+getsum(n)-getsum(ll)+1;
	add(ll,1);add(rr,1);
	std::cout<<ans;
	printf(" ");
}

int main()
{
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	scanf("%d %d",&n,&k);
	if(k>n/2)
		k=n-k;
	ll=1;
	ans=1;
	while(1)
	{
		rr=(ll+k)%n;
		if(rr==0)
			rr=n;
			solve(ll,rr);
		ll=rr;
		if(rr==1)
			break;
	}
}