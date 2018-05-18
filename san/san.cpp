#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 60
#define MAXM 2510
#define INF 0x3f3f3f3f
#define ii pair<int,int>
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

int ne[MAXM],last[MAXN],edge_cnt;
int ans,now,f[1200000],book[MAXN][MAXN];
int a[MAXN],n,m,s[MAXN],ru[MAXN];
vector <int> to[MAXN];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void topu(){
	queue<int>Q;int cnt=0;
	for(int i=1;i<=n;i++)if(!ru[i])
		Q.push(i);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		s[++cnt]=tp;
		for(int i=last[tp];i;i=ne[i]){
			ru[E[i].y]--;
			if(!ru[E[i].y])Q.push(E[i].y);
		}
	}
}

void dfs(int g,int x){
	book[g][x]=1;
	for(int i=0;i<to[x].size();i++)
		dfs(g,to[x][i]);
}

bool judge(int now,int x,bool p,int mask){
	if(p && ((mask>>(x-1))&1)) return false;
	if(!((mask>>(x-1))&1)) p=true;
	if(x==now) p=false;
	for(int i=0;i<to[x].size();i++)
		if(!judge(now,to[x][i],p,mask)) return false;
	return true;
}

int main(){
	freopen("san.in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);ru[y]++;
		add_edge(x,y);to[y].push_back(x);
	}
	topu();
	for(int i=1;i<=n;i++)dfs(i,i);
	memset(f,0xc0,sizeof(f));f[0]=0;
	for(int i=1;i<=n;i++){
		now=s[i];
		for(int j=0;j<(1<<n);j++)if(!((j>>(now-1))&1)){
			if(judge(now,now,false,j)){
				f[j|(1<<(now-1))]=max(f[j|(1<<(now-1))],f[j]+a[now]);
				ans=max(ans,f[j|(1<<(now-1))]);
			}
		}
	}
	cout<<ans;
	return 0;
}
