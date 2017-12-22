#include <cstdlib>
#include <cstdio>
#include <algorithm>


#define MAXN 100010

struct node 
{
	node *ls;
	node *rs;
	int data;
	int height;
	int size;
	int cnt;
	int element_cnt;
	void maintain()
	{
		height=std::max(ls->height,rs->height)+1;
		size=ls->size+rs->size+1;
		element_cnt=ls->element_cnt+rs->element_cnt+cnt;
	}
};

int n;
node mem_pool[MAXN*8];
node *root;
node *null;
node *tail;

void init()
{
	tail=mem_pool;
	null=tail++;
	null->rs=null->ls=null;
	null->data=null->cnt=null->size=0;
	null->height=-1;null->element_cnt=0;
	root=null;
}

void newnode(node *& p,int k)
{
	p=tail++;
	p->cnt=1;
	p->data=k;
	p->rs=p->ls=null;
	p->height=0;
	p->element_cnt=1;
	p->size=1;
}

node * singlerotateRR(node *p)
{
	node *p1=p->rs;
	p->rs=p1->ls;
	p1->ls=p;
	p->maintain();
	p1->maintain();
	return p1;
}

node * singlerotateLL(node *p)
{
	node *p1=p->ls;
	p->ls=p1->rs;
	p1->rs=p;
	p->maintain();
	p1->maintain();
	return p1;
}

node *	doublerotateRL(node *p)
{
	p->ls=singlerotateRR(p->ls);
	return singlerotateLL(p);
}

node *	doublerotateLR(node *p)
{
	p->rs=singlerotateLL(p->rs);
	return singlerotateRR(p);
}

node * insert(node *& p,int k)
{
	if(p==null)
	{
		newnode(p,k);
		return p;
	}		

	if(p->data==k)
	{
		p->cnt++;
		p->element_cnt++;
	}

	else if(k<p->data)
	{
		p->ls=insert(p->ls,k);
		if(p->ls->height-p->rs->height==2)
		{
			if(p->ls->ls->height>p->ls->rs->height)
				p=singlerotateLL(p);
			else
				p=doublerotateRL(p);
		}
	}

	else
	{
		p->rs=insert(p->rs,k);
		if(p->rs->height-p->ls->height==2)
		{
			if(p->rs->rs->height>p->rs->ls->height)
				p=singlerotateRR(p);
			else
				p=doublerotateLR(p);
		}
	}

	p->maintain();
	return p;
}

node * delbalance(node *p)
{
	if(p->ls->height-p->rs->height==2)
	{
		if(p->ls->ls->height>p->ls->rs->height)
			p=singlerotateLL(p);
		else
			p=doublerotateRL(p);
	}
	if(p->rs->height-p->ls->height==2)
	{
		if(p->rs->rs->height>p->rs->ls->height)
			p=singlerotateRR(p);
		else
			p=doublerotateLR(p);
	}
	p->maintain();
	return p;
}

node * delnode (node *& p,int k)
{
	if(p->data==k)
	{
		if(p->rs==null)
			p=p->ls;
		else
		{
			node * p1= p->rs;
			while(p1->ls!=null)
				p1=p1->ls;
			p->cnt=p1->cnt; p->data=p1->data;
			p->rs=delnode(p->rs,p->data);
			p->maintain();
			return p;
		}
	}
	else if(k<p->data)
		p->ls=delnode(p->ls,k);
	else
		p->rs=delnode(p->rs,k);

	if(p->ls!=null)
		p->ls=delbalance(p->ls);
	if(p->rs!=null)
		p->rs=delbalance(p->rs);
	if(p!=null)
		p=delbalance(p);

	p->maintain();
	return p;
}

node * del(node *& p,int k)
{
	if(p->data==k)
	{
		p->cnt--;
		p->element_cnt--;
		if(p->cnt==0)
		p=delnode(p,k);
	}
	else if(k<p->data)
		p->ls=del(p->ls,k);
	else
		p->rs=del(p->rs,k);

	p->maintain();
	return p;
}

int which_rank(node *p,int k)
{
	int lcnt=p->ls->element_cnt;
	if(k>lcnt && k<=lcnt+p->cnt)
		return p->data;
	else if(k<=lcnt)
		return which_rank(p->ls,k);
	else 
		return which_rank(p->rs,k-lcnt-p->cnt);
}

int rank(node * p,int k)
{
	if(p==null)
		return 0;
	if(p->data<k)
		return p->cnt+p->ls->element_cnt+rank(p->rs,k);
	else
		return rank(p->ls,k);
}

int pre(node *p,int k)
{
	if(p==null)
		return 0;
	if(p->data>=k)
		return pre(p->ls,k);
	else
		return std::max(p->data,pre(p->rs,k));
}

int suc(node *p,int k)
{
	if(p==null)
		return 0x7f7f7f7f;
	if(p->data<=k)
		return suc(p->rs,k);
	else
		return std::min(p->data,suc(p->ls,k));
}

void solve()
{
	int c,k;
	scanf("%d%d",&c,&k);
	if(c==1)
		root=insert(root,k);
	if(c==2)
 		del(root,k);
	if(c==3)
	 	printf("%d\n",rank(root,k)+1);
	if(c==4)
	 	printf("%d\n",which_rank(root,k));
	if(c==5)
	 	printf("%d\n",pre(root,k));
	if(c==6)
	 	printf("%d\n",suc(root,k));
}

void make(node * p)
{
	if(p==null)
		return;
	make(p->ls);
	printf("%d %d\n",p->data,p->cnt);
	make(p->rs);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	init();
	while(n--)
		solve();
	//make(root);
	return 0;
}