#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 110
#define MAXM 10010
#define ii pair<int,int>
#define INF 0x7f7f7f7f7f7f7f7f
typedef long long ll;

struct edge{
    int x,y;ll z;
}E[MAXM];

vector <int> to[MAXN];
int T,n,m;
int last[MAXN],ne[MAXM],edge_cnt;
ll dis[MAXN],ans;
int vis[MAXN],can[MAXN];
bool instack[MAXN];

void add_edge(int x,int y,ll z){
    E[++edge_cnt]=(edge){x,y,z};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void dfs(int x){
    can[x]=1;
    for(int i=0;i<to[x].size();i++)if(!can[to[x][i]])
        dfs(to[x][i]);
}

ll spfa(ll add){
    queue<int>Q;Q.push(1);
    memset(instack,false,sizeof(instack));
    memset(dis,0x7f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    instack[1]=true;dis[1]=0;vis[1]=1;
    while(!Q.empty()){
        int tp=Q.front();Q.pop();instack[tp]=false;
        for(int i=last[tp];i;i=ne[i])if(can[E[i].y]){
            int y=E[i].y;
            if(dis[tp]+E[i].z+add<dis[y]){
                dis[y]=dis[tp]+E[i].z+add;
                if(!instack[y]){
                    instack[y]=true,vis[y]++,Q.push(y);
                    if(vis[y]>n+5) return -1;
                }
            }
        }
    }
    return dis[n];
}

int main(){
    freopen("tstrip.in","r",stdin);
    freopen("tstrip.out","w",stdout);
    cin>>T;
    while(T--){
        cin>>n>>m;edge_cnt=0;
        memset(last,0,sizeof(last));
        memset(can,0,sizeof(can));
        for(int i=1;i<=n;i++)to[i].clear();
        for(int i=1;i<=m;i++){
            int x,y;ll z;
            scanf("%d%d%lld",&x,&y,&z);
            add_edge(x,y,z);
            to[y].push_back(x);
        }
        dfs(n);
        if(!can[1]) cout<<-1<<endl;
        else{
            int l=-100000,r=100000;
            while(l<=r){
                int mid=(l+r)>>1;
                ll dist=spfa(mid);
                if(dist>=0) ans=dist,r=mid-1;
                else l=mid+1;
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}
