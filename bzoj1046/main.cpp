#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 1000000000
using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,m,cnt;
int a[100005],f[100005],best[100005];

void solve(int x)
{
	int last=0;
	for(int i=1;i<=n;i++)
		if(f[i]>=x&&a[i]>last)
		{
			printf("%d",a[i]);
			if(x!=1)printf(" ");
			last=a[i];
			x--;
			if(!x)break;
		}

	printf("\n");
}

int find(int x)
{ 
	int l=1,r=cnt,ans=0;
	while(l<=r)
	{

		int mid=(l+r)>>1;
		if(best[mid]>x)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}

void pre()
{
	for(int i=n;i;i--)
	{ 
		int t=find(a[i]);
		f[i]=t+1;
		cnt=max(cnt,t+1);
		if(best[t+1]<a[i])
			best[t+1]=a[i];
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	pre();
	m=read();
	for(int i=1;i<=m;i++)
	{
		int x=read();
		if(x<=cnt)solve(x);
		else puts("Impossible");
	}
	return 0;
}