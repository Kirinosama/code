#include <bits/stdc++.h>
using namespace std;

#define MAXN 300010
#define MAXM 600010
typedef long long ll;

int n,q,rt,nodecnt,Rt,ls[MAXN*4],rs[MAXN*4];
int last[MAXN],ne[MAXM],edge_cnt;
int dfn[MAXN],tail[MAXN],ti,val[MAXN];
int a[MAXN],anc[MAXN][25],dep[MAXN];
ll tot[MAXN*4],tag[MAXN*4];

struct edge{
	int x,y;
}E[MAXM];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,int f){
	dfn[x]=++ti;val[ti]=a[x];
	dep[x]=dep[f]+1;anc[x][0]=f;
	for(int i=1;i<=20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f)
		dfs(E[i].y,x);
	tail[x]=ti;
}

int getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
		x=anc[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)if(anc[x][i]!=anc[y][i])
		x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

int getsec(int x,int y){
	for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>dep[y])
		x=anc[x][i];
	return x;
}

void pushdown(int x,int l,int r){
	if(!tag[x]) return;
	int mid=(l+r)>>1;
	tag[ls[x]]+=tag[x];
	tag[rs[x]]+=tag[x];
	tot[ls[x]]+=tag[x]*(ll)(mid-l+1);
	tot[rs[x]]+=tag[x]*(ll)(r-mid);
	tag[x]=0;
}

void maintain(int x){
	tot[x]=tot[ls[x]]+tot[rs[x]];
} 

void make(int x,int l,int r,int L,int R,ll z){
	if(L>R) return;
	if(l>R || r<L) return;
	if(l>=L && r<=R) tot[x]+=(r-l+1)*z,tag[x]+=z;
	else{
		int mid=(l+r)>>1;
		pushdown(x,l,r);
		make(ls[x],l,mid,L,R,z);
		make(rs[x],mid+1,r,L,R,z);
		maintain(x);
	}
}

ll query(int x,int l,int r,int L,int R){
	if(L>R) return 0;
	if(l>R || r<L) return 0;
	if(l>=L && r<=R) return tot[x];
	else{
		int mid=(l+r)>>1;
		pushdown(x,l,r);
		ll sum=query(ls[x],l,mid,L,R)+query(rs[x],mid+1,r,L,R);
		maintain(x);
		return sum;
	}
}

void solve(){
	int opt,x,y,z,now;
	scanf("%d",&opt);
	if(opt==1){
		scanf("%d",&rt);
	}else if(opt==2){
		scanf("%d%d%d",&x,&y,&z);
		int lca=getlca(x,y);
		if(dfn[rt]<dfn[lca] || dfn[rt]>tail[lca]) now=lca;
		else{
			int lca1=getlca(rt,x);
			int lca2=getlca(rt,y);
			now=dep[lca1]>dep[lca2]?lca1:lca2;
		}
		if(dfn[rt]<dfn[now] || dfn[rt]>tail[now]) make(Rt,1,n,dfn[now],tail[now],z);
		else if(now==rt) make(Rt,1,n,1,n,z);
		else{
			int k=getsec(rt,now);
			make(Rt,1,n,1,dfn[k]-1,z);
			make(Rt,1,n,tail[k]+1,n,z);
		}
	}else{
		scanf("%d",&x);
		if(dfn[rt]<dfn[x] || dfn[rt]>tail[x]) 
			cout<<query(Rt,1,n,dfn[x],tail[x])<<endl;
		else if(rt==x) cout<<query(Rt,1,n,1,n)<<endl;
		else{
			int k=getsec(rt,x);
			ll sum=query(Rt,1,n,1,dfn[k]-1)+query(Rt,1,n,tail[k]+1,n);
			cout<<sum<<endl;
		}
	}
}

void build(int &x,int l,int r){
	x=++nodecnt;
	if(l==r) tot[x]=val[l];
	else{
		int mid=(l+r)>>1;
		build(ls[x],l,mid);
		build(rs[x],mid+1,r);
		maintain(x);
	}
}

int main(){
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	cin>>n>>q;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		add_edge(x,y);add_edge(y,x);
	}
	rt=1;
	dfs(1,1);
	build(Rt,1,n);
	while(q--)
		solve();
	return 0;
}
