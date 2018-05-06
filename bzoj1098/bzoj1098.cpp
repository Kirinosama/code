#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 100010
#define MAXM 4000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
    int x,y;
}E[MAXM];

int book[MAXN],flag[MAXN],cnt[MAXN];
int last[MAXN],ne[MAXM],edge_cnt;
int n,m,ans,ed,pre[MAXN],suc[MAXN];

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void del(int x){
    book[x]=ans;cnt[ans]++;
    suc[pre[x]]=suc[x];
    pre[suc[x]]=pre[x];
    if(ed==x)ed=pre[x];
}

void bfs(int x){
    ans++;
    queue<int>Q;Q.push(x);del(x);
    while(!Q.empty()){
        int tp=Q.front();Q.pop();
        for(int i=ed;i;i=pre[i])flag[i]=false;
        for(int i=last[tp];i;i=ne[i])
            flag[E[i].y]=true;
        for(int i=ed;i;i=pre[i])if(!flag[i]){
            Q.push(i);del(i);
        }
    }
}

int main(){
    freopen("bzoj1098.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        add_edge(x,y);add_edge(y,x);
    }
    for(int i=1;i<=n;i++){
        pre[i]=i-1;suc[i]=i+1;
        ed=i;
    }
    for(int i=1;i<=n;i++)if(!book[i])
        bfs(i);
    cout<<ans<<endl;
    sort(cnt+1,cnt+ans+1);
    for(int i=1;i<=ans;i++)printf("%d ",cnt[i]);
    return 0;
}
