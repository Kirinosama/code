#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 20010
int a[MAXN][6],x,c[MAXN*5],f[MAXN*5],n;

int lowbit(int x)
{
	return x&-x;
}

int getmax(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res=max(res,c[i]);
	return res;
}

void update(int x,int k)
{
	for(int i=x;i<=5*n;i+=lowbit(i))
		c[i]=max(c[i],k);
}

void solve(int x)
{
	for(int i=5;i>=1;i--)
	{
		int pos=a[x][i];
		int k=getmax(pos-1);
		f[pos]=max(f[pos],k+1);
		update(pos,f[pos]);
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=5*n;i++) 
	{
		scanf("%d",&x);
		a[x][++a[x][0]]=i;
	}
	for(int i=1;i<=5*n;i++)
	{ 
		scanf("%d",&x);
		solve(x);
	}
	printf("%d",getmax(5*n));
	return 0;
}