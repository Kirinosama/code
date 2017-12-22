#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXN 200010
#define MAXQ 200010

int sqr,to[MAXN],q,n,m,l,r,ans[MAXQ];

struct node
{
	int x,y;
}s[MAXQ];

struct Query
{
	int pos,l,r,ansid;
	bool operator < (Query a)
	const{
		if(l/sqr==a.l/sqr) return r/sqr<a.r/sqr;
		return l/sqr<a.l/sqr;
	}
}query[MAXQ];

int main()
{
	//freopen("input","r",stdin);
	scanf("%d %d %d",&n,&m,&q);
	sqr=(int)sqrt(m);
	for(int i=1;i<=m;i++) 
		scanf("%d %d",&s[i].x,&s[i].y);
	for(int i=1;i<=n;i++) to[i]=i;
	swap(to[s[1].x],to[s[1].y]);
	l=r=1;
	for(int i=1;i<=q;i++)
	{
		scanf("%d %d %d",&query[i].pos,&query[i].l,&query[i].r);
		query[i].ansid=i;
	}
	sort(query+1,query+1+q);
	for(int i=1;i<=q;i++)
	{
		static int pos1,pos2;
		int pos=query[i].pos;
		int ll=query[i].l;
		int rr=query[i].r;
		while(ll<l)
		{
			l--;
			for(int i=1;i<=n;i++)
			{
				if(to[i]==s[l].x) pos1=i;
				if(to[i]==s[l].y) pos2=i;
			}
			swap(to[pos1],to[pos2]);
		}
		while(rr>r)
		{
			r++;
			swap(to[s[r].x],to[s[r].y]);
		}
		while(ll>l)
		{
			for(int i=1;i<=n;i++)
			{
				if(to[i]==s[l].x) pos1=i;
				if(to[i]==s[l].y) pos2=i;
			}
			swap(to[pos1],to[pos2]);
			l++;
		}
		while(rr<r)
		{
			swap(to[s[r].x],to[s[r].y]);
			r--;
		}
		for(int j=1;j<=n;j++)
			if(to[j]==pos)
				ans[query[i].ansid]=j;
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
