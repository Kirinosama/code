#include<stdio.h>  
#include<iostream>  
#include<string.h>  
#define ll long long  
#define maxn 1000010  
#define INF 0x3f3f3f3f  
#define mem(a,b) memset(a,b,sizeof(a))  
using namespace std;  
  
int n;  
ll w[maxn];  
struct Edge{  
    int to,next;  
}edge[maxn*2];  
int head[maxn],tot;  
int vis[maxn],root,_root,cut;//在找环时使用，判断是否遍历过  
ll maxc[maxn][3],ans;  
  
void add(int u,int v){  
    edge[tot].to=v,edge[tot].next=head[u],head[u]=tot++;  
}  
  
void find_onecircle(int u,int fa){//找环并顺便将所有的点标记  
    vis[u]=1;  
    for(int i=head[u];i!=-1;i=edge[i].next){  
        int v=edge[i].to;  
        if(v==fa) continue;  
        if(!vis[v]) find_onecircle(v,u);  
        else{ root=v,_root=u,cut=i; }  
    }  
}  
  
void tree_maxind(int u,int fa){  
    maxc[u][1]=w[u],maxc[u][0]=0;  
    for(int i=head[u];i!=-1;i=edge[i].next){  
        int v=edge[i].to;  
        if(i==cut||i==(cut^1)||v==fa) continue;  
        tree_maxind(v,u);  
        maxc[u][1]+=maxc[v][0];  
        maxc[u][0]+=max(maxc[v][0],maxc[v][1]);  
    }  
}  
  
ll onecircle_tree_maxind(int u){//在u所在基环树中求最大独立点集  
    ll tmp=0;  
    find_onecircle(u,-1);//在树中找到一个环,并切掉一条边  
    tree_maxind(root,-1);  
    tmp=maxc[root][0];  
    tree_maxind(_root,-1);  
    tmp=max(tmp,maxc[_root][0]);  
    return tmp;  
}  
  
int main(){  
    scanf("%d",&n);  
    mem(head,-1),ans=0,tot=0;  
    mem(vis,0),mem(maxc,0);  
    for(int i=1;i<=n;i++){  
        int a,b;  
        scanf("%lld%d",&a,&b);  
        w[i]=a;  
        add(i,b),add(b,i);  
    }  
    for(int i=1;i<=n;i++){  
        if(vis[i]) continue;  
        ans+=onecircle_tree_maxind(i);  
    }  
    printf("%lld\n",ans);  
    return 0;  
}  