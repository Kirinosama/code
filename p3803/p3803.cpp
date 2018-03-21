#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct complex{
	double real,imag;
	complex(){real=imag=0.0;}
	complex(double x,double y){real=x,imag=y;}
	complex(double x){real=x,imag=0.0;}
	complex operator + (const complex &a)const{
		return complex(real+a.real,imag+a.imag);
	}
	complex operator - (const complex &a)const{
		return complex(real-a.real,imag-a.imag);
	}
	complex operator * (const complex &a)const{
		return complex(real*a.real-imag*a.imag,real*a.imag+imag*a.real);
	}
}A[MAXN*4],B[MAXN*4],u[MAXN*4];

int n,m;

inline int read(){
	int x=0,w=0;char ch;
	while(ch<'0' || ch>'9') w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

int lowbit(int x){
	return x&-x;
}

int bit_reverse(int x,int size){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res|=size/2/lowbit(i);
	return res;
}

void fft(complex *A,int size,bool flag){
	for(int i=0;i<size;i++){
		int j=bit_reverse(i,size);
		if(i>j) swap(A[i],A[j]);
	}
	for(int i=0;i<size;i++){
		double ang=(flag?2.0:-2.0)*M_PI*(double)i/(double)size;
		u[i]=complex(cos(ang),sin(ang));
	}
	for(int step=2;step<=size;step<<=1){
		int gap=step>>1,add_gap=size/step;
		for(int i=0;i<size;i+=step)
			for(int j=i;j<i+gap;j++){
				int k1=(j-i)*add_gap;
				int k2=k1+gap*add_gap;
				complex new1=A[j]+A[j+gap]*u[k1];
				complex new2=A[j]+A[j+gap]*u[k2];
				A[j]=new1,A[j+gap]=new2;
			}
	}
	if(!flag){
		for(int i=0;i<size;i++)
			A[i].real/=(double)size,A[i].imag/=(double)size;
	}
}

int main(){
    freopen("p3803.in","r",stdin);
    cin>>n>>m;
 	int size=1;
 	while(size<=n+m) size<<=1;
 	for(int i=0;i<=n;i++) A[i]=complex(read());
 	for(int i=0;i<=m;i++) B[i]=complex(read());
 	fft(A,size,true);fft(B,size,true);
 	for(int i=0;i<size;i++) A[i]=A[i]*B[i];
 	fft(A,size,false);
 	for(int i=0;i<=n+m;i++) printf("%d ",(int)(A[i].real+0.5));
    return 0;
}