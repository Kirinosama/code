#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 100100
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

struct node{
	node *ch[2];
	int sum,rcol,lcol,tag;
	node (){ch[0]=ch[1]=NULL;sum=rcol=lcol=tag=0;}
	void pushdown(){
		if(tag){
			ch[0]->tag=ch[0]->sum=1;
			ch[0]->lcol=ch[0]->rcol=lcol;
			ch[1]->tag=ch[1]->sum=1;
			ch[1]->lcol=ch[1]->rcol=lcol;
			tag=0;
		}
	}
	void maintain(){
		rcol=ch[1]->rcol;
		lcol=ch[0]->lcol;
		sum=ch[0]->sum+ch[1]->sum-(ch[0]->rcol==ch[1]->lcol);
	}
}*root;

int last[MAXN],ne[MAXM],edge_cnt,ti;
int n,m,a[MAXN],top[MAXN],dep[MAXN],dfn[MAXN];
int fa[MAXN],ID[MAXN],size[MAXN],son[MAXN];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void merge(node *&ans,node *p,int l,int r,int L,int R){
	if(l>R||r<L)return;
	if(l>=L && r<=R){
		if(l==L) ans->lcol=p->lcol;
		ans->sum+=p->sum-(ans->rcol==p->lcol);
		ans->rcol=p->rcol;
	}else{
		int mid=(l+r)>>1;
		p->pushdown();
		merge(ans,ls,l,mid,L,R);
		merge(ans,rs,mid+1,r,L,R);
		p->maintain();
	}
}

void make(node *p,int l,int r,int L,int R,int z){
	if(l>R || r<L) return;
	if(l>=L && r<=R){
		p->lcol=p->rcol=z;
		p->sum=1;p->tag=1;
	}else{
		int mid=(l+r)>>1;
		p->pushdown();
		make(ls,l,mid,L,R,z);
		make(rs,mid+1,r,L,R,z);
		p->maintain();
	}
}

void change(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		make(root,1,n,dfn[top[x]],dfn[x],z);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	make(root,1,n,dfn[y],dfn[x],z);
}

void Query(int x,int y){
	queue <ii> q1;stack <ii> q2;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			q1.push(ii(dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}else{
			q2.push(ii(dfn[top[y]],dfn[y]));
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]) q1.push(ii(dfn[y],dfn[x]));
	else q2.push(ii(dfn[x],dfn[y]));
	int sum=0,lcol=0,rcol=0;
	while(!q1.empty()){
		ii cur=q1.front();q1.pop();
		node *ans=new node;
		merge(ans,root,1,n,cur.first,cur.second);
		sum+=ans->sum;sum-=(lcol==ans->rcol),lcol=ans->lcol;
	}swap(lcol,rcol);
	while(!q2.empty()){
		ii cur=q2.top();q2.pop();
		node *ans=new node;
		merge(ans,root,1,n,cur.first,cur.second);
		sum+=ans->sum;sum-=(rcol==ans->lcol),rcol=ans->rcol;
	}
	printf("%d\n",sum);
}

void solve(){
	char ch[5];
	int x,y,z;
	scanf("%s",ch);
	switch(ch[0]){
		case 'Q':
			scanf("%d %d",&x,&y);
			Query(x,y);
			break;
		case 'C':
			scanf("%d %d %d",&x,&y,&z);
			change(x,y,z);
	}
}

void dfs1(int x,int f){
	fa[x]=f;size[x]=1;son[x]=0;dep[x]=dep[f]+1;
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f){
		int y=E[i].y;dfs1(y,x);
		size[x]+=size[y];
		if(size[y]>size[son[x]])son[x]=y;
	}
}

void dfs2(int x,int tp){
	dfn[x]=++ti;ID[ti]=x;
	top[x]=tp;
	if(son[x])dfs2(son[x],tp);
	for(int i=last[x];i;i=ne[i])if(E[i].y!=fa[x] && E[i].y!=son[x]){
		dfs2(E[i].y,E[i].y);
	}
}

void build(node *&p,int l,int r){
	p=new node;
	if(l==r){
		p->lcol=p->rcol=a[ID[l]];
		p->sum=1;
	}else{
		int mid=(l+r)>>1;
		build(ls,l,mid);build(rs,mid+1,r);
		p->maintain();
	}
}

int main(){
    freopen("p2486.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<n;i++){
    	static int x,y;
    	scanf("%d %d",&x,&y);
    	add_edge(x,y),add_edge(y,x);
    }
    dfs1(1,1);
    dfs2(1,1);
    build(root,1,n);
    while(m--)
    	solve();
    return 0;
}