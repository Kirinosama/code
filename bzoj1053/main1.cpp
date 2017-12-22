#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

ll n,mx,ans;
int zhi[10]={2,3,5,7,11,13,17,19,23,29};
int s[20];

ll pow(ll x,int k)
{
	if(k==0) return 1;
	if(k==1) return x;
	if(k%2) return x*pow(x,k-1);
	else return pow(x*x,k/2); 
}

void dfs(int pos,int cnt,ll mul)
{
	if(pos==10)
	{
		if(cnt>mx)
		{
			mx=cnt;
			ans=mul;
		}
		if(cnt==mx && mul<ans)
			ans=mul;
		return;
	}
	for(int i=0;i<=(pos?s[pos-1]:60);i++)
	{
		if(mul*pow(zhi[pos],i)>n)
			return;
		s[pos]=i;
		dfs(pos+1,cnt*(i+1),mul*pow(zhi[pos],i));
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%lld",&n);
	ans=2000000010;
	dfs(0,1,1);
	printf("%lld",ans);
	return 0;
}