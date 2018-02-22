#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 800010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct complex{
	double real,imag;
	complex(){real=imag=0.0;}
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
	void operator /= (double x){
		real/=x,imag/=x;
	}
}q[MAXN],g[MAXN],u[MAXN],c1[MAXN],c2[MAXN];

int n;

int lowbit(int x){
	return x&-x;
}

int bit_reverse(int x,int size){
	int res=0;
	for(int i=x;i;i-=lowbit(i)){
		res|=size/2/lowbit(i);
	}
	return res;
}

void fft(complex *a,int size,bool flag){
	for(int i=0;i<size;i++){
		int j=bit_reverse(i,size);
		if(i>j) swap(a[i],a[j]);
	}
	for(int i=0;i<size;i++){
		double angle=(flag?2.0:-2.0)*M_PI*(double)i/(double)size;
		u[i]=complex(cos(angle),sin(angle));
	}
	for(int step=2;step<=size;step<<=1){
		int gap=step>>1;
		int addgap=size/step;
		for(int i=0;i<size;i+=step){
			for(int j=i;j<i+gap;j++){
				int k1=(j-i)*addgap;
				int k2=k1+gap*addgap;
				complex new1=a[j]+a[j+gap]*u[k1];
				complex new2=a[j]+a[j+gap]*u[k2];
				a[j]=new1,a[j+gap]=new2;
			}
		}
	}
	if(!flag){
		for(int i=0;i<size;i++) a[i]/=(double)size;
	}
}

int main(){
    freopen("bzoj3527.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf",&q[i].real);
    for(int i=1;i<=n;i++) g[i].real=1.0/((double)i*double(i));
    int size=1;while(size<=2*n) size<<=1;
	fft(q,size,true);fft(g,size,true);
	for(int i=0;i<size;i++) c1[i]=q[i]*g[i];
	fft(c1,size,false);
	for(int i=0;i<size;i++) g[i]=complex();
	for(int i=0;i<n;i++) g[i]=complex(1.0/((double)(n-i)*(double)(n-i)));
	fft(g,size,true);
	for(int i=0;i<size;i++) c2[i]=q[i]*g[i];
	fft(c2,size,false);
	for(int i=1;i<=n;i++) printf("%.3f\n",c1[i].real-c2[n+i].real);
    return 0;
}