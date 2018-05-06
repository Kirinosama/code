#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define eps 1e-9
#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

double f[MAXN],A[MAXN],B[MAXN],R[MAXN],p[MAXN],q[MAXN];
int n,s[MAXN],Q[MAXN],s1[MAXN];

bool cmp(const int &x,const int &y){
    return q[x]<q[y];
}

bool cmp1(const int &x,const int &y){
    return -B[x]/A[x]>-B[y]/A[y];
}

double slope(int x,int y){
    if(fabs(q[x]-q[y])<eps) return 1e20;
    return (p[x]-p[y])/(q[x]-q[y]);
}
    
void solve(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    solve(l,mid);double Max=0.0;
    for(int i=l;i<=mid;i++){
        int j=s[i];Max=max(Max,f[i]);
        p[j]=f[j]*R[j]/(A[j]*R[j]+B[j]);
        q[j]=f[j]/(A[j]*R[j]+B[j]);
    }
    sort(s+l,s+mid+1,cmp);
    int tail=0;
    for(int i=l;i<=mid;i++){
        while(tail>=2 && slope(s[i],Q[tail])>slope(Q[tail],Q[tail-1]))tail--;
        Q[++tail]=s[i];
    }
    int now=1;
    for(int i=mid+1;i<=r;i++)s1[i]=s[i];
    sort(s+mid+1,s+r+1,cmp1);
    for(int i=mid+1;i<=r;i++){
        while(now<tail && slope(Q[now],Q[now+1])>-B[s[i]]/A[s[i]])now++;
        f[s[i]]=max(f[s[i]],A[s[i]]*p[Q[now]]+B[s[i]]*q[Q[now]]);
        f[s[i]]=max(f[s[i]],Max);
    }
    for(int i=mid+1;i<=r;i++)s[i]=s1[i];
    solve(mid+1,r);
}

int main(){
    freopen("bzoj1492.in","r",stdin);
    cin>>n>>f[0];
    for(int i=1;i<=n;i++)scanf("%lf%lf%lf",&A[i],&B[i],&R[i]);
    for(int i=1;i<=n;i++)f[i]=f[0],s[i]=i;
    solve(1,n);double ans=0.0;
    for(int i=1;i<=n;i++)ans=max(ans,f[i]);
    printf("%.3lf",ans);
    return 0;
}
