#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=300015;
typedef long long int64;
typedef pair<int,int> PII;
int n,v[maxn];char s[maxn];
struct Tsuffix_array{
    int sum[maxn],sa[maxn],rank[maxn],tsa[maxn],trank[maxn];
    bool cmp(int i,int j,int l){
        if (i+l>n||j+l>n) return 0;
        return rank[i]==rank[j]&&rank[i+l]==rank[j+l];
    }
    void suffix_sort(){
        int m=255,p,i,j;
        for (i=0;i<=m;++i) sum[i]=0;
        for (i=1;i<=n;++i) ++sum[rank[i]=s[i]];
        for (i=1;i<=m;++i) sum[i]+=sum[i-1];
        for (i=n;i>=1;--i) sa[sum[rank[i]]--]=i;
        for (j=1,p=0;p<n;j<<=1,m=p){
            for (p=0,i=n-j+1;i<=n;++i) tsa[++p]=i;
            for (i=1;i<=n;++i) if (sa[i]>j) tsa[++p]=sa[i]-j;
            for (i=0;i<=m;++i) sum[i]=0;
            for (i=1;i<=n;++i) ++sum[rank[tsa[i]]];
            for (i=1;i<=m;++i) sum[i]+=sum[i-1];
            for (i=n;i>=1;--i) sa[sum[rank[tsa[i]]]--]=tsa[i];
            for (p=trank[sa[1]]=1,i=2;i<=n;++i) trank[sa[i]]=cmp(sa[i],sa[i-1],j)?p:++p;
            memcpy(rank,trank,sizeof(int)*(n+1));
        }
    }
    int height[maxn];
    void get_height(){
        for (int h=0,i=1;i<=n;++i){
            if (rank[i]==1) continue;
            for (h?--h:0;s[i+h]==s[sa[rank[i]-1]+h];++h);
            height[rank[i]]=h; 
        }
    }
    int fa[maxn],siz[maxn],fmx[maxn],fmn[maxn];
    int find(int u){return u==fa[u]?u:fa[u]=find(fa[u]);}
    void merge(int x,int y){
        if (siz[x]<siz[y]) swap(x,y);
        fa[y]=x;siz[x]+=siz[y];
        fmx[x]=max(fmx[x],fmx[y]);
        fmn[x]=min(fmn[x],fmn[y]);
    }
    PII t[maxn];
    int64 ans1[maxn],ans2[maxn];
    void get_ans(){
        for (int i=2;i<=n;++i) t[i-1]=make_pair(height[i],i);
        for (int i=1;i<=n;++i) fmx[rank[i]]=fmn[rank[i]]=v[i];
        sort(t+1,t+n,greater<PII>());memset(ans2,200,sizeof(ans2));
        for (int i=1;i<=n;++i){fa[i]=i;siz[i]=1;}
        for (int i=1;i<=n-1;++i){
            int x=find(t[i].second-1),y=find(t[i].second);
            ans1[t[i].first]+=1ll*siz[x]*siz[y];
            ans2[t[i].first]=max(ans2[t[i].first],1ll*fmx[x]*fmx[y]);
            ans2[t[i].first]=max(ans2[t[i].first],1ll*fmn[x]*fmx[y]);
            ans2[t[i].first]=max(ans2[t[i].first],1ll*fmx[x]*fmn[y]);
            ans2[t[i].first]=max(ans2[t[i].first],1ll*fmn[x]*fmn[y]);
            merge(x,y);
        }
        for (int i=n-1;i>=0;--i){
            ans1[i]+=ans1[i+1];
            ans2[i]=max(ans2[i],ans2[i+1]);
        }
        for (int i=0;i<=n-1;++i)
            printf("%lld %lld\n",ans1[i],!ans1[i]?0:ans2[i]);
    }
}SA;
void init(){
    scanf("%d%s",&n,s+1);
    for (int i=1;i<=n;++i) scanf("%d",&v[i]);
}
void work(){
    SA.suffix_sort();
    SA.get_height();
    SA.get_ans();
}
int main(){
    freopen("bzoj4199.in","r",stdin);
    init();
    work(); 
    return 0;
}
