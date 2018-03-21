#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 40010
#define MAXM 140010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct complex{
	double real,imag;
	complex(){real=imag=0.0;}
	complex(int x){real=x,imag=0.0;}
	complex(double x,double y){real=x,imag=y;}
	complex operator +(const complex &a)const{
		return complex(real+a.real,imag+a.imag);
	}
	complex operator -(const complex &a)const{
		return complex(real-a.real,imag-a.imag);
	}
	complex operator *(const complex &a)const{
		return complex(real*a.real-imag*a.imag,real*a.imag+imag*a.real);
	}
}G1[MAXM],G2[MAXM],G3[MAXM],F1[MAXM],F2[MAXM],F3[MAXM],u[MAXM];

int n,Max,a[MAXN],ans[MAXM];

int lowbit(int x){return x&-x;}

int bit_reverse(int bit_mask,int size){
	int res=0;
	while(bit_mask) res|=size/2/lowbit(bit_mask),bit_mask-=lowbit(bit_mask);
	return res;
}

void fft(complex *A,int size,bool flag){
	for(int i=0;i<size;i++){
		int j=bit_reverse(i,size);
		if(i>j)swap(A[i],A[j]);
	}
	for(int i=0;i<size;i++){
		double angle=(flag?2.0:-2.0)*(double)i*M_PI/(double)size;
		u[i]=complex(cos(angle),sin(angle));
	}
	for(int step=2;step<=size;step<<=1){
		int gap=step>>1;int add=size/step;
		for(int i=0;i<size;i+=step){
			for(int j=i;j<i+gap;j++){
				int k1=(j-i)*add;
				int k2=k1+gap*add;
				complex new1=A[j]+A[j+gap]*u[k1];
				complex new2=A[j]+A[j+gap]*u[k2];
				A[j]=new1,A[j+gap]=new2;
			}
		}
	}
	if(!flag){
		for(int i=0;i<size;i++){
			A[i].real/=(double)size;
			A[i].imag/=(double)size;
		}
	}
}

int main(){
    freopen("bzoj3771.in","r",stdin);
    scanf("%d",&n);int size=131072;
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	Max=max(Max,a[i]);
    }
    for(int i=1;i<=n;i++){
    	G1[a[i]].real=G1[a[i]].real+1;
    	G2[a[i]*2].real=G2[2*a[i]].real+1;
    	G3[a[i]*3].real=G3[3*a[i]].real+1;
    }
    fft(G1,size,true);fft(G2,size,true);
    for(int i=0;i<size;i++){
    	F1[i]=G1[i]*G1[i]*G1[i];
    	F2[i]=G1[i]*G2[i];
    	F3[i]=G1[i]*G1[i];
    }
	fft(F1,size,false);fft(F2,size,false);fft(F3,size,false);
	fft(G1,size,false);fft(G2,size,false);
	for(int i=0;i<=Max*3;i++){
		double x=(F1[i].real-3*F2[i].real+2*G3[i].real)/6+(F3[i].real-G2[i].real)/2+G1[i].real;
		ans[i]=llround(x);
	}
	for(int i=0;i<=Max*3;i++){
		if(ans[i]) printf("%d %d\n",i,ans[i]); 
	}
    return 0;

}