#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 500010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll a[MAXN],m,s[MAXN],f[MAXN];
int n;

struct node{
	ll x,y;
	node(){}
	node(ll p,ll q){x=p,y=q;}
}q[MAXN];

void solve(){
	int head=1,tail=1;
	q[head]=node(0,0);
	for(int i=1;i<=n;i++){
		while(head<tail && q[head+1].y-q[head].y<2*s[i]*(q[head+1].x-q[head].x)) head++;
		f[i]=q[head].y-2*q[head].x*s[i]+s[i]*s[i]+m;
		ll tx=s[i],ty=s[i]*s[i]+f[i];
		while(head<tail && (ty-q[tail].y)*(q[tail].x-q[tail-1].x)<=(tx-q[tail].x)*(q[tail].y-q[tail-1].y))
			tail--;
		q[++tail]=node(tx,ty);
	}
	printf("%lld\n",f[n]);
}

int main(){
    freopen("hdu3507.in","r",stdin);
    while(scanf("%d%lld",&n,&m)!=EOF){
    	s[0]=0;
    	for(int i=1;i<=n;i++){
    		scanf("%lld",&a[i]);
    		s[i]=s[i-1]+a[i];
    	}
    	solve();
    }
    return 0;
}