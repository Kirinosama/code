#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int read()
{
	char ch=getchar();int x=0,f=1;
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,d,a,b;
int x[155],y[155];
int f[155];
bool vis[555];
int main()
{
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
	n=read();d=read();a=read();b=read();
	ll ans=9000000000000000000LL;
	for(int i=1;i<=n;i++)
	{
		x[i]=read();
		vis[x[i]]=1;
	}
	sort(x+1,x+n+1);
	if(a<=b)
	{
		int ans=0;
		for(int i=1;i<=150;i++)
		{
			if(vis[i])
			{
				int num=0,now=i;
				while(vis[now])
				{
					vis[now]=0;
					num++;
					now+=2*d;
				}
				ans+=(num+1)/2;
			}
		}
		cout<<1LL*ans*a;
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			y[j]=x[j]+d;
		}
		for(int j=i+1;j<=n;j++)
		{
			y[j]=x[j]-d;
		}
		sort(y+1,y+n+1);
		memset(f,0x7f7f7f7f,sizeof(f));
		f[0]=0;
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=j;k++)
			{
				f[j]=min(f[j],f[k-1]+a+b*(y[j]-y[k]));
			}
		}
		ans=min(ans,1LL*f[n]);
	}
	cout<<ans;
}

