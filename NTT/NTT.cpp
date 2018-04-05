#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MOD 1004535809LL
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,root;
ll a[200010],b[200010],u[200010];

int getphi(int x){
	int tot=x;
	for(int i=2;i<=sqrt(x)+1;i++){
		if(!(x%i)){
			tot=tot/i*(i-1);
			while(!x%i) x/=i;
		}
	}
	if(x!=1) tot=tot/x*(x-1);
	return tot;
}

ll Pow(ll x,int k,int Mod){
	ll res=1;
	while(k){
		if(k&1) res=(res*x)%Mod;
		k>>=1;x=(x*x)%Mod;
	} 
	return res;
}

int getroot(int x){
	int a[1010],tot=0;
	int k=getphi(x);int cur=k;
	for(int i=2;i<=sqrt(k)+1;i++){
		if(!(k%i)){
			a[++tot]=i;
			while(!(k%i))k/=i;
		}
	}
	if(k)a[++tot]=k;
	for(int i=2;i<x;i++){
		bool flag=false;
		for(int j=1;j<=tot;j++){
			if(Pow(i,cur/a[j],x)==1){
				flag=true;
				break;
			}
		}
		if(!flag) return i;
	}
	return -1;
}

int bit_reverse(int x,int size){
	int res=0;
	for(int i=x;i;i-=i&-i){
		res|=size/2/(i&-i);
	}
	return res;
}

void NTT(ll *A,int size,bool flag){
	for(int i=0;i<size;i++){
		int j=bit_reverse(i,size);
		if(i>j) swap(A[i],A[j]);
	}
	ll mul=Pow(root,(MOD-1)/size,MOD);
	if(flag){
		u[0]=1;
		for(int i=1;i<size;i++) u[i]=(u[i-1]*mul)%MOD;
	}else{
		u[size]=1;
		for(int i=size-1;i>=0;i--) u[i]=(u[i+1]*mul)%MOD;
	}
	for(int step=2;step<=size;step<<=1){
		int gap=step>>1;int add_gap=size/step;
		for(int i=0;i<size;i+=step){
			for(int j=i;j<i+gap;j++){
				int k1=(j-i)*add_gap;
				int k2=k1+gap*add_gap;
				ll new1=(A[j]+A[j+gap]*u[k1])%MOD;
				ll new2=(A[j]+A[j+gap]*u[k2])%MOD;
				A[j]=new1,A[j+gap]=new2;
			}
		}
	}
	ll inv=Pow(size,MOD-2,MOD);
	if(!flag)
		for(int i=0;i<size;i++) A[i]=(A[i]*inv)%MOD;
}

int main(){
    freopen("NTT.in","r",stdin);
    cin>>n>>m;root=getroot(MOD);
    for(int i=0;i<n;i++) scanf("%lld",&a[i]);
    for(int i=0;i<m;i++) scanf("%lld",&b[i]);
    int size=1;while(size<n+m)size<<=1;
    NTT(a,size,true);NTT(b,size,true);
    for(int i=0;i<size;i++) a[i]=(a[i]*b[i])%MOD;
    NTT(a,size,false);
	for(int i=0;i<size;i++)
		printf("%lld\n",a[i]);
    return 0;
}
