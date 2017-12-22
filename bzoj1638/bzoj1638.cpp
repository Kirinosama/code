#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define ll long long
#define inf 1000000000
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,cnt1,cnt2,ans;
int u[50005],v[50005];
int head[5005],h[5005],f[5005],g[5005],r[5005];
struct edge1{int to,next;}e[50005];
struct edge2{int to,next;}ed[50005];
void insert(int u,int v)
{
	e[++cnt1].to=v;e[cnt1].next=head[u];head[u]=cnt1;
	ed[++cnt2].to=u;ed[cnt2].next=h[v];h[v]=cnt2;
}
void dp1(int x)
{
	if(!head[x]){f[x]=1;return;}
	for(int i=head[x];i;i=e[i].next)
	{
		if(!f[e[i].to])dp1(e[i].to);
		f[x]++;
	}
}
void dp2(int x)
{
	if(!h[x]){g[x]=1;return;}
	for(int i=h[x];i;i=ed[i].next)
	{
		if(!g[ed[i].to])dp2(ed[i].to);
		g[x]+=g[ed[i].to];
	}
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		u[i]=read();v[i]=read();
		insert(u[i],v[i]);
	}
	for(int i=1;i<=n;i++)
		if(!f[i])dp1(i);
    dp2(n);
	for(int i=1;i<=m;i++)
		ans=max(ans,g[u[i]]*f[v[i]]);
	printf("%d\n",ans);
	return 0;
}