#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 1000010

int a[MAXN],fa[MAXN],d[MAXN],r[MAXN],l[MAXN],n,t,die[MAXN];

int find(int x)
{
	return fa[x]==x ? x : fa[x]=find(fa[x]);
}

int merge(int x,int y)
{
	if(!x) return y;
	if(!y) return x;
	if(a[x]>a[y]) swap(x,y);
	r[x]=merge(r[x],y);
	if(r[x]>l[x]) swap(r[x],l[x]);
	d[x]=d[r[x]]+1;
	return x;
}

void kill(int x)
{
	int fx=find(x);
	int m=merge(l[fx],r[fx]);
	fa[l[fx]]=fa[r[fx]]=fa[fx]=m;
	die[fx]=1;printf("%d\n",a[fx]);
}

void solve()
{
	char ch; int x,y;
	scanf("%c ",&ch);
	if(ch=='M') 
	{
		scanf("%d %d\n",&x,&y);
		if(die[x] || die[y]) return;
		int fx=find(x);int fy=find(y);
		if(fx!=fy)
		{
			int m=merge(fx,fy);
			fa[fx]=fa[fy]=m;
		}
	}
	else
	{
		scanf("%d\n",&x);
		if(!die[x])	{ kill(x);}
		else printf("0\n");
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n); 
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) fa[i]=i;
	d[0]=-1;
	scanf("%d\n",&t);
	while(t--) solve();
	return 0;
}