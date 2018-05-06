#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

#define MAXN 10010
#define MAXM 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
    int x,y;
}E[MAXM],E1[MAXM];

int n,m,s,t;
int last[MAXN],ne[MAXM],edge_cnt;
int last1[MAXN],ne1[MAXM],edge_cnt1;
int flag1[MAXN],flag2[MAXN];
int dfn[MAXN],low[MAXN],fam[MAXN],ti,bcc_cnt;
int que[MAXN],ru[MAXN],chu[MAXN],book[MAXN];
double A[110][110],f[MAXN];
stack <int> S;
vector <int> bcc[MAXN],to[MAXN];

void add_edge(int x,int y){
   E[++edge_cnt]=(edge){x,y};
   ne[edge_cnt]=last[x];
   last[x]=edge_cnt;
}

void add_edge1(int x,int y){
    E1[++edge_cnt1]=(edge){x,y};
    ne1[edge_cnt1]=last1[x];
    last1[x]=edge_cnt1;
}

void tarjan(int x){
    dfn[x]=low[x]=++ti;S.push(x);
    for(int i=last[x];i;i=ne[i]){
        int y=E[i].y;
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }else if(!fam[y]){
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(dfn[x]==low[x]){
        bcc_cnt++;
        while(S.top()!=x)bcc[bcc_cnt].push_back(S.top()),fam[S.top()]=bcc_cnt,S.pop();
        bcc[bcc_cnt].push_back(S.top()),fam[S.top()]=bcc_cnt,S.pop();
    }
}

void torpu(){
    queue <int> Q;
    int cnt=0;
    for(int i=1;i<=bcc_cnt;i++)if(!ru[i])
        Q.push(i);
    while(!Q.empty()){
        int tp=Q.front();Q.pop();que[++cnt]=tp;
        for(int i=0;i<to[tp].size();i++){
            ru[to[tp][i]]--;
            if(!ru[to[tp][i]])Q.push(to[tp][i]);
        }
    }
}

void solve(int now){
    int cnt=bcc[now].size();
    for(int i=0;i<cnt;i++){
        int cur=bcc[now][i];book[cur]=i;
        for(int j=0;j<=cnt;j++)A[i][j]=0.0;
    }
    for(int i=0;i<cnt;i++){
        int cur=bcc[now][i];A[i][i]=A[i][cnt]=chu[cur];
        for(int j=last[cur];j;j=ne[j]){
            int y=E[j].y;
            if(fam[y]!=now || y==t)A[i][cnt]+=f[y];
            else A[i][book[y]]=-1;
        }
    }
    for(int i=0;i<cnt;i++){
        for(int j=i+1;j<cnt;j++){
            double mul=A[j][i]/A[i][i];
            for(int k=i;k<=cnt;k++)A[j][k]-=A[i][k]*mul;
        }
    }
    for(int i=cnt-1;i>=0;i--){
        if(bcc[now][i]==t) f[t]=0.0;
        else f[bcc[now][i]]=A[i][i]?A[i][cnt]/A[i][i]:0.0;
        for(int j=i-1;j>=0;j--)A[j][cnt]-=A[j][i]*f[bcc[now][i]];
    }
}

void dfs1(int x){
    flag1[x]=1;
    for(int i=last1[x];i;i=ne1[i])if(!flag1[E1[i].y])
        dfs1(E1[i].y);
}

void dfs2(int x){
    flag2[x]=1;if(x==t) return;
    for(int i=last[x];i;i=ne[i])if(!flag2[E[i].y])
        dfs2(E[i].y);
}

bool judge(){
    for(int i=1;i<=edge_cnt;i++)
        add_edge1(E[i].y,E[i].x);
    dfs1(t);dfs2(s);
    for(int i=1;i<=n;i++)if(flag2[i] && !flag1[i])
        return true;
    return false;
}

int main(){
    freopen("bzoj2707.in","r",stdin);
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        add_edge(x,y);chu[x]++;
    }
    if(judge()){
        cout<<"INF";return 0;
    }
    for(int i=1;i<=n;i++)if(!dfn[i])
        tarjan(i);
    for(int i=1;i<=edge_cnt;i++)if(fam[E[i].x]!=fam[E[i].y]){
        to[fam[E[i].x]].push_back(fam[E[i].y]);
        ru[fam[E[i].y]]++;
    }
    torpu();
    for(int i=bcc_cnt;i>=1;i--)
        solve(que[i]);
    printf("%.3lf",f[s]);
    return 0;
}
