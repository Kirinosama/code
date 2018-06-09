#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
#define MAXM 400010

struct edge{
	int x,y;
}E[MAXM];

int T,n,m,k;
int last[MAXN],ne[MAXM],edge_cnt;
int ans,col[MAXN],f[MAXN];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

bool judge(){
	for(int i=1;i<=n;i++){
		for(int j=last[i];j;j=ne[j]){
			if(col[i]==col[E[j].y]) return false;
		}
	}
	return true;
}

void dfs(int x){
	if(x==n+1){
		if(judge())ans++;
		return;
	}else{
		for(int i=1;i<=k;i++){
			col[x]=i;
			dfs(x+1);
		}
	}
}

void solve1(){
	ans=0;dfs(1);
	cout<<ans%6<<endl;
}

void dp(int x,int fa){
	f[x]=1;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa) continue;
		dp(y,x);
		f[x]=(f[x]*(k-1))%6;
		f[x]=(f[x]*f[y])%6;
	}
}

void solve2(){
	dp(1,1);
	cout<<(f[1]*k)%6<<endl;
}

int main(){
	freopen("input","r",stdin);
	cin>>T;
	while(T--){
		cin>>n>>m>>k;edge_cnt=0;
		memset(last,0,sizeof(last));
		for(int i=1;i<=m;i++){
			int x,y;scanf("%d%d",&x,&y);
			add_edge(x,y);add_edge(y,x);
		}
		if(k==1 && m) cout<<0<<endl;
		else if(k==1) cout<<1<<endl;
		else if(k<=10) solve1();
		else solve2();
	}
	return 0;
}
