#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10010
#define MOD 11161223
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int rt1,rt2,num,n,T,a[MAXN],b[MAXN];
int ls[MAXN*100],rs[MAXN*100];
ll Hash[MAXN*100],mul[MAXN];

void init(){
    cin>>n;rt1=rt2=0;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
}

void premake(){
    mul[0]=1;
    for(int i=1;i<=10001;i++)mul[i]=(mul[i-1]*157)%MOD;
}

void maintain(int x,int l,int r){
    int len=r-(l+r)/2;
    Hash[x]=(Hash[ls[x]]*mul[len])%MOD+Hash[rs[x]];
    Hash[x]%=MOD;
}

void insert(int &x,int l,int r,int pos){
    if(!x) x=++num;
    if(l==r) Hash[x]=1;
    else{
        int mid=(l+r)>>1;
        if(pos<=mid)insert(ls[x],l,mid,pos);
        else insert(rs[x],mid+1,r,pos);
        maintain(x,l,r);
    }
}

int query(int x,int l,int r,int L,int R){
    if(l>R || r<L) return 0;
    if(l>=L && r<=R){
        return (Hash[x]*mul[R-r])%MOD; 
    }else{
        int mid=(l+r)>>1;
        return (query(ls[x],l,mid,L,R)+query(rs[x],mid+1,r,L,R))%MOD;
    }
}


void solve(){
    for(int i=1;i<=n;i++){
        insert(rt1,1,n,a[i]);
        insert(rt2,1,n,n-a[i]+1);
        int l=min(n-a[i],a[i]-1);
        if(query(rt1,1,n,a[i]-l,a[i]+l)!=query(rt2,1,n,n-a[i]-l+1,n-a[i]+l+1)){
            cout<<"Y"<<endl;
            return;
        }
    }
    cout<<"N"<<endl;
}

int main(){
    freopen("bzoj2124.in","r",stdin);
    cin>>T;
    premake();
    while(T--){
        init();
        solve();
    }
    return 0;
}
