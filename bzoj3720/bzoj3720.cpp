#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

#define MAXN 60010
#define MAXM 2*MAXN

struct edge{
	int x,y;
}E[MAXM];

int n,m,a[MAXN],last[MAXN],ne[MAXM],edge_cnt,block_cnt,lastans;
int vis[MAXN],sqr,belong[MAXN],father[MAXN],size[MAXN];
vector <int> to[MAXN];
vector <int> v[MAXN];

inline int read(){
	int x=0,w=0;char ch;
	while(ch<'0' || ch>'9')
		w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

void add(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

int cal(int block,int val){
	return v[block].end()-upper_bound(v[block].begin(),v[block].end(),val);
}

int dfs2(int x,int val){
	int sum=cal(x,val);
	for(int i=0;i<to[x].size();i++)
		sum+=dfs2(to[x][i],val);
	return sum;
}

int dfs1(int x,int block,int val){
	if(belong[x]!=block)
		return dfs2(belong[x],val);
	else{
		int sum=a[x]>val;
		for(int i=last[x];i;i=ne[i]){
			int y=E[i].y;
			if(y==father[x]) continue;
			sum+=dfs1(y,block,val);
		}
		return sum;
	}
}

void solve(){
	int type=read(),u=read()^lastans,x=read()^lastans;
	if(type==0){
		lastans=dfs1(u,belong[u],x);
		printf("%d\n",lastans);
	}
	if(type==1){
		v[belong[u]].erase(lower_bound(v[belong[u]].begin(),v[belong[u]].end(),a[u]));
		v[belong[u]].insert((lower_bound(v[belong[u]].begin(),v[belong[u]].end(),x)),x);
		a[u]=x;
	}
	if(type==2){
		a[++n]=x;
		father[n]=u;
		add(u,n),add(n,u);
		if(size[belong[u]]<sqr){
			belong[n]=belong[u];
		}
		else{
			belong[n]=++block_cnt;
			to[belong[u]].push_back(block_cnt);
		}
		size[belong[n]]++;
		v[belong[n]].insert(lower_bound(v[belong[n]].begin(),v[belong[n]].end(),x),x);
	}
}

void dfs(int x,int fa){
	father[x]=fa;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa)continue;
		if(size[belong[x]]<sqr){
			belong[y]=belong[x];
			size[belong[x]]++;
		}
		else{
			belong[y]=++block_cnt;
			size[block_cnt]=1;
		}
		if(belong[x]!=belong[y]){
			to[belong[x]].push_back(belong[y]);
		}
		dfs(y,x);
	}
}

void premake(){
	n=read();sqr=sqrt(n);
    for(int i=1;i<n;i++){
    	int x=read(),y=read();
    	add(x,y),add(y,x);
    }
    for(int i=1;i<=n;i++)
    	a[i]=read();
    m=read();belong[1]=++block_cnt;size[1]=1;
    dfs(1,1);
    for(int i=1;i<=n;i++)
    	v[belong[i]].push_back(a[i]);
    for(int i=1;i<=block_cnt;i++)
    	sort(v[i].begin(),v[i].end());
}

int main(){
    freopen("bzoj3720.in","r",stdin);
    premake();
    while(m--)
    	solve();
    return 0;
}