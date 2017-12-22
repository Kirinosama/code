#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 500010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct point{
	int x,y;
}poi[MAXN];

struct node{
	int x,y,lx,ly,rx,ry;
	node *ch[2];
	void update(){
		lx=rx=x;ly=ry=y;
		if(ch[0]){
			lx=min(lx,ch[0]->lx),rx=max(rx,ch[0]->rx);
			ly=min(ly,ch[0]->ly),ry=max(ry,ch[0]->ry);
		}
		if(ch[1]){
			lx=min(lx,ch[1]->lx),rx=max(rx,ch[1]->rx);
			ly=min(ly,ch[1]->ly),ry=max(ry,ch[1]->ry);
		}
	}
}*root;

int n,CMP,ans,X,Y,Min,Max;

bool cmp(const point &a,const point &b){
	if(!CMP) return a.x<b.x;
	else return a.y<b.y;
}

void newnode(node *&p){
	p=new node;
	p->ch[0]=p->ch[1]=NULL;	
}

void build(node *&p,int d,int l,int r){
	p=new node();
	int mid=(l+r)>>1;CMP=d;
	nth_element(poi+l,poi+mid,poi+r+1,cmp);
	p->x=poi[mid].x,p->y=poi[mid].y;
	if(l<mid)build(p->ch[0],d^1,l,mid-1);
	if(r>mid)build(p->ch[1],d^1,mid+1,r);
	p->update();
}

int choose(int X,int Y,int x,int y,int d){
	if(!d) return X>=x;
	else return Y>=y; 
}

int dis(int X,int Y,int x,int y){
	return abs(x-X)+abs(y-Y);
}

void query_min(node *p,int d){
	if(!p->ch[0] && !p->ch[1]){
		if(p->x!=X || p->y!=Y)
			Min=min(Min,dis(p->x,p->y,X,Y));
		return;
	}
	int c=choose(X,Y,p->x,p->y,d);
	if(p->ch[c]) query_min(p->ch[c],d^1);
	if(p->x!=X || p->y!=Y)Min=min(Min,dis(p->x,p->y,X,Y));
	if(!d){
		if(!c && X+Min<=p->x) return;
		if(c && X-Min>=p->x) return;
	}
	else{
		if(!c && Y+Min<=p->y) return;
		if(c && Y-Min>=p->y) return; 
	}
	if(p->ch[!c]) query_min(p->ch[!c],d^1);
}

void query_max(node *p,int d){
	if(!p->ch[0] && !p->ch[1]){
		Max=max(Max,dis(p->x,p->y,X,Y));
		return;
	}
	int c=choose(X,Y,p->x,p->y,d);
	if(p->ch[!c]) query_max(p->ch[!c],d^1);
	Max=max(Max,dis(p->x,p->y,X,Y));
	if(!d){
		if(!c && max(p->x-X,X-p->lx)+max(p->ry-Y,Y-p->ly)<=Max) return;
		if(c && max(X-p->x,p->rx-X)+max(p->ry-Y,Y-p->ly)<=Max) return;
	}
	else{
		if(!c && max(p->rx-X,X-p->lx)+max(p->y-Y,Y-p->ly)<=Max) return;
		if(c && max(p->rx-X,X-p->lx)+max(p->ry-Y,Y-p->y)<=Max) return; 
	}
	if(p->ch[c]) query_max(p->ch[c],d^1);
}

int main(){
    freopen("bzoj1941.in","r",stdin);
    freopen("out1","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d %d",&poi[i].x,&poi[i].y);
    }
    build(root,0,1,n);ans=1e9;
    for(int i=1;i<=n;i++){
    	X=poi[i].x,Y=poi[i].y;
    	Min=1e9,Max=-1e9;
    	query_min(root,0);
    	query_max(root,0);
    	ans=min(ans,Max-Min);
    }
    printf("%d",ans);
    return 0;
}