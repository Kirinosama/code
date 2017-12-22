#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

typedef long long ll;
#define SUM(x) (x?x->sum:0)
#define ALLCNT(x) (x?x->allcnt:0)
#define MAXN 100010

int a[MAXN],n,m;
ll lsum,rsum,LCNT,RCNT,ans;

struct Treap
{
	struct node
	{
		int data;
		int cnt;
		int allcnt;
		ll sum;
		int k;
		node* ls;
		node* rs;

		void maintain()
		{
			allcnt=cnt+ALLCNT(ls)+ALLCNT(rs);
			sum=cnt*data+SUM(ls)+SUM(rs);
		}
	};	
	node* root;

	void newnode(node*&p,int x)
	{
		p=new node;
		p->ls=p->rs=NULL;
		p->allcnt=1;p->data=x;p->cnt=1;p->sum=x;p->k=rand();
	}

	node* zag(node*p)
	{
		node* p1=p->rs;
		p->rs=p1->ls;
		p1->ls=p;
		p->maintain();
		p1->maintain();
		return p1;
	}

	node* zig(node* p)
	{
		node* p1=p->ls;
		p->ls=p1->rs;
		p1->rs=p;
		p->maintain();
		p1->maintain();
		return p1;
	}

	void __add(node*& p,int x)
	{
		if(!p) {newnode(p,x);return;}
		else if(x==p->data) {p->allcnt++;p->cnt++;p->sum+=x;return;}
		else if(x<p->data)
		{
			__add(p->ls,x);
			if(p->ls->k<p->k)
				p=zig(p);
		}
		else 
		{
			__add(p->rs,x);
			if(p->rs->k<p->k)
				p=zag(p);
		}
		p->maintain();
	}

	void __del(node*&p,int x)
	{
		if(!p) return;
		else if(x<p->data) __del(p->ls,x); 
		else if(x>p->data) __del(p->rs,x);
		else
		{
			p->allcnt--;p->cnt--;p->sum-=p->data;
			if(p->cnt) return;
			if(!p->rs){p=p->ls;return;}
			else if(!p->ls){p=p->rs;return;}
			if(p->rs->k<p->ls->k)
			{
				p=zag(p);__del(p->ls,x);
			}
			else 
			{
				p=zig(p);__del(p->rs,x);
			}
		}
		p->maintain();
	}

	void __print(node* p)
	{
		if(!p) return;
		__print(p->ls);
		printf("data:%d cnt:%d allcnt:%d sum:%lld k:%d\n",p->data,p->cnt,p->allcnt,p->sum,p->k);
		__print(p->rs);
	}

	int __find(node*p,int rk)
	{
		int lcnt=ALLCNT(p->ls);
		if(rk>lcnt && rk<=lcnt+p->cnt)
		{
			lsum+=SUM(p->ls);
			rsum+=SUM(p->rs);
			LCNT+=ALLCNT(p->ls);
			RCNT+=ALLCNT(p->rs);
			return p->data;
		}
		else if(rk<=lcnt)
		{
			RCNT+=ALLCNT(p->rs)+p->cnt;
			rsum+=SUM(p->rs)+p->cnt*p->data;
			return __find(p->ls,rk);
		}
		else
		{
			LCNT+=ALLCNT(p->ls)+p->cnt;
			lsum+=SUM(p->ls)+p->cnt*p->data;
			return __find(p->rs,rk-lcnt-p->cnt);
		}
	}

	void add(int x) {__add(root,x);}
	void del(int x) {__del(root,x);}
	void print() {__print(root);}
	int find(int rk) {return __find(root,rk);}
}t;	

void solve()
{
	LCNT=0;RCNT=0;lsum=0;rsum=0;
	int ch=t.find((m+1)>>1);
	ll res=LCNT*ch-lsum+rsum-RCNT*ch;
	ans=min(ans,res);
}

int main()
{
	freopen("input","r",stdin);
	srand(time(0));ans=0x7fffffffffffffff;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) t.add(a[i]);
	for(int i=m+1;i<=n;i++)
	{
		solve();
		t.add(a[i]);
		t.del(a[i-m]);
	}
	solve();
	printf("%lld",ans);
	return 0;
}