#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 10010
#define MAXM 1010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	int lx,ly,rx,ry;
	node* ch[2];
	node(){ch[0]=ch[1]=NULL;}
	void maintain(){
		lx=min(ch[0]->lx,ch[1]->lx);
		ly=min(ch[0]->ly,ch[1]->ly);
		rx=max(ch[0]->rx,ch[1]->rx);
		ry=max(ch[0]->ry,ch[1]->ry);
	}
}*root;

int tot,n,m,sx,sy,ex,ey,S,T;
int dis[MAXM*MAXM],res,ans1;
int fa[MAXM*MAXM],dist[MAXM*MAXM];

struct Point{
	int ID;
	bool operator < (const Point &a)const{
		return dis[ID]>dis[a.ID];
	}
}D[MAXM*MAXM];

struct point{
	int x,y;
}t[MAXN];

inline int P(int x,int y){
	return x*m+y;
}

bool cmp1(const point &a,const point &b){
	return a.x<b.x;
}

bool cmp2(const point &a,const point &b){
	return a.y<b.y;
}

void build(node *&p,int l,int r,int opt){
	p=new node;
	if(l==r){
		p->lx=p->rx=t[l].x;
		p->ly=p->ry=t[l].y;
		return;
	}else{
		int mid=(l+r)>>1;
		if(!opt) nth_element(t+l,t+mid,t+r+1,cmp1);
		else nth_element(t+l,t+mid,t+r+1,cmp2);
		build(ls,l,mid,opt^1);build(rs,mid+1,r,opt^1);
		p->maintain();
	}
}

inline bool judge(node *p,int x,int y){
	int sum=0;
	sum+=min(abs(p->lx-x),abs(p->rx-x));
	sum+=min(abs(p->ly-y),abs(p->ry-y));
	return sum<res;
}

void query(node *p,int l,int r,int opt,int x,int y){
	if(l==r){
		res=min(res,abs(p->lx-x)+abs(p->ly-y));
		return;
	}else{
		int mid=(l+r)>>1;
		if(!opt){
			if(x<=ls->rx){
				query(ls,l,mid,opt^1,x,y);
				if(judge(rs,x,y)) query(rs,mid+1,r,opt^1,x,y);
			}else{
				query(rs,mid+1,r,opt^1,x,y);
				if(judge(ls,x,y)) query(ls,l,mid,opt^1,x,y);
			}
		}else{
			if(x<=ls->ry){
				query(ls,l,mid,opt^1,x,y);
				if(judge(rs,x,y)) query(rs,mid+1,r,opt^1,x,y);
			}else{
				query(rs,mid+1,r,opt^1,x,y);
				if(judge(ls,x,y)) query(ls,l,mid,opt^1,x,y);
			}
		}
	}
}

inline int find(int x){
	return fa[x]==x?fa[x]:fa[x]=find(fa[x]);
}

inline void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy) fa[fx]=fy;
}

inline void add(int x){
	int tx=x/m,ty=x%m;
	if(tx-1>=0 && dis[x-m]>=dis[x]) merge(x,x-m);
	if(tx+1<n && dis[x+m]>=dis[x]) merge(x,x+m);
	if(ty-1>=0 && dis[x-1]>=dis[x]) merge(x,x-1);
	if(ty+1<m && dis[x+1]>=dis[x]) merge(x,x+1);
}

void bfs(){
	queue <int> Q;
	memset(dist,0x3f,sizeof(dist));
	dist[S]=0;Q.push(S);
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		int tx=x/m,ty=x%m;
		if(x==T){
			cout<<dist[x];
			return;
		}
		if(tx-1>=0 && dis[x-m]>=ans1 && dist[x-m]==INF) dist[x-m]=dist[x]+1,Q.push(x-m);
		if(tx+1<n && dis[x+m]>=ans1 && dist[x+m]==INF) dist[x+m]=dist[x]+1,Q.push(x+m);
		if(ty-1>=0 && dis[x-1]>=ans1 && dist[x-1]==INF) dist[x-1]=dist[x]+1,Q.push(x-1);
		if(ty+1<m && dis[x+1]>=ans1 && dist[x+1]==INF) dist[x+1]=dist[x]+1,Q.push(x+1);
	}
}

int main(){
    freopen("escape.in","r",stdin);
    freopen("escape.out","w",stdout);
    cin>>tot>>n>>m;
    cin>>sx>>sy>>ex>>ey;
    S=sx*m+sy,T=ex*m+ey;
    for(int i=1;i<=tot;i++) scanf("%d%d",&t[i].x,&t[i].y);
    build(root,1,tot,0);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			res=INF;query(root,1,tot,0,i,j);
			dis[P(i,j)]=res;
		}
	for(int i=0;i<n*m;i++) D[i].ID=fa[i]=i;
	sort(D,D+n*m);
	for(int i=0;i<n*m;i++){
		add(D[i].ID);
		if(find(S)==find(T)){
			ans1=dis[D[i].ID];
			cout<<ans1<<' ';
			break;
		}
	}
	bfs();
    return 0;
}