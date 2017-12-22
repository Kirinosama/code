#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

#define MAXN 200010

struct Line
{
	int l,r;
	void in(){
		scanf("%d %d",&l,&r);
	}
}line[MAXN];

struct node
{
	int l,r;
	int cover;
	int sum;
	node *ls,*rs;
	void update()
	{
		if(cover) sum=r-l+1;
		else
		{
			sum=0;
			if(ls) sum+=ls->sum;
			if(rs) sum+=rs->sum;
		}
	}
}*root;

int n,MAX_R;
map <int,int> mp;

void build(node*&p,int l,int r)
{
	p=new node;
	p->ls=p->rs=NULL;
	p->l=l;p->r=r;
	p->sum=p->cover=0;
	if(l!=r)
	{
		int mid=(l+r)>>1;
		build(p->ls,l,mid);
		build(p->rs,mid+1,r);
	}
}

void premake()
{
	int v[MAXN*2];
	for(int i=1;i<=n;i++)
	{
		v[i*2-1]=line[i].l;
		v[i*2]=line[i].r;
	}
	sort(v+1,v+1+2*n);
	int len=unique(v+1,v+1+2*n)-v-1;
	mp[v[1]]=1;
	for(int i=2;i<=len;i++)
	{
		if(v[i]==v[i-1]+1) mp[v[i]]=mp[v[i-1]]+1;
		else mp[v[i]]=mp[v[i-1]]+2;
	}
	MAX_R=mp[v[len]];
	for(int i=1;i<=n;i++)
	{
		line[i].l=mp[line[i].l];
		line[i].r=mp[line[i].r];
		//printf("%d %d\n",line[i].l,line[i].r);
	}
	build(root,1,MAX_R);
}

void insert(node*& p,int l,int r,int ad)
{
	if(r<p->l || l>p->r) return;
	else if(p->l>=l && p->r<=r)
	{
		p->cover+=ad;
		p->update();
	}
	else
	{
		insert(p->ls,l,r,ad);
		insert(p->rs,l,r,ad);
		p->update();
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) line[i].in();
	premake();
	for(int i=1;i<=n;i++) insert(root,line[i].l,line[i].r,1);
	for(int i=1;i<=n;i++)
	{
		int res1=root->sum;
		insert(root,line[i].l,line[i].r,-1);
		int res2=root->sum;
		insert(root,line[1].l,line[i].r,1);
		if(res1==res2)
		{
			printf("%d",i);
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
