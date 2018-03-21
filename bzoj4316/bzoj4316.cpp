#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

#define MAXN 100010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int dfn[MAXN],low[MAXN],ti,n,m,edge_cnt,dp[MAXN][2],d[MAXN][2];
int bcc_cnt,bccno[MAXN],last[MAXN],ne[MAXM],a[MAXN],num;
bool book[MAXN];

vector <int> to[MAXN];
stack <ii> s;

struct edge{
	int x,y;
}E[MAXM];

void link(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

void tarjan(int x,int f){
	dfn[x]=low[x]=++ti;
	for(int i=0;i<to[x].size();i++){
		int y=to[x][i];
		if(y==f) continue;
		if(!dfn[y]){
			s.push(ii(x,y));
			tarjan(y,x);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				bcc_cnt++;
				while(!s.empty()){
					ii cur=s.top();s.pop();
					if(bccno[cur.first]!=bcc_cnt) link(cur.first,bcc_cnt),bccno[cur.first]=bcc_cnt;
					if(bccno[cur.second]!=bcc_cnt) link(cur.second,bcc_cnt),bccno[cur.second]=bcc_cnt;
					if(cur.first==x && cur.second==y) break;
				}
			}
		}
		else if(dfn[x]>dfn[y]){
			low[x]=min(low[x],dfn[y]);
			s.push(ii(x,y));
		}
	}
}

void find(int x,int f){
	for(int i=0;i<to[x].size();i++)
		if(to[x][i]!=f && book[to[x][i]]){
			a[++num]=to[x][i];
			find(to[x][i],x);break;
		}
}

void solve(int x){
	if(num==1){
		dp[x][1]=max(dp[a[1]][0],dp[a[1]][1]);
		dp[x][0]=dp[a[1]][0];
	}
	else if(num==2){
		dp[x][1]=max(dp[a[1]][0]+dp[a[2]][1],dp[a[1]][1]+dp[a[2]][0]);
		dp[x][0]=dp[a[1]][0]+dp[a[2]][0];
	}
	else{
		for(int i=1;i<=num;i++){
			d[i][0]=d[i][1]=0;
			d[i][0]=max(d[i][0],d[i-1][0]+dp[a[i]][0]);
			d[i][0]=max(d[i][0],d[i-1][1]+dp[a[i]][0]);
			d[i][1]=max(d[i][1],d[i-1][0]+dp[a[i]][1]);
		}
		dp[x][1]=max(d[num][0],d[num][1]);
		for(int i=1;i<=num;i++){
			d[i][0]=d[i][1]=0;
			d[i][0]=max(d[i][0],d[i-1][0]+dp[a[i]][0]);
			d[i][0]=max(d[i][0],d[i-1][1]+dp[a[i]][0]);
			if(i!=1 && i!=num) d[i][1]=max(d[i][1],d[i-1][0]+dp[a[i]][1]);
		}
		dp[x][0]=d[num][0];
	}
}

void dfs(int x,int f){
	if(x<=n){
		dp[x][1]=1;
		for(int i=last[x];i;i=ne[i]){
			if(E[i].y==f) continue;
			dfs(E[i].y,x);
			dp[x][1]+=dp[E[i].y][0];
			dp[x][0]+=max(dp[E[i].y][0],dp[E[i].y][1]);
		}
	}
	else{
		for(int i=last[x];i;i=ne[i])
			if(E[i].y!=f) dfs(E[i].y,x);
		for(int i=last[x];i;i=ne[i])	
			if(E[i].y!=f) book[E[i].y]=true;
		num=0;find(f,f);
		solve(x);
		for(int i=last[x];i;i=ne[i])
			if(E[i].y!=f) book[E[i].y]=false;	
	}
}

int main(){
    freopen("bzoj4316.in","r",stdin);
    freopen("output1","w",stdout);
    cin>>n>>m;bcc_cnt=n;
    for(int i=1;i<=m;i++){
    	static int x,y;
    	scanf("%d%d",&x,&y);
    	to[x].push_back(y);
    	to[y].push_back(x);
    }
    tarjan(1,1);
    dfs(1,1);
    printf("%d\n",max(dp[1][0],dp[1][1]));
    // for(int i=1;i<=bcc_cnt;i++){
    // 	printf("dp[%d][0]=%d\n",i,dp[i][0]);
    // 	printf("dp[%d][1]=%d\n",i,dp[i][1]);
    // }
    return 0;
}