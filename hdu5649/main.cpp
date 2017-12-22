#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

vector <avlnode *> v;

struct avlnode
{
	seg_node * seg_root;
	int lcover,rcover;
};

struct seg_node
{
	int l,r;
	int cnt;
	int order;
	seg_node * ls;
	seg_node * rs;
}

void init()
{
	
}

void split(seg_node * p,int k,seg_node *&x,seg_node *&y)
{
	seg_newnode(x);
	seg_newnode(y);
	x->order=y->order=p->order;
	x->cnt=k;y->cnt=p->cnt-k;
	x->l=y->l=p->l;x->r=y->r=p->r;
	if(p->ls->cnt<k)
	{
		x->ls=p->ls;
		split(p->rs,k-p->ls->cnt,x->rs,y->rs);
	}
	else if(p->ls->cnt==k)
	{
		x->ls=p->ls;
		y->rs=p->rs;
	}
	else
	{
		y->rs=p->rs;
		split(p->ls,k,x->ls,y->ls);
	}
}


void split_and_add(seg_node * p,int ll,int rr,int mid);
{
	seg_node * x;
	seg_node * y;
	if(p->order==1)
		split(p,mid-ll,x,y);
	else
		split(p,rr-(mid+1),y,x);
	avl_insert(x,ll,mid);
	avl_insert(y,mid+1,rr);
}

void go(avlnode * p,int ll,int rr,vector<avlnode *> &v)
{
	if(p==null)
		return;
	if(p->lcover>=ll && p->rcover<=rr)
	{
		v.push_back(p);
	}
	else if(p->rcover<ll)
		go(p->rs,ll,rr,v);
	else
		go(p->ls,ll,rr,v);
}

void seg_merge(seg_node *&xxx,seg_node *&yyy,seg_node *&zzz)
{
	if(xxx==null)
		zzz=yyy;
	if(yyy==null)
		zzz=xxx;
	if(xxx!=null && yyy!=null)
	{
		zzz->l=xxx->l;
		zzz->r=xxx->r;
		zzz->cnt=xxx->cnt+yyy->cnt;
		merge(xxx->ls,yyy->ls,zzz->ls);
		merge(xxx->rs,yyy->rs,zzz->rs);
	}
}

void merge(int kind,int ll,int rr)
{
	v.clear();
	go(avlroot,ll,rr,v);
	avlnode* aaa;
	avl_newnode(aaa);
	seg_node * bbb;
	seg_newnode(bbb);
	seg_node * ccc;
	seg_newnode(ccc);
	for(int i=0;i<v.size();i++)
	{
		seg_merge(bbb,v[i]->seg_root,ccc);
		bbb=ccc;
	}
}

void solve(int kind,int ll,int rr)
{
	avlnode * leftroot = ask_pre(avlroot,ll);//小于等于
		split_and_add(leftroot->seg_root,leftroot->lcover,leftroot->rightcover,ll);//将区间两端线段树分离并插入平衡树新节点
		avl_del(avlroot,leftroot->lcover); //在平衡树中删除原节点
	avlnode * rightroot = ask_suc(avlroot,rr);//最大的小于等于
		split_and_add(rightroot->seg_root,rightroot->lcover,rightroot->rightcover,rr);
		avl_del(avlroot,rightroot->lcover);
	merge(kind,ll,rr);//切好后合并 kind为0或1
}

void read()
{
	int ll,rr,pos;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	init();
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d %d",&kind,&ll,&rr);
		solve(kind,ll,rr);
	}
	scanf("%d",&pos);
	ask(pos);
}

int main()
{
	read();
	return 0;
}