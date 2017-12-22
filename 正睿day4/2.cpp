#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
#define MAXN 3010
#define MAXM 300010
 
struct node
{
	ll a,b;
}t[MAXN];

int n,m;
ll d,hp[MAXM],sumsqr[MAXN],ans[MAXN];

void make(int mask)
{
	int cnt=0;
	ll res=0;
	vector <ll> s;
	s.clear();
	for(int i=1;i<=n;i++)
	{
		int k=mask&1;
		mask>>=1;
		if(k==1)
		{
			res+=t[i].a*t[i].b;
			s.push_back(t[i].a+t[i].b);
			cnt++;
		}
	}
	sort(s.begin(),s.end());
	res+=sumsqr[cnt-1]*d*d;
	for(int i=0;i<s.size();i++)
		res+=((int)s.size()-1-i)*d*s[i];
	ans[cnt]=min(ans[cnt],res);
}

void premake()
{
	for(int i=1;i<=n;i++)
		sumsqr[i]=sumsqr[i-1]+i*i;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %lld",&n,&m,&d);
	for(int i=1;i<=n;i++) scanf("%lld",&t[i].a);
	for(int i=1;i<=n;i++) scanf("%lld",&t[i].b);	
	for(int i=1;i<=m;i++) scanf("%lld",&hp[i]);
	premake();
	memset(ans,0x7f,sizeof(ans));
	ans[0]=0;
	for(int i=1;i<=(1<<n)-1;i++) make(i);
	for(int i=1;i<=m;i++) 
	{
		for(int j=n;j>=0;j--)
			if(hp[i]>ans[j])
			{
				printf("%d ",j);
				break;
			}
	}
	return 0;
}
