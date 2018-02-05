#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 10010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

struct node{
	node *ch[2];
	int sum,rcol,lcol;
	node (){ch[0]=ch[1]=NULL;sum=rcol=lcol=0;}
	node (const node *a,const node *b){
		ch[0]=ch[1]=NULL;
		sum=a->sum+b->sum;
		rcol=b->rcol,lcol=a->lcol;
	}
	void maintain(){
		rcol=ch[1]->rcol;
		lcol=ch[0]->lcol;
		sum=ch[0]->sum+ch[1]->sum-(ch[0]->rcol==ch[1]->lcol);
	}
}*root;

int last[MAXN],ne[MAXM],edge_cnt,ti;
int n,m,a[MAXN],top[MAXN],dep[MAXN],dfn[MAXN];
int fa[MAXN],id[MAXN],size[MAXN],son[MAXN];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void Query(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			q1.push(ii(dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}else{
			q2.push(ii(dfn[top[y]],dfn[y]));
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]) 
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
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y!=f)dfs1(y,x);
		size[x]+=size[y];
		if(size[y]>size[son[x]])
			son[x]=y;
	}
}

void dfs2(int x,int tp){
	dfn[x]=++ti;id[ti]=x;
	top[x]=tp;
	if(son[x])dfs2(son[x],tp);
	for(int i=last[x];i;i=ne[i])if(E[i].y!=fa[x] && E[i].y!=son[x]){
		dfs2(E[i].y,E[i].y);
	}
}

void build(node *&p,int l,int r){
	p=new node;
	if(l==r){
		p->lcol=p->rcol=a[id[l]];
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
    for(int i=1;i<=m;i++){
    	static int x,y;
    	scanf("%d %d",&x,&y);
    	add_edge(x,y),add_edge(y,x);
    }
    dfs1(1,1);
    dfs2(1,1);
    build(root,1,n);
    while(m--)solve();
    return 0;
}