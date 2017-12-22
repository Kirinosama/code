#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 250010
#define MAXM 2*MAXN
#define LOG 20
#define ii pair<int,int>
typedef long long ll;
const ll INF=1ll<<60;

struct edge{
	int x,y,z;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt,n,m;
int a[MAXN],dep[MAXN],dfn[MAXN],ti;
int anc[MAXN][25],s[MAXM];
ll f[MAXN],val[MAXN];

inline int read(){
	int x=0,w=0;char ch;
	while(ch<'0' || ch>'9')
		w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

bool cmp(const int &a,const int &b){
	return dfn[a]<dfn[b];
}

void add(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,int fa){
	anc[x][0]=fa;dfn[x]=++ti;
	for(int i=1;i<=LOG;i++)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa) continue;
		dep[y]=dep[x]+1;val[y]=min((ll)E[i].z,val[x]);
		dfs(y,x);
	}
	last[x]=0;
}

void premake(){
	n=read();int x,y,z;
	for(int i=1;i<n;i++){
		x=read(),y=read(),z=read();
		add(x,y,z),add(y,x,z);
	}
	m=read();
	val[1]=INF;dep[1]=1;
	dfs(1,1);
}

int Lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=LOG;i>=0;i--)
		if(dep[x]-(1<<i)>=dep[y])
			x=anc[x][i];
	if(x==y) return y;
	for(int i=LOG;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

void dp(int x){
	ll sum=0;f[x]=val[x];
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		dp(y);
		sum+=f[y];
	}
	last[x]=0;
	if(sum) f[x]=min(f[x],sum);
}

void solve(){
	int k=read();
	for(int i=1;i<=k;i++)
		a[i]=read();
	sort(a+1,a+1+k,cmp);
	int tot=1;
	for(int i=2;i<=k;i++)
		if(Lca(a[tot],a[i])!=a[tot])
			a[++tot]=a[i];
	int top=0;edge_cnt=0;
	s[++top]=1;
	for(int i=1;i<=tot;i++){
		while(1){
			int lca=Lca(s[top],a[i]);
			if(lca==s[top]){
				s[++top]=a[i];
				break;
			}
			else if(dep[lca]<=dep[s[top-1]]){
				add(s[top-1],s[top],0);
				top--;
			}
			else{
				add(lca,s[top],0);
				s[top]=lca;
			}
		}
	}
	while(top>1)
		add(s[top-1],s[top],0),top--;
	dp(1);
	printf("%lld\n",f[1]);
}

int main(){
   // freopen("bzoj2286.in","r",stdin);
    premake();
    while(m--)
    	solve();
    return 0;
}