#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 500010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
#define SIZE(x) ((ll)(x->ry-x->ly+1)*(ll)(x->rx-x->lx+1))
typedef long long ll;

int n,m,sx,sy,t;
ll a[MAXN];

struct node{
	int lx,ly,rx,ry;
	ll sum,add;
	node *ch[4];
	void push_down(){
		for(int i=0;i<4;i++)
			if(ch[i]){
				ch[i]->sum+=SIZE(ch[i])*add;
				ch[i]->add+=add;
			}
		add=0;
	}
	void maintain(){
		sum=0;
		for(int i=0;i<4;i++)
			if(ch[i])
				sum+=ch[i]->sum;
	}
}*root;

void newnode(node *&p){
	p=new node;
	p->sum=p->add=0;
	for(int i=0;i<4;i++)
		p->ch[i]=NULL;
}

void build(node *&p,int lx,int ly,int rx,int ry){
	p=new node;p->lx=lx,p->ly=ly,p->rx=rx,p->ry=ry;
	if(lx==rx && ly==ry){
		p->add=0;p->sum=a[(lx-1)*m+ly];
		return;
	}
	else if(lx==rx){
		int mid=(ly+ry)>>1;
		build(p->ch[0],lx,ly,lx,mid);
		build(p->ch[3],lx,mid+1,lx,ry);
	}
	else if(ly==ry){
		int mid=(lx+rx)>>1;
		build(p->ch[0],lx,ly,mid,ly);
		build(p->ch[3],mid+1,ly,rx,ly);
	}
	else{
		int midx=(lx+rx)>>1;
		int midy=(ly+ry)>>1;
		build(p->ch[0],lx,ly,midx,midy);
		build(p->ch[1],lx,midy+1,midx,ry);
		build(p->ch[2],midx+1,ly,rx,midy);
		build(p->ch[3],midx+1,midy+1,rx,ry);
	}
	p->maintain();
}

ll query(node *p,int lx,int ly,int rx,int ry){
	if(!p) return 0;
	if(max(p->lx,lx)<=min(p->rx,rx) && max(p->ly,ly)<=min(p->ry,ry)){
		if(p->lx>=lx && p->ly>=ly && p->rx<=rx && p->ry<=ry)
			return p->sum;
		p->push_down();ll tot=0;
		for(int i=0;i<4;i++)
			tot+=query(p->ch[i],lx,ly,rx,ry);
		return tot;
	}
	return 0;
}

void add(node *&p,int lx,int ly,int rx,int ry,ll c){
	if(!p) return;
	if(max(p->lx,lx)<=min(p->rx,rx) && max(p->ly,ly)<=min(p->ry,ry)){
		if(p->lx>=lx && p->ly>=ly && p->rx<=rx && p->ry<=ry){
			p->sum+=c*SIZE(p);p->add+=c;return;
		}
		p->push_down();
		for(int i=0;i<4;i++)
			add(p->ch[i],lx,ly,rx,ry,c);
	}

}

void solve(){
	int type,lx,ly,rx,ry;ll c;
	scanf("%d %d %d %d %d",&type,&lx,&ly,&rx,&ry);
	switch(type){
		case 0:
			printf("%lld\n",query(root,lx,ly,rx,ry));
			break;
		case 1:
			scanf("%lld",&c);
			add(root,lx,ly,rx,ry,c);
	}
}

int main(){
    freopen("bzoj2877.in","r",stdin);
    scanf("%d %d %d",&n,&m,&t);
    for(int i=1;i<=n*m;i++)
    	scanf("%lld",&a[i]);
    build(root,1,1,n,m);
    while(t--)
    	solve();
    return 0;
}