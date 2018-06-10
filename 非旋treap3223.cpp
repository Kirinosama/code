#include <bits/stdc++.h>
using namespace std;

#define nn pair<node*,node*>
#define Size(x) (x?x->size:0)
int n,m;

struct node{
	node *ls,*rs;
	int size,val,pri,rev;
	void maintain(){
		size=1+Size(ls)+Size(rs);
	}
	void pushdown(){
		if(rev){
			swap(ls,rs);
			if(ls) ls->rev^=1;
			if(rs) rs->rev^=1;
			rev=0;
		}
	}
}*rt;

node *newnode(int x){
	node *p=new node;
	p->size=1,p->val=x,p->pri=rand(),p->rev=0;
	p->ls=p->rs=NULL;
	return p;
}

node *merge(node *x,node *y){
	if(!x) return y;
	if(!y) return x;
	x->pushdown();y->pushdown();
	if(x->pri<y->pri){
		x->rs=merge(x->rs,y);
		x->maintain();
		return x;
	}else{
		y->ls=merge(x,y->ls);
		y->maintain();
		return y;
	}
}

nn split(node *p,int k){
	if(!p) return nn(NULL,NULL);
	nn res;
	p->pushdown();
	if(Size(p->ls)>=k){
		res=split(p->ls,k);
		p->ls=res.second;
		p->maintain();
		res.second=p;
	}else{
		res=split(p->rs,k-Size(p->ls)-1);
		p->rs=res.first;
		p->maintain();
		res.first=p;
	}
	return res;
}

void reverse(int l,int r){
	nn cur=split(rt,r);
	nn res=split(cur.first,l-1);
	res.second->rev^=1;
	rt=merge(res.first,res.second);
	rt=merge(rt,cur.second);
}

void print(node *x){
	if(!x) return;
	x->pushdown();
	print(x->ls);
	printf("%d ",x->val);
	print(x->rs);
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;rt=NULL;
	for(int i=1;i<=n;i++)rt=merge(rt,newnode(i));
	for(int i=1;i<=m;i++){
		int l,r;scanf("%d%d",&l,&r);
		reverse(l,r);
	}
	print(rt);
	return 0;
}
