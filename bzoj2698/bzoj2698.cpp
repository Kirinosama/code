#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll a[MAXN],s,t;
int n,m;
double ans;

ll make(ll x){
	if(x<s) return 0;
	ll r=x-s+1;
	ll l=max(0LL,x-t+1);
	return (l+r)*(r-l+1)/2;
}

double pow(double x,int k){
    double res=1.0;
    while(k){
        if(k&1) res*=x;
        x*=x,k>>=1;
    }
    return res;
}

double cal(int x){
    return pow((double)(a[x-1]+a[n-x])/(double)a[n],m);
}

int main(){
    freopen("bzoj2698.in","r",stdin);
    scanf("%d %d %lld %lld",&n,&m,&s,&t);
    for(ll i=1;i<=n;i++)
    	a[i]=make(i);
    for(int i=1;i<=n;i++)
        ans+=1.0-cal(i);
    printf("%.3f",ans);
    return 0;
}