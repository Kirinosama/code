#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 800010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,a[MAXN];

struct node{
	node *ch[2],*fa;
	int ID,rev,size;
	node(){ch[0]=ch[1]=fa=NULL;rev=ID=size=0;}
	void maintain(){
		size=1;
		if(ch[0])size+=ch[0]->size;
		if(ch[1])size+=ch[1]->size;
	}
	void pushdown(){
		if(rev){
			swap(ch[0],ch[1]);
			if(ch[0]) ch[0]->rev^=1;
			if(ch[1]) ch[1]->rev^=1;
			rev=0;
		}
	}
}*root,*pos[MAXN];

void pushup(node *p){
	if(p->fa) pushup(p->fa);
	p->pushdown();
}

int wh(node *p){
	return p->fa->ch[1]==p;
}

void rot(node *p){
	node *f=p->fa,*g=f->fa;
	int c=wh(p);
	f->ch[c]=p->ch[!c];
	if(f->ch[c])f->ch[c]->fa=f;
	if(g) g->ch[wh(f)]=p;
	p->fa=g;
	p->ch[!c]=f;f->fa=p;
	if(f==root) root=p;
	f->maintain();p->maintain();
}

void splay(node *p){
	pushup(p);
	for(;p!=root;rot(p)){
		if(p->fa!=root && p->fa->fa!=root)
			rot(wh(p->fa)==wh(p)?p->fa:p);
	}
}

int Rank(int x){
	splay(pos[x]);
	return pos[x]->ch[0]->size;
}

node* find(int x){
	node *p=root;
	while(1){
		p->pushdown();
		int lcnt=ls?ls->size:0;
		if(x<=lcnt) p=ls;
		else if(x==lcnt+1) return p;
		else p=rs,x-=lcnt+1;
	}
}

void reverse(int l,int r){
	node *p=find(r+2);splay(p);
	node *q=find(l);splay(q);
	p->ch[0]->rev^=1;
}

void build(node *&p,int l,int r){
	p=new node;
	int mid=(l+r)>>1;
	p->ID=a[mid];pos[a[mid]]=p;p->size=1;
	if(l==r) return;
	if(l<mid) build(ls,l,mid-1),ls->fa=p;
	if(r>mid) build(rs,mid+1,r),rs->fa=p;
	p->maintain();
}


void solve(){
	char opt[7];
	int x,y,w;
	scanf("%s %d",opt,&x);
	switch(opt[0]){
		case 'Q':printf("%d\n",find(x+1)->ID);break;
		case 'T':w=Rank(x);reverse(1,w);reverse(2,w);break;
		case 'A':printf("%d\n",Rank(x)-1);break;
		case 'B':w=Rank(x);reverse(w,n);reverse(w,n-1);break;
		case 'I':scanf("%d",&y);w=Rank(x);
		if(y==-1)reverse(w-1,w);
		else reverse(w,w+1);
	}
}

int main(){
    freopen("book.in","r",stdin);
    freopen("book.out","w",stdout);    
    cin>>n>>m;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(root,0,n+1);
    while(m--)
    	solve();
    return 0;
}