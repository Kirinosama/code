#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 100010

struct node
{
	int x,y,v;
	void in(){scanf("%d %d %d",&x,&y,&v);}
}p[MAXN];

int n,m,k,l,c[MAXN];

bool cmp(node a,node b)
{
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}

void init()
{
	vector <int> Q; 
	map <int,int> mp;
	for(int i=1;i<=k;i++)
		Q.push_back(p[i].y);
	sort(Q.begin(),Q.end());
	l=unique(Q.begin(),Q.end())-Q.begin();
	for(int i=0;i<l;i++) mp[Q[i]]=i+1;
	for(int i=1;i<=k;i++) p[i].y=mp[p[i].y];
	sort(p+1,p+1+k,cmp);
}

int lowbit(int x) {return x&-x;}

void update(int x,int k)
{
	for(int i=x;i<=l;i+=lowbit(i))
		c[i]=max(c[i],k);
}

int getmax(int x)
{
	int res=-1e9;
	for(int i=x;i;i-=lowbit(i))
		res=max(res,c[i]);
	return res;
}

void solve()
{
	int ans=-1e9;
	for(int i=1;i<=k;i++)
	{
		int res=getmax(p[i].y);
		ans=max(ans,res+p[i].v);
		update(p[i].y,res+p[i].v);
	}
	cout<<ans;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=k;i++)p[i].in();
	init();
	solve();
}