#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define LOG 20
#define MAXN 100010
#define MAXM 2*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

struct PQ{
	priority_queue <int> val,del;
	void pop(){
		while(del.size() && val.top()==del.top())
			val.pop(),del.pop();
		val.pop();
	}
	int top(){
		while(del.size() && val.top()==del.top())
			val.pop(),del.pop();
		return val.top();
	}
	void push(int x){
		val.push(x);
	}
	void erase(int x){
		del.push(x);
	}
	int sectop(){
		int tmp=top();pop();
		int sec=top();push(tmp);
		return sec;
	}
	int size(){
		return val.size()-del.size();
	}
}q1[MAXN],q2[MAXN],q3;

int last[MAXN],ne[MAXM],edge_cnt,son[MAXN],ROOT,minres,light[MAXN];
int n,m,dep[MAXN],anc[MAXN][25],vis[MAXN],rem,father[MAXN],gcnt;

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

void erase(PQ &s){
	if(s.size()>=2)
		q3.erase(s.top()+s.sectop());
}

void insert(PQ &s){
	if(s.size()>=2)
		q3.push(s.top()+s.sectop());
}

inline int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
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

void work(int x,int pre,int root){
	q1[root].push(dis(x,father[root]));
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==pre || vis[y]) continue;
		work(y,x,root);
	}
}

void dfs1(int x,int fa){
	int res=0;son[x]=0;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa || vis[y]) continue;
		dfs1(y,x);
		son[x]+=son[y]+1;
		res=max(res,son[y]+1);
	}
	res=max(res,rem-son[x]-1);
	if(res<minres){
		minres=res;
		ROOT=x;
	}
}

int find_root(int x){
	minres=INF,ROOT=0;
	dfs1(x,x);
	return ROOT;
}

void cnt(int x,int fa){
	rem++;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(vis[y] || y==fa) continue;
		cnt(y,x);
	}
}

int make(int x,int fa){
	int cur=find_root(x);
	father[cur]=fa;
	work(cur,0,cur);
	vis[cur]=1;	q2[cur].push(0);
	for(int i=last[cur];i;i=ne[i]){
		int y=E[i].y;
		if(vis[y]) continue;
		rem=0;cnt(y,y);
		int next_root=make(y,cur);
		q2[cur].push(q1[next_root].top());
	}
	insert(q2[cur]);
	return cur;
}

void premake(){
	make_dep(1,1);
	rem=n;
	make(1,0);
}

void solve(){
	char type[5];
	int x;
	scanf("%s",type);
	if(type[0]=='G'){
		if(n<=1) cout<<n-1<<endl;
		else cout<<q3.top()<<endl;
	}
	else{
		scanf("%d",&x);
		if(!light[x]){
			n--;
			erase(q2[x]);
			q2[x].erase(0);
			insert(q2[x]);
			for(int i=x;father[i];i=father[i]){
				erase(q2[father[i]]);
				if(q1[i].size()) q2[father[i]].erase(q1[i].top());
				q1[i].erase(dis(x,father[i]));
				if(q1[i].size()) q2[father[i]].push(q1[i].top());
				insert(q2[father[i]]);
			}
		}
		else{
			n++;
			erase(q2[x]);
			q2[x].push(0);
			insert(q2[x]);
			for(int i=x;father[i];i=father[i]){
				erase(q2[father[i]]);
				if(q1[i].size()) q2[father[i]].erase(q1[i].top());
				q1[i].push(dis(x,father[i]));
				if(q1[i].size()) q2[father[i]].push(q1[i].top());
				insert(q2[father[i]]);
			}
		}
		light[x]^=1;
	}
}

int main(){
    freopen("bzoj1095.in","r",stdin);
    freopen("out1.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<n;i++){
    	int x,y;
    	scanf("%d %d",&x,&y);
    	add(x,y),add(y,x);
    }
    scanf("%d",&m);
    premake();
    while(m--)
    	solve();
    return 0;
}