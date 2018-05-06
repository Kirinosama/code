#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,k,a[MAXN],f[MAXN],q[MAXN];

bool cmp(int x,int y){
    if(f[x]==f[y]) return a[x]>a[y];
    return f[x]<f[y];
}

void solve(){
    int head=1,tail=1;
    scanf("%d",&k);f[1]=0;q[1]=1;
    for(int i=2;i<=n;i++){
        while(q[head]<i-k) head++;
        int tp=q[head];f[i]=f[tp]+(a[i]>=a[tp]);
        while(head<=tail && cmp(i,q[tail])) tail--;
        q[++tail]=i;
    }
    printf("%d\n",f[n]);
}

int main(){
    freopen("bzoj3831.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    cin>>m;
    while(m--)
        solve();
    return 0;
}
