#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD=998244353;

int n,k;
ll f[1000010],mul[1000010],num[1000010],ans;

int main(){
	freopen("input","r",stdin);
	cin>>n>>k;
	for(int i=1;i<(1<<k);i++)num[i]=num[i-(i&-i)]+1;
	for(int i=1;i<(1<<k);i++)f[i]=1;
	for(int i=2;i<=n;i++){
		for(int j=(1<<k)-1;j>0;j--){
			f[j]=0;
			for(int p=(j-1)&j;p;p=(p-1)&j){
				f[j]=(f[j]+(f[p]*((1<<num[p])%MOD)))%MOD;
			}
		}
	}
	for(int i=1;i<(1<<k);i++)
		ans=(ans+f[i])%MOD;
	cout<<ans;
	return 0;
}
