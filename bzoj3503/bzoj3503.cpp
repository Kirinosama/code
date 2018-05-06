#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,a[1610][1610];
int go[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
int ans[1610];

int num(int x,int y){
    return (x-1)*m+y;
}

void swap_line(int x,int y){
    for(int i=1;i<=n*m+1;i++)
        swap(a[x][i],a[y][i]);
}

void solve(){
    int tot=n*m;
    for(int i=1;i<=tot;i++){
        for(int j=i+1;j<=tot;j++)if(a[j][i])
            swap_line(i,j);
        for(int j=i+1;j<=tot;j++)if(a[j][i])
            for(int k=i;k<=tot;k++)a[j][k]^=a[i][k];
    }
    for(int i=tot;i>=1;i--){
        if(!a[i][i]) ans[i]=1;
        else ans[i]=a[i][tot+1];
        for(int j=i-1;j>=1;j--)if(a[j][i])
            a[j][tot+1]^=ans[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)printf("%d ",ans[num(i,j)]);
        cout<<endl;
    }
}

int main(){
    freopen("bzoj3503.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            a[num(i,j)][num(i,j)]=1;
            for(int k=0;k<4;k++){
                int tx=i+go[k][0],ty=j+go[k][1];
                if(tx<1 || tx>n || ty<1 || ty>m)continue;
                a[num(i,j)][num(tx,ty)]=1;
            }
        }
    solve();
    return 0;
}
