#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define Mod 1004535809
#define MAXM 8010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll sum;
int size,wh;
int n,m,x,s,cnt[MAXM],book[MAXM],res[MAXM],rt;

struct complex{
	double real,imag;
	complex (){}
	complex (double x,double y){real=x,imag=y;}
	complex (ll x){real=x,imag=0;}
	complex operator + (const complex &a)const{
		return complex(real+a.real,imag+a.imag);
	}
	complex operator - (const complex &a)const{
		return complex(real-a.real,imag-a.imag);
	}
	complex operator * (const complex &a)const{
		return complex(real*a.real-imag*a.imag,real*a.imag+imag*a.real);
	}
}a[MAXM*8],b[MAXM*8],cur[MAXM*8],u[MAXM*8];

void getroot(){
	for(int i=2;i<m;i++){
		memset(book,0,sizeof(book));
		int cur=1,cnt=0;
		while(cnt<m-1){
			if(book[cur]) break;
			book[cur]=1,cnt++,cur=(cur*i)%m;
		}
		if(cnt==m-1){
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

int lowbit(int x){return x&-x;}

int bit_reverse(int mask){
	int ans=0;
	for(int i=mask;i;i-=lowbit(i)){
		ans|=size/2/lowbit(i);
	}	
	return ans;
}

void fft(complex *A,bool type){
	for(int i=0;i<size;i++){
		int pos1=bit_reverse(i);
		if(pos1<i) swap(A[i],A[pos1]);
	}
	for(int i=0;i<size;i++){
		double angle=(type?2.0:-2.0)*M_PI/(double)size*(double)i;
		u[i]=complex(cos(angle),sin(angle));
	}
	for(int step=2;step<=size;step<<=1){
		int gap=step/2;
		for(int i=0;i<size;i+=step){
			int dist=size/step;
			for(int j=i;j<i+gap;j++){
				int k1=(j-i)*dist;
				int k2=(j-i+gap)*dist;
				complex new1(A[j]+A[j+gap]*u[k1]);
				complex new2(A[j]+A[j+gap]*u[k2]);
				A[j]=new1,A[j+gap]=new2;
			}
		}
	}
	if(!type)
		for(int i=0;i<size;i++)
			A[i].real/=(double)size,A[i].imag/=(double)size;
}

void fftmul(complex *A,complex *B){
	for(int i=0;i<size;i++)
		cur[i]=complex(0,0);
	for(int i=0;i<=m-3;i++)
		cur[i]=B[i+1];
	for(int i=m-2;i<=2*m-4;i++)
		cur[i]=B[i-(m-2)];
	fft(A,true);
	fft(cur,true);
	for(int i=0;i<size;i++)
		A[i]=A[i]*cur[i];
	fft(A,false);
	for(int i=0;i<=m-2;i++)
		A[i]=complex(llround(A[i+m-2].real)%Mod);
	for(int i=m-1;i<=size;i++)
		A[i]=complex(0,0);
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
    pow(n-1);
    for(int i=0;i<m-1;i++)if(res[i]==x)wh=i;
    for(int i=0;i<m-1;i++){
    	sum+=(ll)cnt[res[i]]*llround(a[wh].real);
    	sum%=Mod;
    	wh--;if(wh<0) wh+=m-1;
    }
    printf("%lld",sum);
    return 0;
}