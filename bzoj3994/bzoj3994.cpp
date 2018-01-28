#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
// #include <cmath>
using namespace std;

#define Mod 1004535809LL
#define MAXM 8010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll sum,INV;
ll size,wh;
int n,m,x,s,cnt[MAXM],res[MAXM],rt;
ll a[MAXM*8],b[MAXM*8],cur[MAXM*8],u[MAXM*8];

void getroot(){
	for(int i=2;i<m;i++){
		int cur=i,cnt=0;
		while(cur!=1)
			cnt++,cur=(cur*i)%m;
		if(cnt==m-2){
			rt=i;break;
		}
	}
	int MOD=1;
	for(int i=0;i<m-1;i++){
		res[i]=MOD;
		MOD=(MOD*rt)%m;
		b[i]=cnt[res[i]];
	}
}

ll pow(ll x,ll k){
	ll res=1;
	while(k){
		if(k&1) res=(res*x)%Mod;
		x=(x*x)%Mod,k>>=1;
	}
	return res;
}

int lowbit(int x){return x&-x;}

int bit_reverse(int mask){
	int ans=0;
	for(int i=mask;i;i-=lowbit(i)){
		ans|=size/2/lowbit(i);
	}	
	return ans;
}

void fft(ll *A,bool type){
	for(int i=0;i<size;i++){
		int pos1=bit_reverse(i);
		if(pos1<i) swap(A[i],A[pos1]);
	}
	ll mul=pow(3,(Mod-1)/size);
	if(type){
		u[0]=1;
		for(int i=1;i<size;i++)
			u[i]=(u[i-1]*mul)%Mod;
	}
	else{
		u[size-1]=mul;
		for(int i=size-2;i>=0;i--)
			u[i]=(u[i+1]*mul)%Mod;
	}
	for(int step=2;step<=size;step<<=1){
		int gap=step/2;
		for(int i=0;i<size;i+=step){
			int dist=size/step;
			for(int j=i;j<i+gap;j++){
				int k1=(j-i)*dist;
				int k2=(j-i+gap)*dist;
				ll new1=(A[j]+A[j+gap]*u[k1])%Mod;
				ll new2=(A[j]+A[j+gap]*u[k2])%Mod;
				A[j]=new1,A[j+gap]=new2;
			}
		}
	}
	if(!type)
		for(int i=0;i<size;i++)
			A[i]=(A[i]*INV)%Mod;
}

void fftmul(ll *A,ll *B){
	for(int i=0;i<size;i++)
		cur[i]=0;
	for(int i=0;i<=m-3;i++)
		cur[i]=B[i+1];
	for(int i=m-2;i<=2*m-4;i++)
		cur[i]=B[i-(m-2)];
	fft(A,true);
	fft(cur,true);
	for(int i=0;i<size;i++)
		A[i]=(A[i]*cur[i])%Mod;
	fft(A,false);
	for(int i=0;i<=m-2;i++)
		A[i]=A[i+m-2]%Mod;
	for(int i=m-1;i<=size;i++)
		A[i]=0;
}

void pow(int k){
	while(k){
		if(k&1) fftmul(a,b);
		fftmul(b,b),k>>=1;
	}
}

int main(){
    freopen("bzoj3994.in","r",stdin);
    cin>>n>>m>>x>>s;
    for(int i=1;i<=s;i++){
    	static int t;
    	scanf("%d",&t),cnt[t]=1;
    }
    getroot();
    a[0]=size=1;
    while(size<=3*m-4) size<<=1;
    INV=pow(size,Mod-2);
    pow(n-1);
    for(int i=0;i<m-1;i++)if(res[i]==x)wh=i;
    for(int i=0;i<m-1;i++){
    	sum+=((ll)cnt[res[i]]*a[wh])%Mod;
    	sum%=Mod;
    	wh--;if(wh<0) wh+=m-1;
    }
    printf("%lld",sum);
    return 0;
}