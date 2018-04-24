#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 520
#define MAXM 250010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
    int x,y,z;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int n,m,k,a[260][260];
int dis[520],cur[MAXN],s,t;

void add_edge(int x,int y,int z){
    E[++edge_cnt]=(edge){x,y,z};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
    E[++edge_cnt]=(edge){y,x,0};
    ne[edge_cnt]=last[y];
    last[y]=edge_cnt;
}

void init(){
    memset(last,0,sizeof(last));
    edge_cnt=1;s=n+m+1,t=s+1;
    for(int i=1;i<=n;i++)add_edge(s,i,1);
    for(int i=n+1;i<=n+m;i++)add_edge(i,t,1);
}

bool bfs(){
    queue<int>Q;Q.push(s);
    memset(dis,-1,sizeof(dis));dis[s]=0;
    while(!Q.empty()){
        int tp=Q.front();Q.pop();
        if(tp==t) return true;
        for(int i=last[tp];i;i=ne[i])if(dis[E[i].y]==-1 && E[i].z){
            Q.push(E[i].y);dis[E[i].y]=dis[tp]+1;
        }
    }
    return false;
}

int dfs(int x,int tot){
    int sum=0,k;
    if(x==t) return tot;
    for(int &i=cur[x];i;i=ne[i])if(E[i].z && dis[E[i].y]==dis[x]+1 && (k=dfs(E[i].y,min(E[i].z,tot-sum)))){
        E[i].z-=k,E[i^1].z+=k,sum+=k;
        if(sum==tot) return sum;
    }
    if(!sum) dis[x]=-1;
    return sum;
}

int dinic(){
    int res=0;
    while(bfs()){
        for(int i=1;i<=t;i++)cur[i]=last[i];
        res+=dfs(s,INF);
    }
    return res;
}

bool judge(int x){
    init();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j]<=x)
                add_edge(i,j+n,1);
    return dinic()>=n-k+1;
}

int main(){
    freopen("bzoj4443.in","r",stdin);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    int l=1,r=1e9,ans;
    while(l<=r){
        int mid=(l+r)>>1;
        if(judge(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    cout<<ans;
    return 0;
}
