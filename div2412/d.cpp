#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 1000010
typedef long long ll;
ll ans,p,q;
int n,a[MAXN],book[MAXN],max_num,odd_cnt;
vector <int> v;

int lowbit(int x)
{
	return x&-x;
}

struct lowb
{
	ll s[MAXN];
	void init()
	{
		memset(s,0,sizeof(s));
	}
	void add(int x,ll k)
	{
		for(int i=x;i<=max_num;i+=lowbit(i))
			s[i]+=k;
	}
	ll query(int x)
	{
		ll res=0;
		for(int i=x;i;i-=lowbit(i))
			res+=s[i];
		return res;
	}
	ll get_sum(int l,int r)
	{
		if(l>r) return 0;
		if(l<=0) return query(r);
		return query(r)-query(l-1);
	}
}cnt,sum;

void premake()
{
	cnt.init();
	sum.init();
	for(int i=1;i<=n;i++)
	{
		cnt.add(a[i],1);
		sum.add(a[i],a[i]);
	}
}

void solve(int P)
{
	ll res=0;
	ll pos=0;
	ll gap=p/q+1;
	while(pos<max_num)
	{
		pos+=P;
		ll l=pos-P;
		ll r=pos;
		res+=cnt.get_sum(l,r-gap)*p;
		res+=(cnt.get_sum(r-gap+1,r)*r-sum.get_sum(r-gap+1,r))*q;
		if(res>ans) return;
	}
	ans=min(ans,res);
}

int main()
{
	freopen("input","r",stdin);
	cin>>n>>p>>q;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]&1) odd_cnt++;
		max_num=max(max_num,a[i]);
	}
	ans=min(n*p,odd_cnt*min(p,q));
	sort(a+1,a+1+n);
	premake();
	for(int i=2;i<=1000000;i++)
	{
		if(!book[i])
		{
			for(int j=i*2;j<=1000000;j+=i)
				book[j]=1;
			v.push_back(i);
		}
		if(i>=max_num)
			break;
	}
	for(int i=0;i<v.size();i++)
		solve(v[i]);
	cout<<ans;
	return 0;
}
