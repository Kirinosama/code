#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 160010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
    int x,y;
}E[MAXN];

int n,ans,book[210][210],cnt1,cnt2;
char a[210][210];
int last[MAXN],ne[MAXN],edge_cnt;
int pre[MAXN],vis[MAXN],now;
int go[8][2]={{1,-2},{1,2},{-1,2},{-1,-2},{2,1},{2,-1},{-2,1},{-2,-1}};

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

int find(int x){
    for(int i=last[x];i;i=ne[i])if(vis[E[i].y]!=now){
        vis[E[i].y]=now;
        if(!pre[E[i].y] || find(pre[E[i].y])){
            pre[E[i].y]=x;
            return 1;
        }
    }
    return 0;
}

void premake(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)if(a[i][j]=='0'){
            if((i+j)&1) book[i][j]=++cnt1;
            else book[i][j]=n*n+(++cnt2);
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)if((i+j)&1){
            for(int k=0;k<8;k++){
                int tx=i+go[k][0];
                int ty=j+go[k][1];
                if(tx<1 || tx>n || ty<1 || ty>n || a[tx][ty]=='1') continue;
                add_edge(book[i][j],book[tx][ty]);
            }
        }
    for(int i=1;i<=cnt1;i++){
        now++;
        if(find(i)) ans++;
    }
    printf("%d",cnt1+cnt2-ans);
}

int main(){
    freopen("bzoj3175.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            char ch=getchar();
            while(ch!='1' && ch!='0')ch=getchar();
            a[i][j]=ch;
        }
    premake();
    return 0;
}
