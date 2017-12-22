#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

#define MAXN 1000010

struct node
{
	node *ls;
	node *rs;
	long long l,r,sum;
	void maintain()
	{
		sum=ls->sum+rs->sum;
	}
};

node *root;
node *null;
node *tail;
node mem_pool[MAXN*6];
long long ans,ll,rr,n,k;

void init()
{
	tail=mem_pool;
	null=tail++;
	null->l=null->r=0;
	null->sum=0;
	null->ls=null->rs=null;
	root=null;
}

void build(node *&p,long long l,long long r)
{
	if(p==null)
		p=tail++;
	p->ls=p->rs=null;
	p->l=l;p->r=r;
	p->sum=0;
	if(l!=r)
	{
		long long mid=(l+r)/2;
		build(p->ls,l,mid);
		build(p->rs,mid+1,r);
	}
}

void add(node *&p,long long l,long long r,long long k)
{
	if(p->l>r || p->r<l)
		return;
	if(p->l>=l && p->r<=r)
	{
		p->sum+=k;
		return;
	}
	else if(p->l!=p->r)
	{
		add(p->ls,l,r,k);
		add(p->rs,l,r,k);
		p->maintain();
	}
}

long long ask(node *p,long long l,long long r)
{
	if(l>r)
		return 0;
	if(p->l>r || p->r<l)
		return 0;
	if(p->l>=l && p->r<=r)
		return p->sum;
	else
		return ask(p->ls,l,r)+ask(p->rs,l,r);
}

int main()
{
	freopen("input","r",stdin);
	cin>>n>>k;
	if(k>n/2)
		k=n-k;
	init();
	build(root,1,n);
	ll=1;
	ans=1;
	while(1)
	{
		rr=ll+k;
		if(rr>n)
			rr-=n;
		if(rr>ll)
		{	
			ans+=ask(root,ll+1,rr-1)+1;
			add(root,ll,ll,1);
			add(root,rr,rr,1);
		}
		else
		{
			ans+=ask(root,ll+1,n);
			ans+=ask(root,1,rr-1)+1;
			add(root,ll,ll,1);
			add(root,rr,rr,1);
		}
		cout<<ans<<' ';
		ll=rr;
		if(ll==1)
			break;
	}
	return 0;
}	