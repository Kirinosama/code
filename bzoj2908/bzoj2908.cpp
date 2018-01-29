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

int n,m,k,a[MAXN],son[MAXN],size[MAXN];
int dep[MAXN],dfn[MAXN],ti,father[MAXN],top[MAXN],id[MAXN];
vector <int> to[MAXN];

struct node{
	node *ch[2];
	int lval,rval
	void maintain(){
		for(int i=0;i<k;i++){
			lval[i][0]=ch[1]->lval[i][ch[0]->lval[i][0]];
			lval[i][1]=ch[1]->lval[i][ch[0]->lval[i][1]];
			rval[i][0]=ch[0]->rval[i][ch[1]->rval[i][0]];
			rval[i][1]=ch[0]->rval[i][ch[1]->rval[i][1]];
		}
	}
}*root;

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
	dfn[x]=++ti;id[ti]=dfn[x];top[x]=tp;
	if(son[x])dfs2(son[x],tp);
	for(int i=0;i<to[x].size();i++)if(to[x][i]!=father[x]){
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

int Transform(node *p,int res,int l,int r,int L,int R,int c){
	if(l>=L && r<=R){
		int k=
		for(int i=0;i<k;i++){
			if(res==-1) 
		}
	}else if(l!=r){
		int mid=(l+r)>>1;
	}
}

void Query(int x,int y){
	queue <int> s1;
	stack <int> s2;
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			s1.push(Transform(root,-1,1,n,dfn[top[x]],dfn[x],-1));
			x=father[top[x]];
		}else{
			s2.push(Transform(root,-1,1,n,dfn[top[y]],dfn[y],1));
			y=father[top[y]];
		}
	}
	if(dep[x]>dep[y]){
		for(int i=dfn[x];i>=dfn[y];i--) s1.push(a[id[i]]);
	}else{
		for(int i=dfn[x];i<=dfn[y];i++) s1.push(a[id[i]]);
	}
	while(!s1.empty()){
		res=nand(res,s1.front());s1.pop();
	}
	while(!s2.empty()){
		res=nand(res,s2.top());s2.pop();
	}
	printf("%d\n",res);
}

void solve(){
	char str[10];int x,y;
	scanf("%s %d %d",str,&x,&y);
	switch(str[0]){
		case 'Q':
			Query(x,y);
			break;
		case 'R':
			Replace(x,y);
	}
}

int main(){
    freopen("bzoj2908.in","r",stdin);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
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