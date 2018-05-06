#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 310
#define MAXM 400010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
    int x,y,z;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int n,m,s,t,dis[MAXN],cur[MAXN];

void add_edge(int x,int y,int z){
    E[++edge_cnt]=(edge){x,y,z};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
    E[++edge_cnt]=(edge){y,x,0};
    ne[edge_cnt]=last[y];
    last[y]=edge_cnt;
}

bool bfs(){
    queue<int>Q;Q.push(s);
    memset(dis,-1,sizeof(dis));dis[s]=0;
    while(!Q.empty()){
        int tp=Q.front();Q.pop();
        for(int i=last[tp];i;i=ne[i])if(E[i].z && dis[E[i].y]==-1)
            dis[E[i].y]=dis[tp]+1,Q.push(E[i].y);
    }
    return dis[t]!=-1;
}

int dfs(int x,int tot){
    int sum=0,k;
    if(x==t) return tot;
    for(int &i=cur[x];i;i=ne[i]){
        int y=E[i].y;
        if(dis[y]==dis[x]+1 && E[i].z && (k=dfs(y,min(tot-sum,E[i].z))))
            E[i].z-=k,E[i^1].z+=k,sum+=k;
        if(sum==tot) return sum;
    }
    if(!sum) dis[x]=-1;
    return sum;
}

int main(){
    freopen("bzoj2768.in","r",stdin);
    cin>>n>>m;s=n+1,t=s+1;edge_cnt=1;
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        if(x)add_edge(s,i,1);
        else add_edge(i,t,1);
    }
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        add_edge(x,y,1);add_edge(y,x,1);
    }
    int res=0;
    while(bfs()){
        for(int i=1;i<=t;i++)cur[i]=last[i];
        res+=dfs(s,INF);
    }
    cout<<res;
    return 0;
}
