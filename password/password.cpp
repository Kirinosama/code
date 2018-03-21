#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n;
ll k,a[50];
map <ll,ll> mp;

bool judge(int mask){
	ll sum=0;
	for(int i=1;i<=n;i++){
		if(mask&1) sum+=a[i];
		mask>>=1;
	}
	return sum==k;
}

ll cal(int s,int mask){
	ll sum=0;
	for(int i=1;i<=n;i++){
		if(mask&1) sum+=a[s+i];
		mask>>=1;
	}
	return sum;
}

void update(ll x){
	if(mp[x]) mp[x]=mp[x]+1;
	else mp[x]=1;
}

int main(){
    freopen("password.in","r",stdin);
    freopen("password.out","w",stdout);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
	if(n<=6){  
		int ans=0;
		for(int i=0;i<(1<<n);i++) if(judge(i)) ans++;
		cout<<ans;
	}else{
		int mid=n/2;ll ans=0;
		for(int i=0;i<(1<<mid);i++)update(cal(0,i));
		for(int i=0;i<(1<<(n-mid));i++) ans+=mp[k-cal(mid,i)];
		cout<<ans;
	}
    return 0;
}