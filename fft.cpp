#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 100010

struct complex{
	double real,imag;
	complex(){}
	complex(double x){real=x,imag=0.0;}
	complex(double x,double y){real=x,imag=y;}
	complex operator + (const complex &a)const{
		return complex(real+a.real,imag+a.imag);
	}
	complex operator - (const complex &a)const{
		return complex(real-a.real,imag-a.imag);
	}
	complex operator * (const complex &a)const{
		return complex(real*a.real-imag*a.imag,real*a.imag+imag*a.real);
	}
}a[MAXN],b[MAXN],c[MAXN],u[MAXN];

int n,m;

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
		for(int i=0;i<size;i+=step){
			for(int j=i;j<i+gap;j++){
				int k1=(j-i)*add_gap;
				int k2=k1+gap*add_gap;
				complex new1=A[j]+A[j+gap]*u[k1];
				complex new2=A[j]+A[j+gap]*u[k2];
				A[j]=new1,A[j+gap]=new2;
			}
		}
	}
	if(!flag){
		for(int i=0;i<size;i++)A[i].real/=(double)size,A[i].imag/=(double)size;
	}
}


int main(){
	cin>>n>>m;
	for(int i=0;i<=n;i++){
		int x;scanf("%d",&x);
		a[i]=complex(x);
	}
	for(int i=0;i<=m;i++){
		int x;scanf("%d",&x);
		b[i]=complex(x);
	}
	int size=1;
	while(size<=n+m)size<<=1;
	fft(a,size,true);fft(b,size,true);
	for(int i=0;i<size;i++)c[i]=a[i]*b[i];
	fft(c,size,false);
	for(int i=0;i<size;i++)printf("%d ",llround(c[i].real));
	return 0;
}
