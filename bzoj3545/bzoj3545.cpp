#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 100010
#define MAXM 500010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y,z;
	bool operator < (const edge &a)const{
		return z<a.z;
	}
}E[MAXM];

struct query{
	int v,x,k,ID;
	bool operator < (const query &a)const{
		return x<a.x;
	}
}q[MAXM];

struct node{
	int num;
	node *ch[2];
	node(){ch[0]=ch[1]=NULL,num=0;}
}*root[MAXN];

int n,m,Q,cnt;
int fa[MAXN],h[MAXN],ans[MAXM],tmp[MAXN];

inline int read(){
	int x=0,w=0;char ch;
	while(ch<'0' || ch>'9') w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

inline int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

inline node* merge(node *p,node *q,int l,int r){
	if(!q) return p;
	if(!p) return q;
	p->num+=q->num;
	if(l==r){
		delete(q);
		return p;
	}
	int mid=(l+r)>>1;
	ls=merge(ls,q->ch[0],l,mid);
	rs=merge(rs,q->ch[1],mid+1,r);
	delete(q);
	return p;
}

inline void make(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy) return;
	root[fy]=merge(root[fy],root[fx],1,cnt);
	fa[fx]=fy;
}

inline void build(node *&p,int l,int r,int pos){
	p=new node;p->num=1;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) build(ls,l,mid,pos);
	else build(rs,mid+1,r,pos);
}

inline void premake(){
	for(int i=1;i<=n;i++) tmp[i]=h[i];
	sort(tmp+1,tmp+1+n);
	for(int i=1;i<=n;i++){
		h[i]=lower_bound(tmp+1,tmp+1+n,h[i])-tmp;
		cnt=max(cnt,h[i]);
	}
	for(int i=1;i<=n;i++)
		build(root[i],1,cnt,h[i]);
}

inline int ask(node *p,int l,int r,int k){
	if(l==r) return l;
	int mid=(l+r)>>1;
	int lcnt=ls?ls->num:0;
	if(k<=lcnt) return ask(ls,l,mid,k);
	else return ask(rs,mid+1,r,k-lcnt);
}

inline int solve(int x,int k){
	int fx=find(x);int tot=root[fx]->num;
	if(tot<k) return -1;
	return tmp[ask(root[fx],1,cnt,tot-k+1)];
}

int main(){
    freopen("bzoj3545.in","r",stdin);
    n=read(),m=read(),Q=read();
    for(int i=1;i<=n;i++) h[i]=read(),fa[i]=i;
    for(int i=1;i<=m;i++) E[i].x=read(),E[i].y=read(),E[i].z=read();
    for(int i=1;i<=Q;i++) q[i].v=read(),q[i].x=read(),q[i].k=read(),q[i].ID=i;
    sort(q+1,q+1+Q);sort(E+1,E+m+1);premake();int pos=0;
	for(int i=1;i<=Q;i++){
		int tx=q[i].x;
		while(pos<m && E[pos+1].z<=tx){
			make(E[pos+1].x,E[pos+1].y);
			pos++;
		}
		ans[q[i].ID]=solve(q[i].v,q[i].k);
	}
	for(int i=1;i<=Q;i++) printf("%d\n",ans[i]);
    return 0;
}