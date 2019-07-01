#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 500010

int f[MAXN][21],deep[MAXN],p,q;
int n,m,root,edge_cnt,last[MAXN],ne[MAXN*2];

struct edge{
	int x,y;
}E[MAXN*2];

inline int read(){
    int X=0,w=1; char ch=0;
    while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}

inline void dfs(int x,int fa,int d){
	f[x][0]=fa;deep[x]=d;
	for(register int i=0;i<=19;i++)
		f[x][i+1]=f[f[x][i]][i];
	for(register int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa) continue;
		dfs(y,x,d+1);
	}
}

inline int lca(int x,int y){
	if(deep[x]>deep[y]) swap(x,y);
	for(register int i=20;i>=0;i--)
		if(deep[f[y][i]]>=deep[x])
			y=f[y][i];
	if(x==y) return x;
	for(register int i=20;i>=0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}

inline void add(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}


int main(){
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&m,&root);
	for(register int i=1;i<n;i++){
		p=read(),q=read();
		add(p,q),add(q,p);
	}
	dfs(root,root,1);
	for(register int i=1;i<=m;i++){
		p=read(),q=read();
		cout<<lca(p,q)<<endl;
	}
	return 0;
}