#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE(x) ((x)?(x)->size:0)
#define HEIGHT(x) ((x)?(x)->height:-1)

#define MAXN 200010

struct node 
{
	node *l;
	node *r;
	int size;
	int height;
	int data;
	int cnt;
}t[MAXN];

struct node *root=NULL;

int i,n,node_cnt;

void maintain(node* p)
{
	p->height=max(HEIGHT(p->l),HEIGHT(p->r))+1;
	p->size=SIZE(p->l)+SIZE(p->r)+1;
}

node* singlerotateRR(node *p)
{
	node *p1=p->r;
	p->r=p1->l;
	p1->l=p;
	maintain(p);
	maintain(p1);
	return p1;
}

node* singlerotateLL(node *p)
{
	node *p1=p->l;
	p->l=p1->r;
	p1->r=p;
	maintain(p);
	maintain(p1);
	return p1;
}

node* doublerotateRL(node *p)
{
	p->l=singlerotateRR(p->l);
	p=singlerotateLL(p);
	return p;
}

node* doublerotateLR(node *p)
{
	p->r=singlerotateLL(p->r);
	p=singlerotateRR(p);
	return p;
}

node* insert(node *p,int k)
{
	if(!p)
	{
		p=&t[node_cnt];
		p->height=1;
		p->size=1;
		p->data=k;
		p->cnt=1;
		p->l=p->r=NULL;
	}

	else if(k==p->data)
	{
		p->cnt++;
	}
	
	else if(k<p->data)
	{
		p->l=insert(p->l,k);
		if(SIZE(p->l)-SIZE(p->r)==2)
		{
			if(k<p->l->data)
			p=singlerotateLL(p);
			else
			p=doublerotateRL(p);
		}
	}
	else if(k>p->data)
	{
		p->r=insert(p->r,k);
		if(SIZE(p->r)-SIZE(p->l)==2)
		{
			if(k>p->r->data)
			p=singlerotateRR(p);
			else
			p=doublerotateLR(p);
		}
	}
	maintain(p);
	return p;
}

node* delBalance(node *p)
{
	if(HEIGHT(p->l)-HEIGHT(p->r)==2)
	{
		if(HEIGHT(p->l->l)>=HEIGHT(p->l->r))
		p=singlerotateLL(p);
		else
		p=doublerotateRL(p);
	}
	if(HEIGHT(p->r)-HEIGHT(p->l)==2)
	{
		if(HEIGHT(p->r->r)>=HEIGHT(p->r->l))
		p=singlerotateRR(p);
		else
		p=doublerotateLR(p);
	}
	maintain(p);
	return p;
}

node* delnode(node *p,int k)
{	
	if(!p->r)
		p=p->l;
	else
	{
		node* now=p->r;
		while(now->l)
		{
			now=now->l;
		}
		p->data=now->data;
		p->cnt=now->cnt;	
		p->r=delnode(p->r,p->data);
	}
	maintain(p);
	return p;
}

node *del(node *p,int k)
{
	if(!p)
		return p;
	if(p->data==k)
	{
		if(p->cnt>1)
			p->cnt--;
		if(p->cnt==1)
			delnode(p,k);
	}

	else if(k<p->data)
		p->l=del(p->l,k);
	else if(k>p->data)
		p->r=del(p->r,k);

	if(p->l)
	p->l=delBalance(p->l);	
	if(p->r)
	p->r=delBalance(p->r);
	if(p)
	p=delBalance(p);

	maintain(p);
	return p;
}

void solve()
{
	int c,k;
	scanf("%d%d",&c,&k);
	if(c==1)
	{
		node_cnt++;
		root=insert(root,k);
	}
	if(c==2)
	root=del(root,k);
	/*if(c==3)
	printf("%d\n",ask_rank(root,k));
	if(c==4)
	printf("%d\n",ask_which_rank(root,k));
	if(c==5)
	printf("%d\n",ask_pre(root,k));
	if(c==6)
	printf("%d\n",ask_suc(root,k));	*/
}



void make(node *p)
{
	if(!p)
	return;
	make(p->l);
	printf("%d %d\n",p->data,p->cnt);
	make(p->r);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	solve();
	make(root);
	return 0;
}
