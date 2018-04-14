#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 1000000007
#define MAXN 1000010
typedef long long ll;

int t;
ll mul[MAXN],f[MAXN];

void premake(){
	mul[1]=1;mul[0]=1;
	for(int i=2;i<=1e6;i++)
		mul[i]=(mul[i-1]*i)%MOD;
	f[1]=0;f[0]=1;
	for(int i=2;i<=1e6;i++)
		f[i]=(f[i-1]*i+(i%2?-1:1))%MOD;
}

void exgcd(ll a,ll b,ll &d,ll &x,ll &y){
	if(!b){
		d=a,x=1,y=0;
	}else{
		exgcd(b,a%b,d,y,x);
		y-=x*(a/b);
	}
}

ll inv(ll p,ll q){
	ll d,x,y;
	exgcd(p,q,d,x,y);
	return d==1?(x+q)%q:-1;
}

ll c(int x,int y){
	return ((mul[x]*inv(mul[x-y],MOD))%MOD*inv(mul[y],MOD))%MOD;
}

ll solve(int x,int y){
	 return (c(x,y)*f[x-y])%MOD;
}

int main(){
	freopen("bzoj4517.in","r",stdin);
	premake();
	cin>>t;
	while(t--){
		int x,y;
		scanf("%d%d",&x,&y);
		cout<<solve(x,y)<<endl;
	}
	return 0;
}
