#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 201314
#define SIZE(x) (x?(x->r-x->l+1):0)
#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 50010
#define MAXM 2*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

struct task{
	int type,ID,pos1,pos2;
	bool operator < (const task &a)const{
		return pos1<a.pos1;
	}
}Q[MAXN];

struct node{
	node *ch[2];
	int add_tag,sum;
	int l,r;
	void pushdown(){
		if(add_tag){
			if(ch[0]){
				ch[0]->sum+=SIZE(ch[0])*add_tag;ch[0]->sum%=MOD;
				ch[0]->add_tag+=add_tag;ch[0]->add_tag%=MOD;
			}
			if(ch[1]){
				ch[1]->sum+=SIZE(ch[1])*add_tag;ch[1]->sum%=MOD;
				ch[1]->add_tag+=add_tag;ch[1]->add_tag%=MOD;
			}
			add_tag=0;
		}
	}
	void maintain(){
		sum=(ch[0]->sum+ch[1]->sum)%MOD;
	}
}*root;

int n,q,ti;
int last[MAXN],ne[MAXM],id[MAXN],fa[MAXN],edge_cnt,ans[MAXN];
int dep[MAXN],dfn[MAXN],size[MAXN],son[MAXN],top[MAXN];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs1(int x){
	son[x]=0;size[x]=1;dep[x]=dep[fa[x]]+1;
	for(int i=last[x];i;i=ne[i])if(E[i].y!=fa[x]){
		dfs1(E[i].y);
		size[x]+=size[E[i].y];
		if(size[E[i].y]>size[son[x]]) son[x]=E[i].y;
	}
}

void dfs2(int x,int tp){
	dfn[x]=++ti;id[ti]=x;top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=last[x];i;i=ne[i])if(E[i].y!=fa[x] && E[i].y!=son[x]){
		dfs2(E[i].y,E[i].y);
	}
}

void build(node *&p,int l,int r){
	p=new node;ls=rs=NULL;
	p->sum=0;p->add_tag=0;
	p->l=l,p->r=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
}

void make(node *p,int l,int r,int L,int R,int k){
	if(l>R || r<L) return;
	if(l>=L && r<=R){
		p->sum+=SIZE(p)*k;p->sum%=MOD;
		p->add_tag+=k;p->add_tag%=MOD;
	}else{
		int mid=(l+r)>>1;
		p->pushdown();
		make(ls,l,mid,L,R,k);
		make(rs,mid+1,r,L,R,k);
		p->maintain();
	}
}

void add(int x){
	while(1){
		make(root,1,n,dfn[top[x]],dfn[x],1);
		if(top[x]==0) break;
		x=fa[top[x]];
	}
}

int getsum(node *p,int l,int r,int L,int R){
	if(l>R || r<L) return 0;
	if(l>=L && r<=R) return p->sum;
	else{
		int mid=(l+r)>>1;
		p->pushdown();
		int cur=(getsum(ls,l,mid,L,R)+getsum(rs,mid+1,r,L,R))%MOD;
		p->maintain();
		return cur;
	}
}

int query(int x){
	int res=0;
	while(1){
		res=(res+getsum(root,1,n,dfn[top[x]],dfn[x]))%MOD;
		if(top[x]==0) break;
		x=fa[top[x]];
	}
	return res;
}

int main(){
    freopen("bzoj3626.in","r",stdin);
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){
    	scanf("%d",&fa[i]);
    	add_edge(fa[i],i);
    	add_edge(i,fa[i]);
    }
    dfs1(0);dfs2(0,0);
    for(int i=1;i<=q;i++){
    	int l,r,z;
    	scanf("%d%d%d",&l,&r,&z);
    	Q[i*2-1].type=1;Q[i*2-1].ID=i;Q[i*2-1].pos1=r;Q[i*2-1].pos2=z;
    	Q[i*2].type=0;Q[i*2].ID=i;Q[i*2].pos1=l-1;Q[i*2].pos2=z;
    }
    build(root,1,n);
    sort(Q+1,Q+2*q+1);int cur=-1;
    for(int i=1;i<=2*q;i++){
    	for(int &j=cur;j<Q[i].pos1;j++) add(j+1);
    	ans[Q[i].ID]+=Q[i].type?query(Q[i].pos2):-query(Q[i].pos2);
    	ans[Q[i].ID]%=MOD;
    }
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    return 0;
}