#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 100010
#define ii pair<int,int>
#define INF 1e12
typedef long long ll;

inline ll read(){
	ll x=0;int w=0;char ch;
	while(ch<'0' || ch>'9') w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

struct node{
	node *ch[2];
	ll Min;int tag;
	node(){ch[0]=ch[1]=NULL,Min=tag=0;}
	void maintain(){
		Min=min(ch[0]->Min,ch[1]->Min);
	}
	void pushdown(){
		if(tag){
			if(ch[0]) ch[0]->Min=Min,ch[0]->tag=1;
			if(ch[1]) ch[1]->Min=Min,ch[1]->tag=1;
			tag=0;
		}
	}
}*root;

int n,m,rt,son[MAXN],size[MAXN],fa[MAXN],dep[MAXN];
int dfn[MAXN],pos[MAXN],top[MAXN],tail[MAXN],ti;
ll a[MAXN];
vector <int> to[MAXN];

void dfs1(int x,int f){
	dep[x]=dep[f]+1;fa[x]=f;size[x]=1;son[x]=0;
	for(int i=0;i<to[x].size();i++){
		int y=to[x][i];
		if(y==f) continue;
		dfs1(y,x);size[x]+=size[y];
		if(size[y]>size[son[x]])son[x]=y;
	}
}

void dfs2(int x,int tp){
	dfn[x]=++ti;pos[ti]=x;top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=0;i<to[x].size();i++){
		int y=to[x][i];
		if(y==fa[x] || y==son[x]) continue;
		dfs2(y,y);
	}
	tail[x]=ti;
}

void build(node *&p,int l,int r){
	p=new node;
	if(l==r){
		p->Min=a[pos[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	p->maintain();
}

void premake(){
	dfs1(1,1);
	dfs2(1,1);
	build(root,1,n);
}

inline int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) return x;
	else return y;
}

void change(node *p,int l,int r,int L,int R,ll k){
	if(l>R || r<L) return;
	if(l>=L && r<=R) p->Min=k,p->tag=1;
	else{
		int mid=(l+r)>>1;
		p->pushdown();
		change(ls,l,mid,L,R,k);
		change(rs,mid+1,r,L,R,k);
		p->maintain();
	}
}

void Change(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		change(root,1,n,dfn[top[x]],dfn[x],z);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	change(root,1,n,dfn[y],dfn[x],z);
}

ll query(node *p,int l,int r,int L,int R){
	if(L>R) return INF;
	if(l>R || r<L) return INF;
	if(l>=L && r<=R) return p->Min;
	else{
		int mid=(l+r)>>1;
		p->pushdown();
		ll res=min(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
		p->maintain();
		return res;
	}
}

ll Query(int x){
	if(x==rt) return root->Min;
	if(lca(x,rt)==x){
		for(int i=0;i<to[x].size();i++){
			if(to[x][i]!=fa[x] && lca(to[x][i],rt)==to[x][i])
				return min(query(root,1,n,1,dfn[to[x][i]]-1),query(root,1,n,tail[to[x][i]]+1,n));
		}
	}else{
		return query(root,1,n,dfn[x],tail[x]); 
	}
	return INF;
}

void solve(){
	int opt=read(),x,y;ll z;
	switch(opt){
		case 1:rt=read();break;
		case 2:
			x=read(),y=read(),z=read();
			Change(x,y,z);break;
		case 3:
			x=read();printf("%lld\n",Query(x));
	}
}

int main(){
    freopen("bzoj3083.in","r",stdin);
    freopen("out1","w",stdout);
    n=read(),m=read();
    for(int i=1;i<n;i++){
    	int x=read(),y=read();
    	to[x].push_back(y),to[y].push_back(x);
    }
    for(int i=1;i<=n;i++)a[i]=read();
    premake();
    rt=read();
	while(m--)solve();
    return 0;
}
