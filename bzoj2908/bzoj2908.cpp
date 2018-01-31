#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll a[MAXN];
int n,m,k,son[MAXN],size[MAXN];
int dep[MAXN],dfn[MAXN],ti,father[MAXN],top[MAXN],id[MAXN];
vector <int> to[MAXN];

struct node{
	node *ch[2];
	int lval[32][2],rval[32][2];
	void maintain(){
		for(int i=0;i<k;i++){
			lval[i][0]=ch[1]->lval[i][ch[0]->lval[i][0]];
			lval[i][1]=ch[1]->lval[i][ch[0]->lval[i][1]];
			rval[i][0]=ch[0]->rval[i][ch[1]->rval[i][0]];
			rval[i][1]=ch[0]->rval[i][ch[1]->rval[i][1]];
		}
	}
}*root;

struct iii{
	int fst,sec,thd;
	iii() {}
	iii(int x,int y,int z) {fst=x,sec=y,thd=z;}
};

int nand(int x,int y){
	return !(x&y);
}

void dfs1(int x,int f){
	dep[x]=dep[f]+1;size[x]=1;son[x]=0;father[x]=f;
	for(int i=0;i<to[x].size();i++)if(to[x][i]!=f){
		dfs1(to[x][i],x);size[x]+=size[to[x][i]];
		if(size[to[x][i]]>size[son[x]])son[x]=to[x][i];
	}	
}

void dfs2(int x,int tp){
	dfn[x]=++ti;id[ti]=x;top[x]=tp;
	if(son[x])dfs2(son[x],tp);
	for(int i=0;i<to[x].size();i++)if(to[x][i]!=father[x] && to[x][i]!=son[x]){
		dfs2(to[x][i],to[x][i]);
	}
}

void build(node *&p,int l,int r){
	p=new node;ls=rs=NULL;
	if(l==r){
		for(int i=0;i<k;i++){
			p->lval[i][0]=p->rval[i][0]=nand((a[id[l]]>>i)&1,0);
			p->lval[i][1]=p->rval[i][1]=nand((a[id[l]]>>i)&1,1);
		}
	}else{
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		p->maintain();
	}
}

void Transform(node *p,int *A,int l,int r,int L,int R,int c){
	if(l>R || r<L) return;
	if(l>=L && r<=R){
		for(int i=0;i<k;i++){
			if(c==1)A[i]=p->lval[i][A[i]];
			else A[i]=p->rval[i][A[i]];
		}
	}else if(l!=r){
		int mid=(l+r)>>1;
		if(c==1) Transform(ls,A,l,mid,L,R,c),Transform(rs,A,mid+1,r,L,R,c);
		else Transform(rs,A,mid+1,r,L,R,c),Transform(ls,A,l,mid,L,R,c);
	}
}

void Query(int x,int y){
	queue <iii> s1;stack <iii> s2;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			s1.push(iii(dfn[top[x]],dfn[x],-1));
			x=father[top[x]];
		}else{
			s2.push(iii(dfn[top[y]],dfn[y],1));
			y=father[top[y]];
		}
	}
	if(dep[x]>dep[y]){
		s1.push(iii(dfn[y],dfn[x],-1));
	}else{
		s1.push(iii(dfn[x],dfn[y],1));
	}
	int A[32]={0};
	while(!s1.empty()){
		iii cur=s1.front();
		Transform(root,A,1,n,cur.fst,cur.sec,cur.thd),s1.pop();
	}
	while(!s2.empty()){
		iii cur=s2.top();
		Transform(root,A,1,n,cur.fst,cur.sec,cur.thd),s2.pop();
	}
	ll res=0;
	for(int i=0;i<k;i++)
		res+=(ll)A[i]*(1LL<<i);
	printf("%lld\n",res);
}

void Replace(node *&p,int l,int r,int L,int R){
	if(l>R || r<L) return;
	if(l>=L && r<=R){
		for(int i=0;i<k;i++){
			p->lval[i][0]=p->rval[i][0]=nand((a[id[l]]>>i)&1,0);
			p->lval[i][1]=p->rval[i][1]=nand((a[id[l]]>>i)&1,1);
		}
	}else if(l!=r){
		int mid=(l+r)>>1;
		Replace(ls,l,mid,L,R);
		Replace(rs,mid+1,r,L,R);
		p->maintain();
	}
}

void solve(){
	char str[10];int x;ll y;
	scanf("%s %d %lld",str,&x,&y);
	switch(str[0]){
		case 'Q':
			Query(x,y);break;
		case 'R':
			a[x]=y;Replace(root,1,n,dfn[x],dfn[x]);
	}
}

int main(){
    freopen("bzoj2908.in","r",stdin);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
   	for(int i=1;i<n;i++){
   		static int x,y;
   		scanf("%d %d",&x,&y);
   		to[x].push_back(y);
   		to[y].push_back(x);
   	}
   	dfs1(1,1);dfs2(1,1);
   	build(root,1,n);
   	while(m--)
   		solve();
    return 0;
}