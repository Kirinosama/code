#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll ans;
ll n,m,k;

const ll MOD=1000000007;

ll POW(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1) res=(res*x)%MOD;
		x=(x*x)%MOD;y>>=1;
	}
	return res;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m>>k;
	if(k==-1 && ((n&1)!=(m&1))){
		cout<<0;
		return 0;
	}
	ans=POW(2,n-1);
	ans=POW(ans,m-1);
	cout<<ans;
	return 0;
}