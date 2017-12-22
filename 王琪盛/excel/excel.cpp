#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll MOD=1e9+7;
ll ans;
ll r,c,mint,maxt;

int main(){
	freopen("excel.in","r",stdin);
	freopen("excel.out","w",stdout);
	cin>>r>>c>>mint>>maxt;
	for(ll i=2;i<r;i++)
		for(ll j=2;j<c;j++){
			if(2*(i+j)>=mint && 2*(i+j)<=maxt)
				ans=(ans+(i-1)*(j-1)*(r-i)*(c-j))%MOD;
		}
	ans=(ll)(ans*6)%MOD;
	cout<<ans;
	return 0;
}