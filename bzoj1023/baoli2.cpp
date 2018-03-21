#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

#define MAXN 50010
#define MAXM 20010000
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,ne[MAXM],last[MAXN],edge_cnt,cnt,a[MAXN];
int dfn[MAXN],low[MAXN],ti,fst,sec,ans;
int bcc_cnt,bccno[MAXN],val[MAXN],dp[MAXN];
bool book[MAXN];
vector <int> to[MAXN];
stack <ii> S;

struct edge{
	int x,y;
}E[MAXM];

void link(int x,int y){
	to[x].push_back(y);
	to[y].push_back(x);
}

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

void init(){
	int k,x,y;bcc_cnt=n;edge_cnt=ti=ans=0;
	memset(dp,0,sizeof(dp));
	memset(bccno,0,sizeof(bccno));
	memset(last,0,sizeof(last));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	for(int i=1;i<=n;i++)to[i].clear();
	while(!S.empty())S.pop();
	for(int i=1;i<=m;i++){
		scanf("%d",&k);y=0;
		for(int j=1;j<=k;j++,y=x){
			scanf("%d",&x);
			if(y)link(x,y);
		}
	}
}

void tarjan(int x,int f){
	dfn[x]=low[x]=++ti;
	for(int i=0;i<to[x].size();i++){
		int y=to[x][i];
		if(y==f) continue;
		if(!dfn[y]){
			S.push(ii(x,y));
			tarjan(y,x);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				bcc_cnt++;
				while(!S.empty()){
					ii cur=S.top();S.pop();
					if(bccno[cur.first]!=bcc_cnt) bccno[cur.first]=bcc_cnt,add_edge(cur.first,bcc_cnt);
					if(bccno[cur.second]!=bcc_cnt) bccno[cur.second]=bcc_cnt,add_edge(cur.second,bcc_cnt);
					if(cur.first==x && cur.second==y) break;
				}
			}
		}
		else if(dfn[x]>=dfn[y]){
			S.push(ii(x,y));
			low[x]=min(low[x],dfn[y]);
		}
	}
}

void dfs(int x,int f){
	for(int i=0;i<to[x].size();i++)
		if(to[x][i]!=f && book[to[x][i]]){
			a[++cnt]=to[x][i];
			dfs(to[x][i],x);
			break;
		}
}

void update(int x){
	sec=max(sec,x);
	if(sec>fst) swap(sec,fst);
}

void solve1(int x,int f){//x为圆点
	sec=fst=0;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==f) continue;
		if(y<=n) dp[x]=max(dp[x],dp[y]+1),update(dp[y]+1);
		else{
			int MAX=0;cnt=0;
			for(int j=last[y];j;j=ne[j])if(E[j].y!=x){
				val[E[j].y]=INF;
				book[E[j].y]=true;
			}dfs(x,x);
			for(int i=1;i<=cnt;i++){
				MAX=max(MAX,dp[a[i]]+min(i,cnt+1-i));
				dp[x]=max(dp[x],dp[a[i]]+min(i,cnt+1-i));
				book[a[i]]=false;
			}
			update(MAX);
		}
	}
	ans=max(ans,dp[x]);
	ans=max(ans,fst+sec);
}

void solve2(int x,int f){
	for(int i=last[x];i;i=ne[i])
		if(E[i].y!=f) book[E[i].y]=true;
	cnt=0;dfs(f,f);
	if(cnt>1){
		for(int i=1;i<=cnt;i++)
			for(int j=i+1;j<=cnt;j++)
				ans=max(ans,dp[a[i]]+dp[a[j]]+min(j-i,cnt+1-(j-i)));
	}
	for(int i=last[x];i;i=ne[i])
		if(E[i].y!=f) book[E[i].y]=false;
}

void DP(int x,int f){
	for(int i=last[x];i;i=ne[i])
		if(E[i].y!=f) DP(E[i].y,x);
	if(x<=n) solve1(x,f);
	else solve2(x,f);
}

int main(){
    freopen("bzoj1023.in","r",stdin);
    freopen("out2","w",stdout);
   	while(scanf("%d %d",&n,&m)!=EOF){
   		init();
   		tarjan(1,1);
   		DP(1,1);
   		cout<<ans<<endl;
   	}
    return 0;
}