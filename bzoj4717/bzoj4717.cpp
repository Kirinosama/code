#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
 
#define MAXN 260
#define MAXM 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;
 
int opt,type,pos,val,l,r,L,R,ans,cnt[2010];
int n,m,q,a[MAXN],b[MAXM];
 
void change(){
    if(!type) a[pos]=val;
    else b[pos]=val;
}
 
int cal(int power){
    int sum=0;
    for(int i=L;i<=R;i++){
        int p=(power+b[i]-1)/b[i];
        if(p<=0) sum+=cnt[2000];
        else if(p>2000) continue;
        else sum+=cnt[2000]-cnt[p-1];
    }
    return sum;
}
 
void query(){
    memset(cnt,0,sizeof(cnt));
    for(int i=l;i<=r;i++)
        cnt[a[i]]++;
    for(int i=1;i<=2000;i++)
        cnt[i]+=cnt[i-1];
    int left=1,right=2000000000;
    while(left<=right){
        int mid=(ll)(left+right)>>1;
        if(cal(mid)>=val) ans=mid,left=mid+1;
        else right=mid-1;
    }
    cout<<ans<<endl;
}
 
void solve(){
    scanf("%d",&opt);
    switch(opt){
        case 0:
            scanf("%d %d %d",&type,&pos,&val);
            change();
            break;
        case 1:
            scanf("%d %d %d %d %d",&l,&r,&L,&R,&val);
            query();
    }
}
 
int main(){
    freopen("bzoj4717.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    cin>>q;
    while(q--)
        solve();
    return 0;
}