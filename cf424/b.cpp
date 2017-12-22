#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXN 110
int ans,l,r,n,m;
int maxx;

struct node
{
	int x,y;
	void in()
	{
		scanf("%d %d",&x,&y);
		maxx=max(maxx,x);
	}
}q[MAXN];

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	if(!m)
	{
		if(n==1)
		{
			printf("1");
			return 0;
		}
		else
		{
			printf("-1");
			return 0;
		}
	}
	for(int i=1;i<=m;i++)
		q[i].in();
	l=0;r=1e9;
	for(int i=1;i<=m;i++)
	{
		l=max(l,(q[i].x+q[i].y-1)/q[i].y);
		if(q[i].y-1!=0) 
			r=min(r,(q[i].x-1)/(q[i].y-1));
	}
	if(r==1e9)
	{
		if(n>maxx)
		{
			printf("-1");
			return 0;
		}
		else
		{
			printf("1");
			return 0;
		}
	}
	if(l>r) 
	{
		printf("-1");
		return 0;
	}
	for(int i=l;i<=r;i++)
	{
		if(!ans) ans=(n+i-1)/i;
		else if((n+i-1)/i==ans) continue;
		else 
		{
			printf("-1");
			return 0;
		}
	}
	printf("%d",ans);
	return 0;
}