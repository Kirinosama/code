#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 989381
#define MAXN 500010
#define MAXM 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ii p[500010];

struct edge{
    int x,y;
}E[MAXM];

int n,m,edge_cnt,last[MAXN],ne[MAXM];
int du[MAXN],dfn[MAXN],fa[MAXN],size[MAXN];
ll jie[MAXN],mul[MAXN];

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

bool dfs(int x,int f){
    if(dfn[x]) return true;
    else dfn[x]=1;
    for(int i=last[x];i;i=ne[i])if(E[i].y!=f){
        if(dfs(E[i].y,x)) return true;
    }
    return false;
}

bool judge(){
    for(int i=1;i<=n;i++)if(du[i]>2)
        return true;
    for(int i=1;i<=n;i++)if(!dfn[i] && dfs(i,i))
        return true;
    return false;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx==fy) return;
    size[fx]+=size[fy];
    fa[fy]=fx;
}

void solve(){
    int dian=0,lian=0;
    jie[0]=1,mul[0]=1;
    for(int i=1;i<=n;i++){
        jie[i]=(jie[i-1]*i)%MOD;
        mul[i]=(mul[i-1]*2)%MOD;
    }
    for(int i=1;i<=n;i++)fa[i]=i,size[i]=1;
    for(int i=1;i<=edge_cnt;i+=2)
        merge(E[i].x,E[i].y);
    for(int i=1;i<=n;i++)if(fa[i]==i){
        if(size[i]==1) dian++;
        else lian++;
    }
    printf("%lld",(jie[dian+lian]*mul[lian])%MOD);
}

int main(){
    freopen("bzoj3444.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&p[i].first,&p[i].second);
        if(p[i].first>p[i].second)swap(p[i].first,p[i].second);
    }
    sort(p+1,p+m+1);
    for(int i=1;i<=m;i++){
        if(p[i]==p[i-1]) continue;
        du[p[i].first]++,du[p[i].second]++;
        add_edge(p[i].first,p[i].second);
        add_edge(p[i].second,p[i].first);
    }
    if(judge()){
        cout<<0;
    }else solve();
    return 0;
}
