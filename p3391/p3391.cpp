#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	int size,ID,rev;
	node *ch[2],*fa;
	node(){size=1,ID=rev=0;ch[0]=ch[1]=fa=NULL;}
	void maintain(){
		size=1;
		if(ch[0]) size+=ch[0]->size;
		if(ch[1]) size+=ch[1]->size;
	}
	void pushdown(){
		if(rev){
			if(ch[0]) ch[0]->rev^=1;
			if(ch[1]) ch[1]->rev^=1;
			swap(ch[0],ch[1]);
			rev=0;
		}
	}
}*root;

int n,m;

void build(node *&p,int l,int r){
	p=new node;
	int mid=(l+r)>>1;
	p->ID=mid;
	if(l!=r){
		int mid=(l+r)>>1;
		if(l<=mid-1)build(ls,l,mid-1),ls->fa=p;
		if(mid+1<=r)build(rs,mid+1,r),rs->fa=p;
		p->maintain();
	}
}

node * find(int x){
	node *p=root;
	while(1){
		p->pushdown();
		int lcnt=ls?ls->size:0;
		if(x<=lcnt) p=ls;
		else if(x==lcnt+1) return p;
		else x-=lcnt+1,p=rs;
	}
}

void pushup(node *p){
	if(p!=root) pushup(p->fa);
	p->pushdown();
}

int wh(node *p){
	return p->fa->ch[1]==p;
}

void rot(node *p){
	node *f=p->fa,*g=f->fa;
	int c=wh(p);
	f->ch[c]=p->ch[!c];
	if(f->ch[c]) f->ch[c]->fa=f;
	p->fa=g;if(g) g->ch[wh(f)]=p;
	p->ch[!c]=f;f->fa=p;
	if(f==root) root=p;
	f->maintain(),p->maintain();
}

void splay(node *p){
	pushup(p);
	for(;p!=root;rot(p))
		if(p->fa!=root && p->fa->fa!=root)
			rot(wh(p->fa)==wh(p)?p->fa:p);
}

void print(node *p){
	p->pushdown();
	if(ls) print(ls);
	if(p->ID>=1 && p->ID<=n) printf("%d ",p->ID);
	if(rs) print(rs);
}

int main(){
    freopen("p3391.in","r",stdin);
    cin>>n>>m;build(root,0,n+1);
    for(int i=1;i<=m;i++){
    	int l,r;
    	scanf("%d%d",&l,&r);
    	node *p=find(r+2);splay(p);
    	node *q=find(l);splay(q);
    	p->ch[0]->rev^=1;
    }
    print(root);
    return 0;
}