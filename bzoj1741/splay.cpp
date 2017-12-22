#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 100010

struct node
{
	node* ch[2];
	node* fa;
	int cnt;
	int data;
	int sumcnt;
	void cal()
	{
		sumcnt=cnt;
		if(ch[0]) sumcnt+=ch[0]->sumcnt;
		if(ch[1]) sumcnt+=ch[1]->sumcnt;
	}
}t[MAXN],*root;

void rot(node* p,int f)  //
{
	node *fa=p->fa;
	node *grand=fa->fa;
	fa->ch[f]=p->ch[!f];
	if(p->ch[!f]) p->ch[!f]->fa=fa;
	p->ch[!f]=fa;
	if(fa==grand->ch[0]) grand->ch[0]=p;
	else grand->ch[1]=p;
	p->fa=grand;
	fa->fa=p;
	fa->cal();p->cal();
	if(fa==root) root=p;
}

void splay(node* x,node* q) //把p转到q下面
{
	node* y=x->fa;
	node* z=y->fa;
}	

void insert(int k)
{
	node* p=root;
	node* fa;
	while(p)
	{
		fa=p;
		p=p->ch[k>p->data];
	}
	p=new node;
	p->cnt=1,p->data=k,p->ch[0]=p->ch[1]=NULL,p->fa=fa;
	if(fa) fa->ch[k>fa->data]=p;
	if(p!=root) splay(p);
}

node* find(int k)
{
	node* p=root;
	while(p && p->data!=k)
		p=p->ch[k>p->data];
	return p;
}

void del(int k)
{
	if(!root) return;
	node* p=find(k);
	if(!p) return;
	splay(p);
	if(!p->ch[0] && !p->ch[1]) root=NULL;
	else if(p->ch[0] && !p->ch[1]) root=p->ch[0],p->ch[0]->fa=NULL;
	else if(p->ch[1] && !p->ch[0]) root=p->ch[1],p->ch[1]->fa=NULL;
	else
	{
		node *cur=p->ch[1];
		while(cur->ch[0])
			cur=cur->ch[0];
		splay(cur);
		p->ch[0]->fa=cur;
		p->ch[1]->fa=cur;
	}
}

int pre(int x)
{
	int res=-1e9;
	node* p=root;
	while(p)
	{
		if(p->data<x)
		{
			res=max(res,p->data);
			p=p->ch[1];
		}
		else
			p=p->ch[0];
	}
	return res;
}

int suc(int x)
{
	int res=1e9;
	node* p=root;
	while(p)
	{
		if(p->data>x)
		{
			res=min(res,p->data);
			p=p->ch[0];
		}
		else
			p=p->ch[1];
	}
	return res;
}

int main()
{
	freopen("input","r",stdin);
	insert(3);
	insert(11);
	insert(15);
	return 0;
}