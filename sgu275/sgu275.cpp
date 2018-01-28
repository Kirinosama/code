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

ll a[MAXN],m[MAXN];
int Log,n;

void solve(ll mask){
	ll highbit=1LL<<(ll)(Log-1);
	for(int i=1;i<=Log;i++,highbit>>=1){
		if(mask&highbit)
			mask^=m[i];
	}
	if(mask){
		highbit=1LL<<(ll)(Log-1);
		for(int i=1;i<=Log;i++,highbit>>=1)
			if(mask&highbit){
				m[i]=mask;
				for(int j=1;j<i;j++)
					if(m[j]&highbit) m[j]^=mask;
				break;
			}
	}
}

int main(){
    freopen("sgu275.in","r",stdin);
	cin>>n;	while((1LL<<(ll)Log)<=1e18) Log++;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		solve(a[i]);
	}
	ll ans=0;
	for(int i=1;i<=Log;i++) ans^=m[i];
	cout<<ans;
    return 0;
}