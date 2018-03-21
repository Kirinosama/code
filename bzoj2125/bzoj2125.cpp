#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

#define MAXN 200010
#define MAXM 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,q,edge_cnt,last[MAXN],ne[MAXM],ans;
int dfn[MAXN],low[MAXN],ti,bcc_cnt,bccno[MAXN];
int ne1[MAXM],last1[MAXN],edge_cnt1,flag,val[MAXN];
int anc[MAXN][25],dep[MAXN],deep[MAXN];
bool book[MAXN];

struct edge{
	int x,y,z;
}E[MAXM],E1[MAXM];

stack <edge> Q;

void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void link(int x,int y){
	E1[++edge_cnt1]=(edge){x,y,0};
	ne1[edge_cnt1]=last1[x];
	last1[x]=edge_cnt1;
	E1[++edge_cnt1]=(edge){y,x,0};
	ne1[edge_cnt1]=last1[y];
	last1[y]=edge_cnt1;
}

void tarjan(int x,int f){
	//printf("%d->%d\n",f,x);
	dfn[x]=low[x]=++ti;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(!dfn[y]){
			Q.push(E[i]);
			tarjan(y,x);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				bcc_cnt++;
				while(!Q.empty()){
					edge cur=Q.top();Q.pop();
					if(bccno[cur.x]!=bcc_cnt){
						link(cur.x,bcc_cnt),bccno[cur.x]=bcc_cnt;
					}
					if(bccno[cur.y]!=bcc_cnt){
						link(cur.y,bcc_cnt),bccno[cur.y]=bcc_cnt;
					}
					if(cur.x==x && cur.y==y) break;
				}
			}
		}
		else if(y!=f && dfn[x]>dfn[y]){
			low[x]=min(low[x],dfn[y]);
			Q.push(E[i]);
		}
	}
}

void dfs1(int x,int f,int dis){
	val[x]=min(val[x],dis);
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y!=flag && y!=f && book[y]) dfs1(y,x,dis+E[i].z);
	}
}

void dfs(int x,int f){
	anc[x][0]=f;deep[x]=deep[f]+1;
	for(int i=1;i<=20;i++)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	if(x>n){
		for(int i=last1[x];i;i=ne1[i])
			book[E1[i].y]=true,val[E1[i].y]=INF;
		flag=f,dfs1(f,f,0);
		for(int i=last1[x];i;i=ne1[i]){
			if(E1[i].y!=f) E1[i].z=val[E1[i].y];
			else E1[i^1].z=val[E1[i].y];
			book[E1[i].y]=false;
		}
	}
	for(int i=last1[x];i;i=ne1[i]){
		int y=E1[i].y;
		if(y!=f) dfs(y,x);
	}
}

void init(int x,int f){
	for(int i=last1[x];i;i=ne1[i]){
		if(E1[i].y==f) continue;
		dep[E1[i].y]=dep[x]+E1[i].z;
		init(E1[i].y,x);
	}
}

int lca(int x,int y){
	if(deep[x]<deep[y]) swap(x,y);
	for(int i=20;i>=0;i--)
		if(deep[x]-(1<<i)>=deep[y])
			x=anc[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

void dfs2(int x,int f,int ed,int dis){
	if(x==ed){
		ans=min(ans,dis);return;
	}
	for(int i=last[x];i;i=ne[i])
		if(E[i].y!=f && book[E[i].y])
			dfs2(E[i].y,x,ed,dis+E[i].z);
}

int find(int x,int f,int ed){
	int res=INF;
	if(x==ed) return 0;
	//printf("%d->%d\n",f,x);
	for(int i=last[x];i;i=ne[i])
		if(E[i].y!=f && book[E[i].y])
			res=min(res,find(E[i].y,x,ed)+E[i].z);
	return res;
}

int cal(int x,int y,int id){
	for(int i=last1[id];i;i=ne1[i])
		book[E1[i].y]=true;
	int sum=find(x,x,y);
	for(int i=last1[id];i;i=ne1[i])
		book[E1[i].y]=false;
	return sum;
}

void solve1(int x,int y,int id){
	int p1=x,p2=y;
	for(int i=20;i>=0;i--)
		if(deep[p1]-(1<<i)>deep[id])
			p1=anc[p1][i];
	for(int i=20;i>=0;i--)
		if(deep[p2]-(1<<i)>deep[id])
			p2=anc[p2][i];
	int res=cal(p1,p2,id);
	res+=dep[x]+dep[y]-dep[p1]-dep[p2];
	printf("%d\n",res);
}

void solve(){
	static int x,y;
	scanf("%d %d",&x,&y);
	if(lca(x,y)>n) solve1(x,y,lca(x,y));
	else printf("%d\n",dep[x]+dep[y]-2*dep[lca(x,y)]);
}

int main(){
    freopen("bzoj2125.in","r",stdin);
    freopen("bzoj2125.out","w",stdout);
   	cin>>n>>m>>q;edge_cnt1=1;
   	for(int i=1;i<=m;i++){
   		static int u,v,w;
   		scanf("%d %d %d",&u,&v,&w);
   		add_edge(u,v,w),add_edge(v,u,w);
   	}bcc_cnt=n;
   	tarjan(1,1);
   	dfs(1,1);
   	init(1,1);
   	while(q--)
   		solve();
    return 0;
}