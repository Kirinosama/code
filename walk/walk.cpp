#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,ne[MAXN],round[MAXN],ti,dfn[MAXN],to[MAXN];
int go[MAXN][25];

void dfs(int x){
	if(!dfn[x]){
		dfn[x]=++ti;
		dfs(to[x]);
		ne[x]=ti-dfn[x];
	}else{
		ti++;
		ne[x]=0;round[x]=ti-dfn[x];
		return;
	}
}

void premake(){
	for(int i=1;i<=n;i++) go[i][0]=to[i];
	for(int i=1;i<=20;i++)
		for(int j=1;j<=n;j++)go[j][i]=go[go[j][i-1]][i-1];
}

int wh(int x,int k){
	int pos=x;
	for(int i=0;i<=20;i++,k>>=1)if(k&1){
		pos=go[pos][i];
	}
	return pos;
}

int main(){
    freopen("walk.in","r",stdin);
    freopen("walk.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%d",&to[i]);
    premake();
    for(int i=1;i<=n;i++)if(!dfn[i])
    	dfs(i);
   	//for(int i=1;i<=n;i++)printf("%d %d\n",ne[i],round[i]);
	for(int i=1;i<=m;i++){
		int s;ll k;
		scanf("%d%lld",&s,&k);
		if(k<=ne[s]) printf("%d\n",wh(s,k));
		else{
			int p=wh(s,ne[s]);
			printf("%d\n",wh(p,(k-ne[s])%round[p]));
		}
	}
    return 0;
}