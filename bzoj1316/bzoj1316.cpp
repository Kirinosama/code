#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define MAXN 10010
#define MAXM 110
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

inline int read(){
	int x=0,w=0;char ch;
	while(ch<'0' || ch>'9') w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

int a[MAXM],n,m,root,tot,p[MAXN],cnt,rootans,size[MAXN];
int vis[MAXN],dis[MAXN],ans[MAXN];
int last[MAXN],ne[MAXN*2],edge_cnt;
set <int> s;

struct edge{
	int x,y,z;
}E[MAXN*2];

inline void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

inline void getroot(int x,int f){
	size[x]=1;int Max=0;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(vis[y] || y==f) continue;
		getroot(y,x);size[x]+=size[y];
		Max=max(Max,size[y]);
	}
	Max=max(Max,tot-size[x]);
	if(Max<rootans){
		rootans=Max,root=x;
	}
}

inline void dfs(int x,int f){
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f && !vis[E[i].y]){
		dis[E[i].y]=dis[x]+E[i].z;
		dfs(E[i].y,x);
	}p[++cnt]=dis[x];
}

inline void solve(int x){
	vis[x]=1;s.clear();s.insert(0);
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(vis[y]) continue;
		cnt=0;dis[y]=E[i].z,dfs(y,x);
		for(int j=1;j<=m;j++)if(!ans[j]){
			for(int k=1;k<=cnt;k++)if(s.find(a[j]-p[k])!=s.end()){
				ans[j]=1;break;
			}
		}
		for(int j=1;j<=cnt;j++)s.insert(p[j]);
	}
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(vis[y]) continue;
		rootans=INF,tot=size[y];
		getroot(y,y);solve(y);
	}
}

int main(){
    freopen("bzoj1316.in","r",stdin);
    n=read(),m=read();int x,y,z;
    for(int i=1;i<n;i++){
    	x=read(),y=read(),z=read();
    	add_edge(x,y,z);add_edge(y,x,z);
    }
    for(int i=1;i<=m;i++){
    	a[i]=read();
    	if(!a[i]) ans[i]=1;
    }
    tot=n;rootans=INF;
	getroot(1,1);
	solve(root);
	for(int i=1;i<=m;i++)if(ans[i]){
		printf("Yes\n");
	}else{
		printf("No\n");
	}
    return 0;
}