#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int t,prime[MAXN],cnt,mbs[MAXN],book[MAXN];
ll a,b,c,d,k;

void premake(){
	mbs[1]=1;
	for(int i=2;i<=100000;i++){
		if(!book[i]) prime[++cnt]=i,mbs[i]=-1;
		for(int j=1;j<=cnt && i*prime[j]<=100000;j++){
			book[i*prime[j]]=1;
			if(i%prime[j]==0){
				mbs[i*prime[j]]=0;break;
			}
			mbs[i*prime[j]]=-mbs[i];
		}
	}
}

ll f(ll x){
	return (b/x)*(d/x);
}

int main(){
    freopen("hdu1695.in","r",stdin);
    cin>>t;premake();
 	for(int j=1;j<=t;j++){
    	ll ans=0,res=0;
    	scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&d,&k);
    	printf("Case %d: ",j);
    	if(k==0){cout<<0<<endl;continue;}
    	ll Max=min(b,d),N=Max/k;
    	for(int i=1;i<=N;i++) ans+=f(i*k)*mbs[i];
    	b=d=Max;
    	for(int i=1;i<=N;i++) res+=f(i*k)*mbs[i];
    	res-=(b>=k);ans-=res>>1;
    	cout<<ans<<endl;
    }
    return 0;
}