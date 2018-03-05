#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int main(){	
    int i,x,y;  
    ll dist;  
    cin>>n>>t;  
    for(i=2;i<=n;i++)  
    {  
        scanf("%d%lld%lld%lld%lld",&fa[i],&dist,&p[i],&q[i],&l[i]);  
        add(fa[i],i,dist);  
    }  
    queue[++r]=1;  
    while(r^h)  
    {  
        x=queue[++h];  
        for(i=head[x];i;i=table[i].next)  
            dis[table[i].to]=dis[x]+table[i].f,queue[++r]=table[i].to;  
    }  
    memset(f,0x3f,sizeof(f));f[1]=0;  
    CDQ_Tree(1,n,++cnt);  
    for(i=2;i<=n;i++)  
        printf("%lld\n",f[i]==4557430888798830399ll?0:f[i]);  
}  