#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	node *ch[2],*fa;
	int size,rev;
	node(){ch[0]=ch[1]=fa=NULL;size=1,rev=0;}
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
		}
		rev=0;
	}
}*t[MAXN];

int n,m,a[MAXN];

int wh(node *p){
	return p->fa->ch[1]==p;
}

bool isroot(node *p){
	return (!p->fa) || (p->fa->ch[0]!=p && p->fa->ch[1]!=p);
}

void rot(node *p){
	node *f=p->fa,*g=f->fa;
	int c=wh(p);
	f->ch[c]=p->ch[!c];
	if(f->ch[c]) f->ch[c]->fa=f;
	p->fa=g;if(!isroot(f))g->ch[wh(f)]=p;
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

void link(node *p,node *q){
	makeroot(p);p->fa=q;
}

void cut(node *p,node *q){
	makeroot(p);access(q);splay(q);
	if(q->ch[0]==p && !p->ch[1]) q->ch[0]=p->fa=NULL;
	p->maintain();
}

void solve(){
	int opt,x,y;
	scanf("%d%d",&opt,&x);
	switch(opt){
		case 1:makeroot(t[n]);access(t[x]);splay(t[x]);cout<<t[x]->size-1<<endl;break;
		case 2:scanf("%d",&y);cut(t[x],x+a[x]<n?t[x+a[x]]:t[n]);a[x]=y;link(t[x],x+a[x]<n?t[x+a[x]]:t[n]);
	}
}

int main(){
    freopen("p3203.in","r",stdin);
    cin>>n;
    for(int i=0;i<=n;i++)t[i]=new node;
    for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
    	link(t[i],i+a[i]<n?t[i+a[i]]:t[n]);
    }
    cin>>m;
    while(m--) solve();
    return 0;
}