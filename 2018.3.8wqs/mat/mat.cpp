#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n;
ll a[MAXN],b[MAXN];

int main(){
    freopen("mat.in","r",stdin);
    freopen("mat.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
    sort(a+1,a+n+1);sort(b+1,b+n+1);
	ll sum1=0,sum2=0,res=0,pos=0;
	for(int i=1;i<=n;i++){
		while(pos<n && b[pos+1]<a[i]){
			pos++;sum1+=b[pos],sum2+=b[pos]*b[pos];
		}
		res+=pos*a[i]*a[i]+sum2-2LL*a[i]*sum1;
	}
	sum1=sum2=pos=0;
	for(int i=1;i<=n;i++){
		while(pos<n && a[pos+1]<b[i]){
			pos++;sum1+=a[pos],sum2+=a[pos]*a[pos];
		}
		res-=pos*b[i]*b[i]+sum2-2LL*b[i]*sum1;
	}
	printf("%.1f",(double)res/(double)n);
    return 0;
}