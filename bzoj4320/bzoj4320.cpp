#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 300010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,sqr,l[MAXN],r[MAXN],pos[MAXN];
int mn[MAXN],f[MAXN],mod[MAXN];

void premake(){
    sqr=(int)sqrt(300000);
    for(int i=1;i<=300000;i++)pos[i]=i/sqr+1;
    for(int i=1;i<=300000;i++){
        r[pos[i]]=i;
        if(pos[i]!=pos[i-1]) l[pos[i]]=i;
    }
    pos[0]=1;l[1]=0;
    memset(mn,0x3f,sizeof(mn));
    memset(f,0x3f,sizeof(f));
    memset(mod,0x3f,sizeof(mod));
}

void solve(){
    char opt[5];int x;
    scanf("%s %d\n",opt,&x);
    if(opt[0]=='A'){
        for(int i=1;i<=sqr;i++)mod[i]=min(mod[i],x%i);
        for(int i=x;i>=l[pos[x]];i--)mn[i]=min(mn[i],x);
        for(int i=pos[x]-1;i>=1;i--)f[i]=min(f[i],x);
    }else{
        if(x<=sqr) cout<<mod[x]<<endl;
        else{
            int ans=INF;
            for(int i=0;i<=300000;i+=x)
                ans=min(ans,min(mn[i],f[pos[i]])-i);
            printf("%d\n",ans);
        }
    }
}

int main(){
    freopen("bzoj4320.in","r",stdin);
    cin>>n;
    premake();
    for(int i=1;i<=n;i++)
        solve();
    return 0;
}
