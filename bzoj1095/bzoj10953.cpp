#include<queue>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int logn=18;
const int maxn=100000+10;
const int maxm=200000+10;

int first[maxn],ne[maxm],ecnt;
struct Edge{int u,v;Edge(int u=0,int v=0):u(u),v(v){}}e[maxm];
inline void add_edge(int u,int v){
    ne[ecnt]=first[u];first[u]=ecnt;e[ecnt++]=Edge(u,v);
    ne[ecnt]=first[v];first[v]=ecnt;e[ecnt++]=Edge(v,u);
}

int anc[maxn][logn+2],dep[maxn];
inline void dfs_anc(int u,int pre)
{
    anc[u][0]=pre;dep[u]=dep[pre]+1;
    for(int i=1;(1<<i)+1<=dep[u];++i) anc[u][i]=anc[anc[u][i-1]][i-1];
    for(int i=first[u];i!=-1;i=ne[i])
        if(e[i].v!=pre) dfs_anc(e[i].v,u);
}

int n;

inline void init_data()
{
    cin>>n;memset(first,-1,sizeof first);
    for(int i=1,u,v;i<n;++i){
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
}

int top,path[maxn],sz[maxn],Msz[maxn],done[maxn];

void DP(int u,int pre)
{
    path[++top]=u;
    sz[u]=1;Msz[u]=0;
    for(int i=first[u];i!=-1;i=ne[i])
    {
        int v=e[i].v;   
        if(done[v]||v==pre) continue;
        DP(v,u);
        sz[u]+=sz[v];Msz[u]=max(Msz[u],sz[v]);
    }
}

inline int find_G(int u)
{
    top=0;
    DP(u,u);
    int m=Msz[u],pos=u;
    for(int i=2;i<=top;++i)
    {
        int t=max(Msz[path[i]],sz[u]-sz[path[i]]);
        if(t <= m) {m=t;pos=path[i];}   
    }
    return pos;
}

inline int dis(int a,int b)
{
    int x=a,y=b;
    if(dep[a] > dep[b]) swap(a,b);
    if(dep[a] < dep[b]){
        int t=dep[b]-dep[a];
        for(int i=logn;i>=0;--i)
            if(t-(1<<i) >= 0){
                t-=1<<i;b=anc[b][i];
            }
    }
    if(a!=b) 
    {
        for(int i=logn;i>=0;--i)
            if(anc[a][i]!=anc[b][i])
                a=anc[a][i],b=anc[b][i];
        a=anc[a][0];b=anc[b][0];
    }
    return dep[x]+dep[y]-2*dep[a];
}

struct PQ{
    priority_queue<int>q1,q2;
    inline void push(const int &x){q1.push(x);}
    inline void erase(const int &x){q2.push(x);}
    inline void pop(){
        while(q2.size() && q1.top()==q2.top()) q1.pop(),q2.pop();
        q1.pop();
    }
    inline int top(){
        while(q2.size()&&(q1.top()==q2.top())) q1.pop(),q2.pop();
        return q1.top();
    }
    inline int top2(){
        int t=top();pop();
        int ret=top();push(t);
        return ret;
    }
    inline int size(){return q1.size()-q2.size();}
}f[maxn],g[maxn],ans;//f[u]记到G的距离，g[u]记分治树上儿子的f[u]堆顶 

inline void work(int u,int pre,const int &G,const int &fa)
{
    f[G].push(dis(u,fa));
    for(int i=first[u];i!=-1;i=ne[i])
    {
        int v=e[i].v; 
        if(done[v]||v==pre) continue;   
        work(v,u,G,fa);
    }
}

inline void insert(PQ &q){
    if(q.size() >= 2)   ans.push(q.top()+q.top2());
}

inline void erase(PQ &q){
    if(q.size() >= 2)   ans.erase(q.top()+q.top2());
}

int p[maxn];//分治树上父亲 
inline int DivTree(int u,int fa)
{
    if(u==2){
        int stop=1; 
    }

    int G=find_G(u);
    g[G].push(0);//一切以G为中心！！ 
    work(G,G,G,fa);
    done[G]=1;
    for(int i=first[G];i!=-1;i=ne[i])
    {
        int v=e[i].v;
        if(done[v]) continue;
        int Gy=DivTree(v,G);
        p[Gy]=G;

//      cout<<f[v].size();

        g[G].push(f[Gy].top());//注意构建的时候要用Gy不能用v，因为我Gy才是分治树上G的儿子 
    }
    insert(g[G]);
    return G;
}

inline void del(int u)
{
    erase(g[u]);
    g[u].erase(0);
    insert(g[u]);

    for(int t=u;p[t];t=p[t])
    {
        erase(g[p[t]]);
//      cout<<"*"<<g[p[t]].size()<<endl;
        g[p[t]].erase(f[t].top());
        f[t].erase(dis(u,p[t]));
        if(f[t].size()) g[p[t]].push(f[t].top());
        insert(g[p[t]]);
    }
}
inline void add(int u)
{
    erase(g[u]);
    g[u].push(0);
    insert(g[u]);

    for(int t=u;p[t];t=p[t])
    {
        erase(g[p[t]]);
        if(f[t].size()) g[p[t]].erase(f[t].top());
        f[t].push(dis(u,p[t]));
        g[p[t]].push(f[t].top());
        insert(g[p[t]]);
    }
}

int col[maxn];
inline void solve()
{
    int m,cntw=n;cin>>m;
    char op[5];int a;

    while(m--)
    {
        scanf("%s",op);
        if(op[0]=='G') 
        {
            if(cntw<=1) printf("%d\n",cntw-1); 
            else printf("%d\n",ans.top());
        }
        else{
            //反色并update 
            scanf("%d",&a);
            if(!col[a]) {--cntw;del(a);}
            else{++cntw;add(a);}
            col[a]^=1;
        }
    }
}

int main()
{
    freopen("bzoj1095.in","r",stdin);
    freopen("out4.out","w",stdout);
    init_data();
    dfs_anc(1,1);
    DivTree(1,0);
    solve();

    return 0;
}