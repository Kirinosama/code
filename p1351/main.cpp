#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 200010
#define MOD 10007

vector <int> to[MAXN];
int son[MAXN][2],fa[MAXN],sum[MAXN],a[MAXN],n;
int ans1,ans2;

void dfs(int x,int f){
	fa[x]=f;
	for(int i=0;i<to[x].size();i++){
		int y=to[x][i];
		if(y!=f){
			dfs(y,x);
			sum[x]=(sum[x]+a[y])%MOD;
			if(a[y]>son[x][1]) son[x][1]=a[y];
			if(son[x][1]>son[x][0]) swap(son[x][0],son[x][1]);
		}
	}
	//printf("%d %d %d %d\n",x,son[x][0],son[x][1],sum[x]);
}

void dfs1(int x){
	if(fa[x]!=0 && fa[fa[x]]!=0){
		ans1=max(a[x]*a[fa[fa[x]]],ans1);
		ans2=(ans2+2*a[x]*a[fa[fa[x]]])%MOD;
	}
	if(fa[x]!=0){
		ans2=(ans2+a[x]*(sum[fa[x]]-a[x]))%MOD;
		if(a[x]==son[fa[x]][0] && son[fa[x]][1]!=-1e9) ans1=max(ans1,a[x]*son[fa[x]][1]);
		if(a[x]!=son[fa[x]][0] && son[fa[x]][0]!=-1e9) ans1=max(ans1,a[x]*son[fa[x]][0]);
	}
	for(int i=0;i<to[x].size();i++)
		if(to[x][i]!=fa[x])
			dfs1(to[x][i]);
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<n;i++){
		static int x,y;
		scanf("%d %d",&x,&y);
		to[x].push_back(y);
		to[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		son[i][0]=son[i][1]=-1e9;
	}
	dfs(1,0);
	dfs1(1);
	cout<<ans1<<' '<<ans2;
	return 0;
}