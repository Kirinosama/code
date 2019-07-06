#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007LL 
typedef long long ll;

int s,t,k;
ll ans,mul[400010];

ll Pow(ll x,ll k){
	if(!x) return 1;
	ll res=1;
	while(k){
		if(k&1) res=(res*x)%MOD;
		x=(x*x)%MOD;
		k>>=1;
	}
	return res;
}

void premake(){
	mul[1]=1;
	for(ll i=2;i<=400000;i++)
		mul[i]=(mul[i-1]*i)%MOD;
}

ll c(int x,int y){
	if(y>x) return 0;
	if(x==y) return 1;
	if(!y) return 1;
	ll res=mul[x];
	res=(res*Pow(mul[x-y],MOD-2))%MOD;
	res=(res*Pow(mul[y],MOD-2))%MOD;
	return res;
}

int main(){
//	freopen("input","r",stdin);
	cin>>s>>t>>k;
	if(s>t) swap(s,t);
	premake();
	for(int i=t-s;i<=k;i++){
		if((t-s+i)&1) continue; 
		int x=(t-s+i)/2,y=(i-t+s)/2;
		ans=(ans+c(x+y,x))%MOD;
		ans=(ans+MOD-c(x+y,x+s+1))%MOD;
	}
	cout<<ans;
	return 0;
}
