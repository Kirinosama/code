#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll n,ans;

ll make(ll x){
	ll r=min(x-1,n);
	ll l=(x+1)/2;
	return r>=l?r-l+1:0;
}

void solve(ll x){
	int cnt=0;ll maxnum=1;
	bool flag=true;
	for(ll i=x;i;i/=10,cnt++)
		if(i%10!=9) flag=false;
	int maxlen=flag?cnt:cnt-1;
	for(int i=1;i<=maxlen;i++,maxnum*=10);
		maxnum--;
	for(ll i=0;i<9;i++)
		ans+=make(i*(maxnum+1)+maxnum);
	cout<<ans;
}

int main(){
    freopen("cf452.in","r",stdin);
    cin>>n;
    if(n<=4) cout<<n*(n-1)/2;
    else solve(n+n-1);
    return 0;
}