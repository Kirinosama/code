#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define LOG 20
int n,m,last[100010],ne[200010],edge_cnt,anc[100010][25];
int dep[100010],cnt,light[100010];

struct edge{
	int x,y;
}E[200010];

void add(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

inline int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=LOG;i>=0;i--)
		if(dep[anc[x][i]]>=dep[y])
			x=anc[x][i];
	if(x==y) return y;
	for(int i=LOG;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

void make_dep(int x,int fa){
	anc[x][0]=fa;
	for(int i=1;i<=LOG;i++)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa) continue;
		dep[y]=dep[x]+1;
		make_dep(y,x);
	}
}

int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}

void solve(){
	char type[5];
	int x;
	scanf("%s",type);
	if(type[0]=='G'){
		if(cnt<=1) cout<<cnt-1<<endl;
		else{
			int res=0;
			for(int i=1;i<=n;i++)
				for(int j=i+1;j<=n;j++)
					if(light[i]==0 && light[j]==0)
						res=max(res,dis(i,j));
			cout<<res<<endl;
		}
	}
	else{
		scanf("%d",&x);
		if(!light[x]) cnt--;
		else cnt++;
		light[x]^=1;
	}
}

int main(){
	freopen("bzoj1095.in","r",stdin);
	freopen("out3.out","w",stdout);
	scanf("%d",&n);cnt=n;
    for(int i=1;i<n;i++){
    	int x,y;
    	scanf("%d %d",&x,&y);
    	add(x,y),add(y,x);
    }
    scanf("%d",&m);
   	make_dep(1,1);
    while(m--)
    	solve();
}