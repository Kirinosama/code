#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define MAXN 10010
#define MAXM 2*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y,z;
}E[MAXM];

struct query{
	int x,ID;
}Q[110];

set <int> s;
int last[MAXN],ne[MAXM],edge_cnt,tot,root,ans[110];
int n,q,size[MAXN],vis[MAXN],f[MAXN],cnt,dis[MAXN];

void add(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void getroot(int x,int fa){
	size[x]=1;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(vis[y] || y==fa) continue;
		getroot(y,x);size[x]+=size[y];
		f[x]=max(f[x],size[y]);
	}
	f[x]=max(f[x],tot-size[x]);
	if(f[x]<f[root]) root=x;
}

void dfs(int x,int fa,int dep){
	dis[++cnt]=dep;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa || vis[y]) continue;
		dfs(y,x,dep+E[i].z);
	}
}

void solve(int x){
	vis[x]=1;
	s.clear();s.insert(0);
	for(int i=last[x];i;i=ne[i])if(!vis[E[i].y]){
		cnt=0;dfs(E[i].y,E[i].y,E[i].z);
		for(int j=1;j<=q;j++)if(!ans[Q[j].ID]){
			for(int k=1;k<=cnt;k++)if(s.find(Q[j].x-dis[k])!=s.end()){
				ans[Q[j].ID]=1;break;
			}
		}
		for(int j=1;j<=cnt;j++)s.insert(dis[j]);
	}
	for(int i=last[x];i;i=ne[i])if(!vis[E[i].y]){
		root=0;tot=size[E[i].y];getroot(E[i].y,E[i].y);
		solve(root);
	}
}

int main(){
    freopen("p3806.in","r",stdin);
    cin>>n>>q;
    for(int i=1;i<n;i++){
    	int x,y,z;
    	scanf("%d%d%d",&x,&y,&z);
    	add(x,y,z);add(y,x,z);
    }
    for(int i=1;i<=q;i++){
    	scanf("%d",&Q[i].x);
    	Q[i].ID=i;
    }
    f[root]=INF;root=0;tot=n;getroot(1,1);
    solve(root);
    for(int i=1;i<=q;i++) printf("%s\n",ans[i]?"AYE":"NAY");
    return 0;
}