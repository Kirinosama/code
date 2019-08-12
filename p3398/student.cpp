#include <bits/stdc++.h>
using namespace std;
struct xiu
{
	int to,from;
	int dis;
}e[200010];
int cnt=0;
int f[10005]={0};
void add (int u,int v,int w)
{
	e[++cnt].dis=w;
	e[cnt].to=v;
	e[cnt].from=u;
}
bool cmp (const xiu &x,const xiu &y)
{
	return x.dis<y.dis;
}
int find(int x)
{
	if (x==f[x])
	    return x;
	else
	    return f[x]=find (f[x]);
}
void combine (int x,int y)
{
	f[find(x)]=find(y);
	return;
}
int main()
{
	freopen("1.in","r",stdin);
	int n,m,count=0;
	int i,j,k=0,u,v,w;
	cin>>n>>m;
	for(int i=1;i<=n;i++)f[i]=i;
	for (i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
		add(u,v,w);
	}
	sort(e+1,e+1+m,cmp);
	for (i=1;i<=m;i++)
	{
		if (count==n-1)
		    break;
		int c=e[i].from,d=e[i].to;
		if (find(c)==find(d))
		    continue;
		combine(d,c);
		k+=e[i].dis;
		count++;
	}
	if(count==n-1) cout<<k;
	else cout<<"orz";
	return 0;
}

