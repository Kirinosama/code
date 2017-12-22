#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

#define MAXN 200010

map <string,int> mp;
int ans,vis[MAXN],cnt,n,father[MAXN];
int to[MAXN],num[MAXN];
string s1,s2;

int find(int x)
{
	if(father[x]!=x) father[x]=find(father[x]);
	return father[x];
}

void merge(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	if(fx!=fy) father[fx]=fy;
}

void dfs(int x)
{
	vis[x]=1;
	int v=to[x];
	if(!v) return;
	if(vis[v])
	{
		ans+=2;
		return;
	}
	else dfs(v);
}

int main()
{
	//freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>s1>>s2;
		if(!mp[s1]) mp[s1]=++cnt;
		if(!mp[s2]) mp[s2]=++cnt;
		to[mp[s1]]=mp[s2];
	}
	for(int i=1;i<=cnt;i++) father[i]=i;
	for(int i=1;i<=cnt;i++)
		if(to[i]) merge(i,to[i]);
	for(int i=1;i<=cnt;i++) num[find(i)]++;
	for(int i=1;i<=cnt;i++) 
		if(num[i])
			ans+=num[i]-1;
	for(int i=1;i<=cnt;i++)
		if(father[i]==i)
		{
			if(num[i]==1) continue;
			else dfs(i);
		}
	cout<<ans;
	return 0;
}
