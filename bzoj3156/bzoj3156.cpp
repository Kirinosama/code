#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define eps 1e-8
#define size (tail-head+1)
#define MAXN 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct point{
	ll x,y;
}p[MAXN];

ll n,a[MAXN],ans,f[MAXN],sum[MAXN];
int head,tail,q[MAXN];

double slope(point a,point b){
	return (double)(b.y-a.y)/(double)(b.x-a.x);
}

int main(){
    freopen("bzoj3156.in","r",stdin);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[n-i+1]);
    for(ll i=1;i<=n;i++) sum[i]=sum[i-1]+i;
    f[1]=a[1];head=tail=1;p[1]=(point){1,2*f[1]+2};q[1]=1;
	for(ll i=2;i<=n;i++){
		while(size>=2 && slope(p[q[head]],p[q[head+1]])<=2*i)
			head++;
		f[i]=f[q[head]]+sum[i-q[head]-1]+a[i];
		p[i]=(point){i,2*f[i]+i*i+i};
		while(size>=2 && slope(p[q[tail]],p[q[tail-1]])>slope(p[q[tail]],p[i]))
			tail--;
		q[++tail]=i;
	}
	ans=1e18;
	for(int i=1;i<=n;i++) ans=min(ans,f[i]+sum[n-i]);
	printf("%lld",ans);
    return 0;
}