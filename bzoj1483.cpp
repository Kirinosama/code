#include <cstdlib>
#include <cstdio>
#include <set>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 100010

int ans,a,b,n,m,x,v[MAXN],fa[MAXN*10];
set <int> t[MAXN*10];

void solve(int a,int b)
{
	set <int> :: iterator it;
	for(it=t[a].begin();it!=t[a].end();it++)
	{
		if(v[*it-1]==b) ans--;
		if(v[*it+1]==b) ans--;
		t[b].insert(*it);
	}
	for(it=t[a].begin();it!=t[a].end();it++) v[*it]=b;
	t[a].clear();
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=1;i<=n;i++)
	{
		fa[v[i]]=v[i];
		if(v[i]!=v[i-1]) ans++;
		t[v[i]].insert(i);
	}	
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&x);
		if(x==2) printf("%d\n",ans);
		else
		{
			scanf("%d %d",&a,&b);
			if(a==b) continue;
			if(t[fa[a]].size()>t[fa[b]].size())
				swap(fa[a],fa[b]);
			solve(fa[a],fa[b]);
		}
	}
	return 0;
}