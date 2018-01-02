#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m;
char a[MAXN];

struct node{
	node *ch[2],*fa;
	int sum,c,size,rev,opt;
	int lmax,lmin,rmax,rmin;
	void update(){
		if(!ch[0] && !ch[1]){
			lmin=min(0,c);lmax=max(0,c);
			rmin=min(0,c);rmax=max(0,c);
		}
		size=1;sum=c;
		if(ch[0]){
			sum+=ch[0]->sum;
			lmin=min(ch[0]->lmin,ch[0]->sum+c+(ch[1]?ch[1]->lmin:0));
			lmax=max(ch[0]->lmax,ch[0]->sum+c+(ch[1]?ch[1]->lmax:0));
			size+=ch[0]->size;
		}
		if(ch[1]){
			sum+=ch[1]->sum;
			rmin=min(ch[1]->rmin,ch[1]->sum+c+(ch[0]?ch[0]->rmin:0));
			rmax=max(ch[1]->rmax,ch[1]->sum+c+(ch[0]?ch[0]->rmax:0));
			size+=ch[1]->size;
		}
	}
	void pushdown(){
		if(rev){
			swap(ch[0],ch[1]);
			if(ch[0]) ch[0]->rev^=1;
			if(ch[1]) ch[1]->rev^=1;
			rev=0;
		}
		if(opt){
			sum=-sum;
			int x=lmin;
			lmin=-lmax;
			lmax=-x;
			x=rmin;
			rmin=-rmax;
			rmax=-rmin;
			if(ch[0]) ch[0]->opt^=1;
			if(ch[1]) ch[1]->opt^=1;
			opt=0;
		}
	}
}*root;

void build(node *&p,int l,int r){
	int mid=(l+r)>>1;
	p=new node;p->rev=p->opt=0;
	if(mid==0 || mid==n+1) p->c=0; 
	else p->c=a[mid]=='('?1:-1;
	p->sum=p->c;
	p->ch[0]=p->ch[1]=NULL;
	if(l==r){
		p->lmin=min(0,p->c);p->lmax=max(0,p->c);
		p->rmin=min(0,p->c);p->rmax=max(0,p->c);
		p->size=1;
		return;	
	}
	if(l<mid) build(p->ch[0],l,mid-1),p->ch[0]->fa=p;
	if(r>mid) build(p->ch[1],mid+1,r),p->ch[1]->fa=p;
	p->update();
}

node* find(int x){
	int lcnt;node *cur=root;
	while((lcnt=cur->ch[0]?cur->ch[0]->size:0)+1!=x){
		cur->pushdown();
		if(x<=lcnt) cur=cur->ch[0];
		else cur=cur->ch[1],x-=lcnt+1;
	}
	cur->pushdown();
	return cur;
}

int cal(node *p){
	int t1=-p->lmin;
	int t2=p->rmax;
	return (t1+1)/2+(t2+1)/2;
}

int gets(node *p){
	return p->fa->ch[1]==p;
}

void rot(node *&p){
	node *f=p->fa,*g=f->fa;
	int c=gets(p);
	f->ch[c]=p->ch[!c];
	if(f->ch[c]) f->ch[c]->fa=f;
	p->fa=g;if(g) g->ch[gets(f)]=p;
	p->ch[!c]=f;f->fa=p;
	f->update(),p->update();
	if(f==root) root=p;
}

void splay(node *p){
	for(node *cur=p;cur->fa;rot(cur)){
		if(cur->fa->fa)
			rot(gets(cur->fa)==gets(cur)?cur->fa:cur);
	}
}

void query(int l,int r){
	node *x=find(l);
	node *y=find(r+2);
	splay(y),splay(x);
	printf("%d\n",cal(root->ch[1]->ch[0]));
}

void change(int l,int r){
	node *x=find(l);
	node *y=find(r+2);
	splay(y),splay(x);
	root->ch[1]->ch[0]->opt^=1;
}

void reverse(int l,int r){
	node *x=find(l);
	node *y=find(r+2);
	splay(y),splay(x);
	root->ch[1]->ch[0]->rev^=1;
}

void solve(){
	int type,l,r;
	scanf("%d %d %d",&type,&l,&r);
	switch(type){
		case 0:
			query(l,r);
			break;
		case 1:
			change(l,r);
			break;
		case 2:
			reverse(l,r);
	}
}

int main(){
    freopen("bzoj2209.in","r",stdin);
    scanf("%d %d\n",&n,&m);
    for(int i=1;i<=n;i++)
    	scanf("%c",&a[i]);
    build(root,0,n+1);root->fa=NULL;
    while(m--)
    	solve();
    return 0;
}