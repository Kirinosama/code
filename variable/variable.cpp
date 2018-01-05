#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXM 200010
#define MAXN 1010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,W,p,q,T,edge_cnt,last[MAXN],ne[MAXM];
int book[MAXN],ans,add[MAXN],s,t,dis[MAXN],cur[MAXN];

struct aaa{
	int x,y,z,a,b,c,d,e,f;
	void in(){
		scanf("%d%d%d%d%d%d%d%d%d",&x,&y,&z,&a,&b,&c,&d,&e,&f);
	}
}task[MAXN];

struct edge{
	int x,y,z;
}E[MAXM];

void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x,0};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

bool bfs(){
	queue <int> Q;
	memset(dis,0,sizeof(dis));
	Q.push(s),dis[s]=1;
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		if(tp==t) return true;
		for(int i=last[tp];i;i=ne[i]){
			int y=E[i].y;
			if(E[i].z && !dis[y]){
				dis[y]=dis[tp]+1;
				Q.push(y);
			}
		}
	}
	return false;
}

int dinic(int x,int sum){
	int tot=0,k;
	if(x==t) return sum;
	for(int &i=cur[x];i;i=ne[i]){
		int y=E[i].y;
		if(dis[y]==dis[x]+1 && E[i].z && (k=dinic(y,min(E[i].z,sum-tot)))){
			E[i].z-=k,E[i^1].z+=k,tot+=k;
			if(tot==sum) return tot;
		}
	}
	if(!tot) dis[x]=0;
	return tot;
}

void solve(){
	int ans=0,x,y,r;
	cin>>n>>W>>p>>q;
	s=n+1,t=n+2;
	edge_cnt=1;
	memset(book,0,sizeof(book));
	memset(last,0,sizeof(last));
	for(int i=1;i<=p;i++){
		task[i].in();
		add[task[i].x]+=(task[i].d-task[i].f)*(-W);
		add[task[i].y]+=(task[i].e-task[i].d)*(-W);
		add[task[i].z]+=(task[i].f-task[i].e)*(-W);
	}
	for(int i=1;i<=q;i++){
		scanf("%d %d %d",&x,&y,&r);
		if(r==0) add_edge(x,y,INF);
		else if(r==1) add_edge(x,y,INF),add_edge(y,x,INF);
		else{
			add_edge(s,x,-W+add[x]),add_edge(x,t,INF),add_edge(s,y,INF),add_edge(y,t,W-add[y]);
			book[x]=book[y]=1;
		}
	}
	for(int i=1;i<=n;i++)
		if(!book[i])
			add_edge(s,i,-W+add[i]),add_edge(i,t,W-add[i]);
	for(int i=1;i<=p;i++){
		add_edge(task[i].x,task[i].y,2*task[i].a);
		add_edge(task[i].y,task[i].x,2*task[i].a);
		add_edge(task[i].y,task[i].z,2*task[i].b);
		add_edge(task[i].z,task[i].y,2*task[i].b);
		add_edge(task[i].z,task[i].x,2*task[i].c);
		add_edge(task[i].x,task[i].z,2*task[i].c);
	}
	while(bfs()){
		for(int i=1;i<=t;i++) cur[i]=last[i];
		ans+=dinic(s,INF);
	}
	cout<<ans<<endl;
}

int main(){
    freopen("variable.in","r",stdin);
    cin>>T;
    while(T--)
    	solve();
    return 0;
}