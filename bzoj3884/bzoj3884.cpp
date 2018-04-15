#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int get_phi(int x){
	int res=x;
	for(int i=2;i<=sqrt(x)+1;i++){
		if(x%i==0) res=(res/i)*(i-1);
		while(x%i==0) x/=i;
	}
	return x==1?res:res/x*(x-1);
}

int pow(long long x,int k,int mod){
	long long res=1;
	while(k){
		if(k&1) res=(res*x)%mod;
		k>>=1,x=(x*x)%mod;
	}
	return res;
}

int f(int x){
	if(x==1) return 0;
	int phi=get_phi(x);
	return pow(2,f(phi)+phi,x);
}

int main(){
	freopen("bzoj3884.in","r",stdin);
	int t;cin>>t;
	while(t--){
		int x;cin>>x;
		printf("%d\n",f(x));
	}
	return 0;
}
