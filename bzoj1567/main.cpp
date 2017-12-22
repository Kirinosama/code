#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <set>
#include <iostream>
using namespace std;

#define MAXN 55
#define ii pair<int,int>
#define It set <int> :: iterator
const int mul1=127;
const int mul2=89;
int a[MAXN][MAXN],b[MAXN][MAXN],n,ans;
set <int> s1[MAXN];
set <int> s2[MAXN];

void solve(int x,int y,set <int> *s,int k)
{	
	int l=min(n-x+1,n-y+1);
	for(int t=0;t<=l;t++)
	{
		int res=0;
		for(int i=x;i<=x+t-1;i++)
		{
			for(int j=y;j<=y+t-1;j++)
			{
				if(k==1) res=res*mul1+a[i][j];
				if(k==2) res=res*mul1+b[i][j];
				if(i-x+1==j-y+1)
					s[i-x+1].insert(res);   
			}
			res*=mul2;
		}
	}
}

bool judge(int k)
{
	for(It i=s1[k].begin();i!=s1[k].end();i++)
		if(s2[k].count(*i)) return true;
	return false;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&b[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			solve(i,j,s1,1);
			solve(i,j,s2,2);
		}
	int l=1;int r=n;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(judge(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}