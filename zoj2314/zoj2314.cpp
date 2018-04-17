#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 210
#define MAXM 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,T,ans[MAXN],ru[MAXN],chu[MAXN];
int last[MAXN],ne[MAXM],edge_cnt;
int dis[MAXN],s,t,cur[MAXN];

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
    memset(dis,-1,sizeof(dis));dis[s]=0;
    queue<int>Q;Q.push(s);
    while(!Q.empty()){
        int tp=Q.front();Q.pop();
        for(int i=last[tp];i;i=ne[i])if(E[i].z && dis[E[i].y]==-1){
            dis[E[i].y]=dis[tp]+1;Q.push(E[i].y);
        }
    }
    return dis[t]!=-1;
}

int dinic(int x,int sum){
    int tot=0,k;
    if(x==t) return sum;
    for(int &i=cur[x];i;i=ne[i]){
        if(E[i].z && dis[E[i].y]==dis[x]+1 && (k=dinic(E[i].y,min(sum-tot,E[i].z))))
            E[i].z-=k,E[i^1].z+=k,tot+=k;
        if(tot==sum) return tot;
    }
    if(!tot) dis[x]=-1;
    return tot;
}

void maxflow(){
    while(bfs()){
        for(int i=1;i<=t;i++)cur[i]=last[i];
        dinic(s,INF);
    }
}

void solve(){
    cin>>n>>m;edge_cnt=1;
    memset(last,0,sizeof(last));
    s=n+1,t=s+1;
    for(int i=1;i<=m;i++){
        int x,y,p,q;
        scanf("%d%d%d%d",&x,&y,&p,&q);ans[i]=p;
        add_edge(x,y,q-p);add_edge(s,y,p);add_edge(x,t,p);
    }
    maxflow();
    for(int i=last[s];i;i=ne[i])if(E[i].z){
        cout<<"NO"<<endl;return;
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=m;i++)printf("%d\n",ans[i]+E[i*6-3].z);
}

int main(){
    freopen("zoj2314.in","r",stdin);
    cin>>T;
    while(T--)
        solve();
    return 0;
}
