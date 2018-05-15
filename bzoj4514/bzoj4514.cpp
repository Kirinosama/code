#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

#define MAXN 210
#define MAXM 100010
#define ii pair<int,int>
#define INF 1000000000000000000LL
typedef long long ll;

int n,s,t;
int last[MAXN],ne[MAXM],edge_cnt;
int a[MAXN],pre[MAXN];
bool instack[MAXN];
ll b[MAXN],c[MAXN];
ll dis[MAXN],ans,tot;

struct edge{
    int x,y;
    ll z,w;
}E[MAXM];

void add_edge(int x,int y,ll z,ll w){
    E[++edge_cnt]=(edge){x,y,z,w};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
    E[++edge_cnt]=(edge){y,x,0,-w};
    ne[edge_cnt]=last[y];
    last[y]=edge_cnt;
}

bool judge(int x){
    int cnt=0;
    for(int i=2;i<=sqrt(x+1);i++){
        while(x%i==0) x/=i,cnt++;  
    }
    if(x!=1) cnt++;
    return cnt&1;
}

bool isprime(int x){
    for(int i=2;i<=sqrt(x);i++)
        if(x%i==0) return false;
    return true;
}

void make(int x,int y){
    if(judge(a[x])==judge(a[y])) return;
    if(a[x]<a[y]) swap(x,y);
    if(a[x]%a[y]==0){
        if(!isprime(a[x]/a[y])) return;
        if(judge(a[x])) add_edge(x,y,INF,c[x]*c[y]);
        else add_edge(y,x,INF,c[x]*c[y]);        
    }
}

void premake(){
    s=n+1,t=s+1;
    for(int i=1;i<=n;i++){
        if(judge(a[i]))add_edge(s,i,b[i],0);
        else add_edge(i,t,b[i],0);
    }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            make(i,j);
}

bool spfa(){
    queue<int>Q;Q.push(s);
    memset(instack,false,sizeof(instack));instack[s]=true;
    memset(dis,128,sizeof(dis));dis[s]=0;
    while(!Q.empty()){
        int tp=Q.front();Q.pop();instack[tp]=false;
        for(int i=last[tp];i;i=ne[i])if(E[i].z>0){
            if(dis[E[i].y]<dis[tp]+E[i].w){
                dis[E[i].y]=dis[tp]+E[i].w;pre[E[i].y]=i;
                if(!instack[E[i].y])instack[E[i].y]=true,Q.push(E[i].y);
            }
        }
    }
    if(dis[t]+tot<0) return false;
    ll Min=INF;
    for(int i=t;i!=s;i=E[pre[i]].x){
        Min=min(E[pre[i]].z,Min);
    }
    if(dis[t]<0) Min=min(Min,-tot/dis[t]);
    tot+=Min*dis[t];
    for(int i=t;i!=s;i=E[pre[i]].x){
        E[pre[i]].z-=Min;
        E[pre[i]^1].z+=Min;
    }
    return true;
}

int main(){
    freopen("bzoj4514.in","r",stdin);
    cin>>n;edge_cnt=1;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
    premake();
    while(spfa());
    for(int i=2;i<=edge_cnt;i++)if(E[i].y==s)
        ans+=E[i].z;
    cout<<ans;
    return 0;
}
