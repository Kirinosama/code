#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 100010
#define MAXM 200010

int n,last[MAXN],ne[MAXM],edge_cnt;
int val[MAXN],w[MAXN],dep[MAXN],father[MAXN],top[MAXN],tail[MAXN],son[MAXN];
int id[MAXN],size[MAXN],cnt;

struct node{
	node *ch[2];
	int MAX,add,flag;
	void update(){
		MAX=0;
		if(ch[0]) MAX=max(MAX,ch[0]->MAX);
		if(ch[1]) MAX=max(MAX,ch[1]->MAX);
	}
	void push_down(){
		if(flag){
			if(ch[0]){
				ch[0]->flag=1;
				ch[0]->add=0;
				ch[0]->MAX=MAX;
			}
			if(ch[1]){
				ch[1]->flag=1;
				ch[1]->add=0;
				ch[1]->MAX=MAX;
			}
			flag=0;
		}
		else if(add){
			if(ch[0])
				ch[0]->add+=add,ch[0]->MAX+=add;
			if(ch[1])
				ch[1]->add+=add,ch[1]->MAX+=add;
			add=0;
		}
	}
}*root;

struct edge{
	int x,y,z;
}E[MAXM];

void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs1(int x,int fa){
	father[x]=fa;
	dep[x]=dep[fa]+1;
	son[x]=0,size[x]=1;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa) continue;
		val[y]=E[i].z,dfs1(y,x);
		size[x]+=size[y];
		if(size[y]>size[son[x]])
			son[x]=y;
	}
}

void dfs2(int x,int tp){
	top[x]=tp;id[x]=++cnt;
	if(son[x]) dfs2(son[x],tp);
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==father[x] || y==son[x]) continue;
		dfs2(y,y);
	}
	tail[x]=cnt;
}

void build(node *&p,int l,int r){
	p=new node;
	p->ch[0]=p->ch[1]=NULL;
	p->flag=p->add=0;
	if(l==r) p->MAX=w[l];
	else{
		int mid=(l+r)>>1;
		build(p->ch[0],l,mid);
		build(p->ch[1],mid+1,r);
		p->update();
	}
}

void premake(){
	for(int i=1;i<n;i++){
		static int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		add_edge(x,y,z),add_edge(y,x,z);
	}
	dfs1(1,1);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
		w[id[i]]=val[i];
	build(root,1,n);
}

void change(node *&p,int l,int r,int L,int R,int k){
	if(l>R || r<L) return;
	if(l>=L && r<=R){
		p->flag=1;
		p->add=0;
		p->MAX=k;
		return;
	}
	if(l!=r){
		int mid=(l+r)>>1;
		p->push_down();
		change(p->ch[0],l,mid,L,R,k);
		change(p->ch[1],mid+1,r,L,R,k);
		p->update();
	}
}

void add(node *&p,int l,int r,int L,int R,int k){
	if(l>R || r<L) return;
	if(l>=L && r<=R){
		p->MAX+=k;
		return;
	}
	if(l!=r){
		int mid=(l+r)>>1;
		p->push_down();
		add(p->ch[0],l,mid,L,R,k);
		add(p->ch[1],mid+1,r,L,R,k);
		p->update();
	}
}

int query(node *p,int l,int r,int L,int R){
	int res=0;
	if(l>R || r<L) return 0;
	if(l>=L && r<=R){
		return p->MAX;
	}
	if(l!=r){
		int mid=(l+r)>>1;
		p->push_down();
		res=max(res,query(p->ch[0],l,mid,L,R));
		res=max(res,query(p->ch[1],mid+1,r,L,R));
		p->update();
		return res;
	}
	return 0;
}

void Query(int u,int v){
	int ans=0;
	while(u!=v){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		if(top[u]!=top[v])
			ans=max(ans,query(root,1,n,id[top[u]],id[u])),u=father[top[u]];
		else{
			if(dep[u]<dep[v]) swap(u,v);
			ans=max(ans,query(root,1,n,id[v]+1,id[u])),u=v;
		}
	}
	printf("%d\n",ans);
}

void cover(int u,int v,int k){
	while(u!=v){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		if(top[u]!=top[v])
			change(root,1,n,id[top[u]],id[u],k),u=father[top[u]];
		else{
			if(dep[u]<dep[v]) swap(u,v);
			change(root,1,n,id[v]+1,id[u],k),u=v;
		}
	}
}

void Add(int u,int v,int k){
	while(u!=v){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		if(top[u]!=top[v])
			add(root,1,n,id[top[u]],id[u],k),u=father[top[u]];
		else{
			if(dep[u]<dep[v]) swap(u,v);
			add(root,1,n,id[v]+1,id[u],k),u=v;
		}
	}
}

void solve(){
	char type[10];int u,v,k,x,y;
	while(1){
		scanf("%s",type);
		if(type[0]=='S') break;
		switch(type[1]){
			case 'h':
				scanf("%d %d",&u,&k);
				x=E[u*2-1].x,y=E[u*2-1].y;
				if(dep[x]<dep[y]) swap(x,y);
				change(root,1,n,id[x],id[x],k);break;
			case 'o':
				scanf("%d %d %d",&u,&v,&k);
				cover(u,v,k);break;
			case 'd':
				scanf("%d %d %d",&u,&v,&k);
				Add(u,v,k);break;
			case 'a':
				scanf("%d %d",&u,&v);
				Query(u,v);
		}
	}
}

int main(){
	freopen("bzoj1984.in","r",stdin);
	freopen("out1","w",stdout);
	scanf("%d",&n);
	premake();
	solve();
	return 0;
}
