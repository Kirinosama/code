#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 600010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	node *ch[2],*fa;
	int key,Xor,rev;
	node(){ch[0]=ch[1]=fa=NULL,Xor=key=rev=0;}
	void pushdown(){
		if(rev){
			swap(ch[0],ch[1]);
			if(ch[0])ch[0]->rev^=1;
			if(ch[1])ch[1]->rev^=1;
		}
		rev=0;
	}
	void maintain(){
		Xor=key;
		if(ch[0]) Xor^=ch[0]->Xor;
		if(ch[1]) Xor^=ch[1]->Xor;
	}
}*t[MAXN];

int n,m,a[MAXN];

bool isroot(node *p){
	if(!p->fa) return true;
	return p->fa->ch[0]!=p && p->fa->ch[1]!=p;
}

int wh(node *p){
	return p->fa->ch[1]==p;
}

void rot(node* p){
	node *f=p->fa,*g=f->fa;
	int c=wh(p);
	f->ch[c]=p->ch[!c];
	if(f->ch[c]) f->ch[c]->fa=f;
	p->fa=g;if(!isroot(f)) g->ch[wh(f)]=p;
	p->ch[!c]=f;f->fa=p;
	f->maintain();p->maintain();
}

void pushup(node *p){
	if(!isroot(p)) pushup(p->fa);
	p->pushdown();
}

void splay(node *p){
	pushup(p);
	for(;!isroot(p);rot(p))if(!isroot(p->fa))
		rot(wh(p->fa)^wh(p)?p:p->fa);
}

void access(node *p){
	for(node *cur=NULL;p;cur=p,p=p->fa){
		splay(p);p->ch[1]=cur;
		p->maintain();
	}
}

void makeroot(node *p){
	access(p);splay(p);
	p->rev^=1;
}

node * find(node* p){
	access(p);splay(p);
	while(p->ch[0]) p=p->ch[0];
	return p;
}

void cut(node *p,node *q){
	makeroot(p);access(q);splay(q);
	if(q->ch[0]==p && !p->ch[1]) q->ch[0]=NULL,p->fa=NULL;
	q->maintain();
}

void link(node *p,node *q){
	makeroot(p);p->fa=q;
}

void solve(){
	int opt,x,y;
	scanf("%d%d%d",&opt,&x,&y);
	switch(opt){
		case 0:makeroot(t[x]),access(t[y]),splay(t[y]);cout<<t[y]->Xor<<endl;break;
		case 1:if(find(t[x])!=find(t[y])) link(t[x],t[y]);break;
		case 2:cut(t[x],t[y]);break;
		case 3:makeroot(t[x]);t[x]->key=y;t[x]->maintain();
	}
}

int main(){
    freopen("p3690.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	t[i]=new node;
    	scanf("%d",&t[i]->key);
    	t[i]->Xor=t[i]->key;
    }
    while(m--) solve();
    return 0;
}