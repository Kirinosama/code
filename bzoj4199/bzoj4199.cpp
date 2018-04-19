#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 300010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

vector <int> pos[MAXN];
int n,len;
int rk[MAXN],sa2[MAXN],cnt[MAXN],sa[MAXN],height[MAXN];
int father[MAXN];
ll tot[MAXN],size[MAXN],ans,Max[MAXN],Min[MAXN],mul[MAXN],a[MAXN],anss[MAXN];
ll Min1,Min2,Max1,Max2;
string s;

bool same(int *A,int x,int y,int z){
    return A[x]==A[y] && A[x+z]==A[y+z];
}

void get_sa(int m){
    for(int i=0;i<m;i++)cnt[i]=0;
    for(int i=0;i<len;i++)cnt[rk[i]=s[i]]++;
    for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
    for(int i=len-1;i>=0;i--)sa[--cnt[rk[i]]]=i;
    for(int gap=1;gap<len;gap<<=1){
        int p=0;
        for(int i=len-gap;i<len;i++)sa2[p++]=i;
        for(int i=0;i<len;i++)if(sa[i]>=gap)
            sa2[p++]=sa[i]-gap;
        for(int i=0;i<m;i++)cnt[i]=0;
        for(int i=0;i<len;i++)cnt[rk[i]]++;
        for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
        for(int i=len-1;i>=0;i--)sa[--cnt[rk[sa2[i]]]]=sa2[i];
        swap(rk,sa2);rk[sa[0]]=0;
        for(int i=1;i<len;i++)rk[sa[i]]=rk[sa[i-1]]+!same(sa2,sa[i],sa[i-1],gap);
        m=rk[sa[len-1]]+1;if(len==m) return;
    }
}

void get_height(){
    for(int i=0;i<len;i++)rk[sa[i]]=i;
    int k=0;
    for(int i=0;i<len-1;i++){
        if(k) k--;
        int j=sa[rk[i]-1];
        while(s[i+k]==s[j+k])k++;
        height[rk[i]]=k;
    }
}

void premake(){
    get_sa('z'+1);
    get_height();
    /*for(int i=1;i<len;i++)printf("%d ",height[i]);
    cout<<endl;
    for(int i=1;i<len;i++)printf("%d ",a[sa[i]+1]);
    cout<<endl;*/
}

int find(int x){
    return father[x]==x?x:father[x]=find(father[x]);
}

void merge(int x,int y,int cur){
    int fx=find(x),fy=find(y);
    if(fx==fy) return;
    tot[cur]+=size[fx]*size[fy];
    ans=max(ans,Max[fx]*Max[fy]);
    ans=max(ans,Min[fx]*Min[fy]);
    Max[fy]=max(Max[fy],Max[fx]);
    Min[fy]=min(Min[fy],Min[fx]);
    size[fy]+=size[fx];father[fx]=fy;
}

void solve(){
    for(int i=0;i<=n;i++){
        father[i]=i;
        size[i]=1;Max[i]=Min[i]=a[sa[i]+1];
        mul[i]=-1e18;
    }
    for(int i=1;i<len;i++)pos[height[i]].push_back(i);
    ans=-1e18;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<pos[i].size();j++){
            int now=pos[i][j];
            merge(now,now-1,i);
        }
        anss[i]=ans;
    }
    for(int i=n-2;i>=1;i--)tot[i]+=tot[i+1];
    printf("%lld %lld\n",(ll)n*(ll)(n-1)/2,max(Max1*Max2,Min1*Min2));
    for(int i=1;i<n;i++)printf("%lld %lld\n",tot[i],anss[i]==-1e18?0:anss[i]);
}

void update(ll x){
    Max2=max(Max2,x);
    if(Max2>Max1) swap(Max1,Max2);
    Min2=min(Min2,x);
    if(Min2<Min1) swap(Min1,Min2);
}

int main(){
    freopen("bzoj4199.in","r",stdin);
    cin>>n>>s;s+='\n';len=s.length();
    Max1=Max2=-INF;Min1=Min2=INF;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        update(a[i]);
    }
    premake();
    solve();
    return 0;
}
