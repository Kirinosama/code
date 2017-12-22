#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#define maxn 200000
using namespace std;

const int inf = 0x7fffffff;

struct Edge{
	int to, next, w;
}edge[maxn];

int from[maxn], to[maxn];

int h[maxn], cnt = 1;

void add(int u, int v, int w){
	cnt ++;
	edge[cnt].to = v;
	edge[cnt].next = h[u];
	edge[cnt].w = w;
	h[u] = cnt;
	swap(u, v);w = 0;
	cnt ++;
	edge[cnt].to = v;
	edge[cnt].next = h[u];
	edge[cnt].w = w;
	h[u] = cnt;
}

int n, m, S, T;

queue<int>Q;

int d[4010];

bool BFS(){
	Q.push(S);
	memset(d, -1, sizeof d);
	d[S] = 0;
	while(!Q.empty()){
		int u = Q.front();Q.pop();
		for(int i = h[u]; i; i = edge[i].next){
			if(!edge[i].w)continue;
			int v = edge[i].to;
			if(d[v] == -1){
				d[v] = d[u] + 1;
				Q.push(v);
			}
		}
	}return d[T] != -1;
}

int DFS(int x, int a){
	if(a == 0 || x == T)return a;
	int used = 0, f;
	for(int i = h[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(d[v] == d[x] + 1){
			f = DFS(v, min(edge[i].w, a - used));
			edge[i].w -= f;
			edge[i ^ 1].w += f;
			used += f;
			if(used == a)return used;
		}
	}
	if(!used)d[x] = -1;
	return used;
}

void Dinic(){
	int ans = 0;
	while(BFS())
		ans += DFS(S, inf);
}

int low[maxn], pre[maxn], dfs_clock, sccno[maxn], scc_cnt;

stack<int>s;

void Tarjan(int u){
	low[u] = pre[u] = ++ dfs_clock;
	s.push(u);
	for(int i = h[u]; i; i = edge[i].next){
		if(!edge[i].w)continue;
		int v = edge[i].to;
		if(!pre[v])Tarjan(v), low[u] = min(low[u], low[v]);
		else if(!sccno[v])low[u] = min(low[u], pre[v]);
	}
	if(low[u] == pre[u]){
		++ scc_cnt;
		for(;;){
			int v = s.top();s.pop();
			sccno[v] = scc_cnt;
			if(v == u)break;
		}
	}
}

int main(){
 //   freopen("mincut.in" ,"r",stdin );
//	freopen("mincut.out","w",stdout);
	scanf("%d%d%d%d", &n, &m, &S, &T);
	int w;
	for(int i = 1; i <= m; i ++){
		scanf("%d%d%d", &from[i], &to[i], &w);
		add(from[i], to[i], w);
	}
	Dinic();
	for(int i = 1; i <= n; i ++)
	    if(!pre[i])Tarjan(i);
	for(int i = 1; i <= m; i ++){
		int u = from[i], v = to[i];
		if(edge[i << 1].w){
			printf("0 0\n");
			continue;
		}
		if(sccno[u] == sccno[v])
		    printf("0 0\n");
		else if(sccno[u] == sccno[S] && sccno[v] == sccno[T])
		    printf("1 1\n");
		else printf("1 0\n");
	}
	return 0;
}