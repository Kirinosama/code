#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>
using namespace std;

const int INF=0x7fffffff;
int n;

struct treap
{
	struct node
	{
		int data,size,allsize,k;
		node* ls;
		node* rs;
		void maintain()
		{
			allsize=size;
			if(ls) allsize+=ls->allsize;
			if(rs) allsize+=rs->allsize;
		}
	}*root;

	node* newnode(int x)
	{
		node* p=new node;
		p->ls=p->rs=NULL;
		p->data=x;p->allsize=p->size=1;p->k=rand();
		return p;
	}

	void zag(node*& p)
	{
		node* p1=p->rs;
		p->rs=p1->ls;
		p1->ls=p;
		p->maintain();
		p1->maintain();
		p=p1;
	}

	void zig(node*& p)
	{
		node* p1=p->ls;
		p->ls=p1->rs;
		p1->rs=p;
		p->maintain();
		p1->maintain();
		p=p1;
	}

	void __add(node*&p,int x)
	{
		if(!p) p=newnode(x);
		else if(p->data==x)
			p->size++,p->allsize++;
		else if(x<p->data)
		{
			__add(p->ls,x);
			if(p->ls->k<p->k)
				zig(p);
			p->maintain();
		}
		else 
		{
			__add(p->rs,x);
			if(p->rs->k<p->k)
				zag(p);
			p->maintain();
		}
	}

	void __del(node*& p,int x,int o)
	{
		if(!p) return;
		if(p->data==x)
		{
			if(o==1 && p->size>1)
			{
				p->size--,p->allsize--;
				return;
			}
			if(p->ls && p->rs)
			{
				if(p->ls->k<p->rs->k)
				{
					zig(p);
					__del(p->rs,x,2);
				}
				else 
				{
					zag(p);
					__del(p->ls,x,2);
				}
			}
			else if(!p->ls) p=p->rs;
			else p=p->ls; 
		}
		else if(x<p->data)
			__del(p->ls,x,1);
		else
			__del(p->rs,x,1);
		if(p) p->maintain();
	}

	int less(int x)
	{
		int sum=0;
		node* p=root;
		while(p)
		{
			if(p->data<x)
			{
				sum+=p->size;
				sum+=p->ls ? p->ls->allsize : 0;
				p=p->rs;
			}
			else p=p->ls;
		}
		return sum;
	}

	int pre(int x)
	{
		int res=-INF;
		node* p=root;
		while(p)
		{
			if(p->data>=x) p=p->ls;
			else 
			{
				res=max(res,p->data);
				p=p->rs;
			}
		}
		return res;
	}

	int suc(int x)
	{
		int res=INF;
		node* p=root;
		while(p)
		{
			if(p->data<=x) p=p->rs;
			else 
			{
				res=min(res,p->data);
				p=p->ls;
			}
		}
		return res;
	}

	int __find(node* p,int x)
	{
		int lcnt=p->ls ? p->ls->allsize : 0;
		if(x>lcnt && x<=lcnt+p->size) return p->data;
		else if(x<=lcnt) return __find(p->ls,x);
		else return __find(p->rs,x-lcnt-p->size);
	}

	void add(int x){ __add(root,x); }
	void del(int x){ __del(root,x,1); }
	int find(int x){ return __find(root,x); }
}t;

void solve()
{
	int ta,x;
	scanf("%d %d",&ta,&x);
	if(ta==1) t.add(x);
	if(ta==2) t.del(x);
	if(ta==3) printf("%d\n",t.less(x)+1);
	if(ta==4) printf("%d\n",t.find(x));
	if(ta==5) printf("%d\n",t.pre(x));
	if(ta==6) printf("%d\n",t.suc(x));
}

int main()
{
	freopen("input","r",stdin);
	srand(time(0));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)solve();
	return 0;
}