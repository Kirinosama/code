#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 20010
#define MAXM 40010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,q;
int last[MAXN],ne[MAXM],edge_cnt;
int anc[MAXN][21],dep[MAXN];
ll base[MAXN][21][61],mul[61],a[MAXN];

struct edge{
    int x,y;
}E[MAXM];

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}
    
void add(ll *A,ll x){
    for(int i=0;i<=60;i++)if(x&mul[i]){
        if(A[i]) x^=A[i];
        else{
            A[i]=x;
            for(int j=i+1;j<=60;j++)if(x&mul[j])
                A[i]^=A[j];
            for(int j=i-1;j>=0;j--)if(A[j]&mul[i])
                A[j]^=A[i];
            break;
        }
    }
}

void insert(ll *A,ll *B){
    for(int i=0;i<=60;i++)if(B[i])
        add(A,B[i]);
}

void make(int x){
    add(base[x][0],a[x]);
    for(int i=1;i<=20;i++){
        insert(base[x][i],base[x][i-1]);
        insert(base[x][i],base[anc[x][i-1]][i-1]);
    }
}

void dfs(int x,int f){
    dep[x]=dep[f]+1;anc[x][0]=f;
    for(int i=1;i<=20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
    make(x);
    for(int i=last[x];i;i=ne[i])if(E[i].y!=f)
        dfs(E[i].y,x);
}

void print(int x){
    for(int j=0;j<=20;j++){
        for(int i=0;i<=60;i++){
            printf("%lld %lld\n",mul[i],base[x][j][i]);
        }
        cout<<endl;
    }
}

ll cal(ll *A){
    ll res=0;
    for(int i=0;i<=60;i++)res^=A[i];
    return res;
}

ll solve(int x,int y){
    ll cur[61]={0};
    if(dep[x]<dep[y])swap(x,y);
    for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
        insert(cur,base[x][i]),x=anc[x][i];
    if(x==y){add(cur,a[x]);return cal(cur);}
    for(int i=20;i>=0;i--)if(anc[x][i]!=anc[y][i]){
        insert(cur,base[x][i]),insert(cur,base[y][i]);
        x=anc[x][i],y=anc[y][i];
    }
    add(cur,a[x]);add(cur,a[y]);
    add(cur,a[anc[x][0]]);
    return cal(cur);
}

int main(){
    freopen("bzoj4568.in","r",stdin);
    cin>>n>>q;
    mul[60]=1;
    for(int i=59;i>=0;i--)mul[i]=mul[i+1]*2;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add_edge(x,y);add_edge(y,x);
    }
    dfs(1,1);
    while(q--){
        int x,y;scanf("%d%d",&x,&y);
        printf("%lld\n",solve(x,y));
    }
    return 0;
}
