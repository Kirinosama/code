#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;

const int max_n=1e3+5;
const int max_m=1e4+5;
const int max_N=max_n+3;
const int max_M=max_N*2+max_m;
const int max_e=max_M*2;
const int INF=1e9;

int n,m,N,x,y,z,maxflow,mincost;
int need[max_n];
int point[max_N],next[max_e],v[max_e],remain[max_e],c[max_e],tot;
int dis[max_N],last[max_N];
bool vis[max_N];
queue <int> q;

inline void addedge(int x,int y,int cap,int z){
    ++tot; next[tot]=point[x]; point[x]=tot; v[tot]=y; remain[tot]=cap; c[tot]=z;
    ++tot; next[tot]=point[y]; point[y]=tot; v[tot]=x; remain[tot]=0; c[tot]=-z;
}

inline int addflow(int s,int t){
    int ans=INF,now=t;
    while (now!=s){
        ans=min(ans,remain[last[now]]);
        now=v[last[now]^1];
    }

    now=t;
    while (now!=s)
    {
        remain[last[now]]-=ans;;
        remain[last[now]^1]+=ans;
        now=v[last[now]^1];
    }
    return ans;
}

inline bool bfs(int s,int t){

    memset(dis,0x7f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s]=0;
    vis[s]=true;
    while (!q.empty()) q.pop();

    q.push(s);

    while (!q.empty()){
        int now=q.front(); q.pop();
        vis[now]=false;
        for (int i=point[now];i!=-1;i=next[i])
          if (dis[v[i]]>dis[now]+c[i]&&remain[i]){
            dis[v[i]]=dis[now]+c[i];
            last[v[i]]=i;
            if (!vis[v[i]]){
                vis[v[i]]=true;
                q.push(v[i]);
            }
          }
    }

    if (dis[t]>INF) return false;
    int flow=addflow(s,t);
    maxflow+=flow;
    mincost+=flow*dis[t];
    return true;
}

inline void major(int s,int t){
    maxflow=0; mincost=0;
    while (bfs(s,t));
}

int main(){
    tot=-1;
    memset(point,-1,sizeof(point));
    memset(next,-1,sizeof(next));

    scanf("%d%d",&n,&m);
    N=n+3;
    for (int i=1;i<=n;++i){
        scanf("%d",&need[i]);
        x=need[i]-need[i-1];
        if (x>=0) addedge(1,1+i,x,0);
        else addedge(1+i,N,-x,0);
    }
    x=-need[n];
    if (x>=0) addedge(1,n+2,x,0);
    else addedge(n+2,N,-x,0);
    for (int i=1;i<=m;++i){
        scanf("%d%d%d",&x,&y,&z);
        addedge(1+x,1+y+1,INF,z);
    }
    for (int i=1;i<=n;++i)
      addedge(1+i+1,1+i,INF,0);

    major(1,N);
    printf("%d\n",mincost);
}