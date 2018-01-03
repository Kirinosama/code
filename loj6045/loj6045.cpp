#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 610
#define MAXM MAXN*MAXN*4
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int s,t,sum,dis[MAXN],cur[MAXN],w[MAXN],maxflow;
int n,num[MAXN],a[MAXN][MAXN],vis[MAXN*2];
int pre[MAXN],edge_cnt,last[MAXN],ne[MAXM];
vector <int> v[MAXN];

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

bool find(int x){
    for(int i=0;i<v[x].size();i++){
        int y=v[x][i];
        if(!vis[y]){
            vis[y]=1;
            if(!pre[y] || find(pre[y])){
                pre[y]=x;
                return true;
            }
        }
    }
    return false;
}

bool bfs(){
    queue <int> Q;
    memset(dis,0,sizeof(dis));
    Q.push(s);dis[s]=1;
    while(!Q.empty()){
        int tp=Q.front();Q.pop();
        if(tp==t) return true;
        for(int i=last[tp];i;i=ne[i]){
            if(E[i].z && !dis[E[i].y])
                dis[E[i].y]=dis[tp]+1,Q.push(E[i].y);
        }
    }
    return false;
}

int dinic(int x,int rem){
    int tot=0,k;
    if(x==t) return rem;
    for(int &i=cur[x];i;i=ne[i]){
        if(E[i].z && dis[E[i].y]==dis[x]+1 && (k=dinic(E[i].y,min(E[i].z,rem-tot)))){
            E[i].z-=k,E[i^1].z+=k,tot+=k;
            if(tot==rem) return rem;
        }
    }
    if(!tot) dis[x]=0;
    return tot;
}

int main(){
    freopen("loj6045.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++){
            scanf("%d",&a[i][j]);
            v[i].push_back(a[i][j]+n);
        }
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
        w[i]=-w[i];
    }
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        find(i);
    }
    edge_cnt=1;s=n+1,t=s+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=num[i];j++)
            if(pre[a[i][j]+n]!=i)
                add_edge(i,pre[a[i][j]+n],INF);
    }
    for(int i=1;i<=n;i++){
        if(w[i]>=0) add_edge(s,i,w[i]),sum+=w[i];
        else add_edge(i,t,-w[i]);
    }
    while(bfs()){
        for(int i=1;i<=t;i++) cur[i]=last[i];
        maxflow+=dinic(s,INF);
    }
    printf("%d",maxflow-sum);
    return 0;
}