#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 100010
#define MAXM 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int T,n,m;
int edge_cnt,last[MAXN],ne[MAXM];
int ans[MAXN],ru[MAXN];

struct edge{
    int x,y;
}E[MAXM];

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void solve(){
    priority_queue<int>Q;
    int cnt=0;
    for(int i=1;i<=n;i++)if(!ru[i])Q.push(i);
    while(!Q.empty()){
        ans[++cnt]=Q.top();Q.pop();
        for(int i=last[ans[cnt]];i;i=ne[i]){
            ru[E[i].y]--;
            if(!ru[E[i].y]) Q.push(E[i].y);
        }
    }
    if(cnt==n){
        for(int i=n;i>=1;i--)printf("%d ",ans[i]);
        cout<<endl;
    }else cout<<"Impossible!"<<endl;
}

int main(){
    freopen("bzoj4010.in","r",stdin);
    cin>>T;
    while(T--){
        cin>>n>>m;edge_cnt=0;
        memset(last,0,sizeof(last));
        memset(ru,0,sizeof(ru));
        for(int i=1;i<=m;i++){
            int x,y;scanf("%d%d",&x,&y);
            ru[x]++;add_edge(y,x);
        }
        solve();
    }
    return 0;
}
