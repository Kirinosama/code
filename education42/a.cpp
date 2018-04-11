#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
#define ii pair<int,int>
#define INF 0x3f3f3f3f

int n;
ll sum[200010];

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		ll x;scanf("%lld",&x);
		sum[i]=sum[i-1]+x;
	}
	for(int i=1;i<=n;i++){
		if(sum[i]*2LL>=sum[n]){
			cout<<i;
			return 0;
		}
	}
	return 0;
}
